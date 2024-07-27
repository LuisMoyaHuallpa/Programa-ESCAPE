#include "pedestrian.h"
#include "io.h"
#include "nodeEvacution.h"
#include "stateMatrix.h"
#include "subLink.h"
#include "tiempo.h"
#include <cstddef>
#include <cstdio>
#include <map>
#include <utility>
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sarsa pedestrian::sarsaAlgorithm;
int pedestrian::contador = 1;
const int pedestrian::surviveReward = 100000;
const int pedestrian::deadReward = -1000; 
const int pedestrian::stepReward = -1;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// pedestrian::pedestrian() : nodeFinal() {
//     (*this).idPedestrian = 0;
//     (*this).hhType = 0;
//     (*this).hhId = 0;
// }
pedestrian::pedestrian(const int edad, const int gender, const int hhType, const int hhId, const node* nodeArranque)
    : idPedestrian(contador++), edad(edad), gender(gender), hhType(hhType), hhId(hhId),
      nodeArranque(nodeArranque), nodeInicio(nullptr), nodeFinal(nullptr), nodeInicioAnterior(nullptr),
      direccionPedestrian(), tiempoInicial(0), evacuado(false), reward(0),
      QCurrent(nullptr), QPrevious(nullptr),
      velocidad() {
    nodeInicio = const_cast<node*>(nodeArranque);
    verificarPedestrianEvacuation();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrian::setPosition(vector2D position) {
    (*this).position = position;
}
void pedestrian::setNodeInicio(node* nodeInicio){
    (*this).nodeInicio = nodeInicio;
}
void pedestrian::setNodeFinal(node* nodeFinal) {
    (*this).nodeFinal = nodeFinal;
}
void pedestrian::setNodeInicioAnterior(node* nodeInicioAnterior) {
    (*this).nodeInicioAnterior = nodeInicioAnterior;
}
void pedestrian::setLinkActual(link* linkActual) {
    (*this).linkActual = linkActual;
}
void pedestrian::setLinkPasado(link *linkPasado) {
    (*this).linkPasado = linkPasado;
}
void pedestrian::setDireccionPedestrian(vector2D direccionPedestrian) {
    (*this).direccionPedestrian = direccionPedestrian;
}
void pedestrian::setVelocidad(vector2DVelocidad velocidad) {
    (*this).velocidad = velocidad;
}
void pedestrian::setTiempoInicial(int tiempoInicial) {
    const_cast<int&>((*this).tiempoInicial) = tiempoInicial;
}
// void pedestrian::setOrientacionLinkPasado(vector2D orientacionLinkPasado) {
//     (*this).orientacionLinkPasado = orientacionLinkPasado;
// }
// void pedestrian::setTiempoFinal(int tiempoFinal) {
//     (*this).tiempoFinal = tiempoFinal;
// }
// void pedestrian::setEmpezoCaminar(bool empezoCaminar) {
//     (*this).empezoCaminar = empezoCaminar;
// }
// void pedestrian::setPrimerTiempo(bool primerTiempo) {
//     (*this).primerTiempo = primerTiempo;
// }
// void pedestrian::setSaltoLink(bool saltoLink) {
//     (*this).saltoLink = saltoLink;
// }
void pedestrian::setEvacuado(bool evacuado) {
    (*this).evacuado = evacuado;
}
void pedestrian::setReward(int reward) {
    (*this).reward = reward;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int pedestrian::getIdPedestrian() const {
    return idPedestrian;
}
const int pedestrian::getEdad() const{
    return edad;
}
const int pedestrian::getGender() const {
    return gender;
}
const int pedestrian::getHHType() const{
    return hhType;
}
const int pedestrian::getHHId() const{
    return hhId;
}
const vector2D pedestrian::getPosition() const{
    return position;
}
const node* pedestrian::getNodeArranque() const {
    return nodeArranque;
}
const node* pedestrian::getNodeInicio() const{
    return nodeInicio;
}
const node* pedestrian::getNodeFinal() const {
    return nodeFinal;  
}
const node* pedestrian::getNodeInicioAnterior() const {
    return nodeInicioAnterior;  
}
const link* pedestrian::getLinkActual() const {
    return linkActual;
}
const link* pedestrian::getLinkPasado() const {
    return linkPasado;
}
vector2D pedestrian::getDireccionPedestrian() const {
    return direccionPedestrian;
}
vector2DVelocidad& pedestrian::getVelocidad() {
    return velocidad;
}
const int pedestrian::getTiempoInicial() const {
    return tiempoInicial;
}
const bool pedestrian::getEvacuado() const {
    return evacuado;
}
const int pedestrian::getReward() const {
    return reward;  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool pedestrian::operator==(const pedestrian& pedestrian2) const{
    /* compara si dos pedestrian son iguales*/
    // la comparacion es con id
    return idPedestrian == pedestrian2.idPedestrian;
}
void pedestrian::caminar() {
    /* formula de desplazamiento*/
    position += velocidad * tiempo::get()->getDeltaT();
}
double pedestrian::calcularIDoubleSublink() {
    /* Calcula la ubicacion de la persona en el array del subLink*/
    // distancia de la persona al nodeInicio de la persona
    double index_x = position.getX() - nodeInicio->getCoordenada().getX();
    double index_y = position.getY() - nodeInicio->getCoordenada().getY();
    double index_hipo = std::sqrt(std::pow(index_x,2) + pow(index_y, 2)) / static_cast<double>(linkActual->getAnchoSubdivisiones());
    // if (direccionPedestrian.getX()<0) {
    //     index_hipo = link::numberDivisiones-1-index_hipo;
    // }
    return index_hipo;
}
void pedestrian::contarPedestrianInSublink() {
    /* Cada persona tiene una posicion por lo tanto sabe donde agregar el conteo,
        esto significa que no cuenta en todo las calles, solo en las calles que
        hay personas.*/
    double index_d = calcularIDoubleSublink();
    int index = std::floor(index_d);
    // verifica si la persona esta en intersecciones, al inicio o final
    if (!(index == 0 or index == link::numberLinkDivision)) {
        // convierto index_d a int debido a que quiero los index del vector sublink, y contar
        // cuenta la cantidad de personas en la calle
        // ubica las personas en las subdivisiones
        linkActual->getSublink().at(index).getPedestriansInSublink().push_back(this);
    }
}
void pedestrian::eleccionGeneralLink() {
   // Configurar el generador de números aleatorios
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis(0.0, 1.0);
    // Generar un número aleatorio en el rango [0.0, 1.0)
    const double randomNumber = dis(gen);
    // compara el numero aletorio con optima choice rate
    // este ultimo debe ir descendiendo cuando halla mas simulaciones
    // a mayor simulaciones mas uso de la elecion sarsa
    switch (randomNumber <= tiempo::get()->getRandomChoiceRate() ? 1 : 2) {
        case 1:
            eleccionRandomLink();
            break;
        case 2:
            eleccionSarsaLink();
            break;
    }
}
void pedestrian::eleccionRandomLink() {
    /* La persona esta en una interseccion y tiene multiples opciones para elegir una calle.
        segun aletoriedad se decide cual sera la calle a tomar y se guardará en linkActual.*/
    // Algoritmo Motor Mersenne Twister
    static std::random_device rd;
    static std::mt19937 generador(rd());
    // linkConnection del nodo de inicio 
    const std::vector<link*> linkConnection = nodeInicio->getLinkConnection();
    const int limite_max = linkConnection.size() - 1 ;
    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<size_t> distribucion(0, limite_max);
    // eleccion de una calle de forma aletoria
    const size_t numero_aleatorio = distribucion(generador);
    // eleccion de la calle nueva, parte principal de la funcion
    setLinkActual(linkConnection.at(numero_aleatorio));
    // agrega persona a la calle
    linkActual->getPedestriansLink().push_back(this);
    // enviando informacion de action al stateMatrix
    // puntero al Qcurrent
    QCurrent = &QsActual->at(numero_aleatorio); 
    // sabiendo la calle defino el nodo final.
    calcularNodeFinal();
}
void pedestrian::eleccionSarsaLink() {
    // busca el elemento mayor de Qs Actual
    auto it = std::max_element(QsActual->begin(), QsActual->end());
    // encuentra el indice del elemento
    size_t iQmenor = std::distance(QsActual->begin(), it);
    // eleccion de la calle nueva, parte principal de la funcion
    setLinkActual(nodeInicio->getLinkConnection().at(iQmenor));
    // agrega persona a la calle
    linkActual->getPedestriansLink().push_back(this);
    // enviando informacion de action al stateMatrix
    // puntero al Qcurrent
    QCurrent = &QsActual->at(iQmenor); 
    // contando persona que experimenta state y action
    // sabiendo la calle defino el nodo final.
    calcularNodeFinal();
}
// void pedestrian::eleccionDosCallesContinuas() {
//     // linkActual es la calle a punto de cambiar
//     if (!(nodeInicio->getLinkConnection().at(0)->getIdLink() == linkActual->getIdLink())) {
//         // setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(0)));
//         // setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(0)).get());
//         setLinkActual(nodeInicio->getLinkConnection().at(0));
//         // enviando informacion de action al stateMatrix
//         stateMatrixPedestrian.getActionValue().setILinkConnection(0);
//         stateMatrixPedestrian.getActionValue().setIdLink(linkActual->getIdLink());
//         // sabiendo la calle defino el nodo final.
//         calcularNodeFinal();
//         // verificar si el nodo final es un nodo de evacucion.
//         verificarPedestrianEvacuation();
//     }
//     else {
//         // setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(1)));
//         // setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(1)).get());
//         setLinkActual(nodeInicio->getLinkConnection().at(0));
//         // enviando informacion de action al stateMatrix
//         stateMatrixPedestrian.getActionValue().setILinkConnection(1);
//         stateMatrixPedestrian.getActionValue().setIdLink(linkActual->getIdLink());
//         // sabiendo la calle defino el nodo final.
//         calcularNodeFinal();
//         // verificar si el nodo final es un nodo de evacucion.
//         verificarPedestrianEvacuation();
//     }
// }
bool pedestrian::verificarEndLink() {
    // Da verdadero si la persona se encuentra ubicada en el termino de calle.
    bool terminoLink = false;
    if (position.getX()*std::copysign(1, direccionPedestrian.getX()) >= nodeFinal->getCoordenada().getX()*std::copysign(1, direccionPedestrian.getX()) and
    position.getY()*std::copysign(1, direccionPedestrian.getY()) >= nodeFinal->getCoordenada().getY()*std::copysign(1, direccionPedestrian.getY())){
        terminoLink = true;
    }
    return terminoLink;
}
void pedestrian::calcularNodeFinal() {
    /* busqueda del node final segun la calle que se encuentre
        cada calle tiene un nodo de inicio y final depeendiendo
        si esta de ida o vuelta delvolvera el nodo final esto seria ida */
    if(nodeInicio->getIdNode() == linkActual->getNode1()->getIdNode()){
        // setNodeFinal(nodes::get()->getDbNodeTotal().at(linkActual->getIdNode2()).get());
        setNodeFinal(const_cast<node*>(linkActual->getNode2()));
    }
    // esto seria vuelta
    else {
        setNodeFinal(const_cast<node*>(linkActual->getNode1()));
    }
}
int pedestrian::calcularSignoNumero(double numero) {
    if (numero >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}
void pedestrian::cambioCalle() {
    /* se cambia de calle cuando se termina de recorre la calle actual*/
    if (verificarEndLink()) {
        // guarda la interseccion actual antes que sea cambiada, por tanto es la interseccion anterior
        setNodeInicioAnterior(nodeInicio);
        // guarda calle actual antes que sea cambiada, por tanto es la calle anterior
        setLinkPasado(linkActual);
        // busca y elimina esta persona en la calle pasada, porque esta a punto de estar en una calle nueva
        std::vector<pedestrian*>& pedestrianLink = linkPasado->getPedestriansLink();
        pedestrianLink.erase(std::remove(pedestrianLink.begin(), pedestrianLink.end(), this), pedestrianLink.end());
        // busca y elimina esta persona en la calle pasada, porque esta a punto de estar en una calle nueva
        // std::vector<pedestrian*>& pedestriansInSublink = subDivisionPasada->getPedestriansInSublink();
        // pedestriansInSublink.erase(std::remove(pedestriansInSublink.begin(), pedestriansInSublink.end(), this),pedestriansInSublink.end());

        // guarda el stateMatrix para calculos del algoritmo sarsa.
        // stateMatrixPasado = stateMatrixActual;
        QPrevious = QCurrent;
        // ahora la interseccion final es la interseccion inicial.
        setNodeInicio(nodeFinal);
        // correcion de la posicion cuando se llega cerca al nodo.
        setPosition({nodeInicio->getCoordenada().getX(), nodeInicio->getCoordenada().getY()});
        // calculo del stateMatrix para obtener datos de state.
        calcularLevelDensityAtNode();

        // verificar si el nodo final es un nodo de evacucion.
        verificarPedestrianEvacuation();
        // calculo del reward
        calcularReward();
        // eleccionde de la calle
        eleccionGeneralLink();
        // guarda infomacion de stateMatrix de la persona en una tabla en nodo.
        // stateMatrixtoTableAtNode();
        // algoritmo sarsa, actualiza en nodoAnterior
        algoritmoSarsa();
        // direccion de la persona en la calle.
        calcularDireccionPedestrian();
        // envio informacion de direccion al vector de velocidad.
        getVelocidad().setDireccion(getDireccionPedestrian());
        // falta mejor para que ajuste tambien esta velcoida
        // stateMatrixActual->mostrarStateMatrix();
    }
    else {
        // calculo del reward
        calcularReward();
    }
}
void pedestrian::calcularDireccionPedestrian() {
    setDireccionPedestrian(linkActual->getOrientacionLink() * calcularSignoDireccion());
}
vector2D pedestrian::calcularSignoDireccion() {
    double x = calcularSignoNumero(nodeFinal->getCoordenada().getX() - nodeInicio->getCoordenada().getX());
    double y = calcularSignoNumero(nodeFinal->getCoordenada().getY() - nodeInicio->getCoordenada().getY());
    return vector2D(x,y);
}
void pedestrian::calcularReward() {
    /* calculo del reward por paso*/
    if (evacuado == true) {
        reward += surviveReward;
    }
    else {
        reward += stepReward;
    }
}
void pedestrian::verificarPedestrianEvacuation(){
    /* verifica si el nodoInicio a la cual la persona esta caminado es un nodo de
        evacuacion. Esto cuando cambia de calle y entra a la funcion cambioCalle*/
    if (nodeInicio->getNodeType() == "nodeEvacuation") {
        // si no esta lleno el nodo
        if (!dynamic_cast<nodeEvacuation*>(nodeInicio)->getLleno()) {
            evacuado= true;
            // cuenta las personas evacuadas en cada punto de evacuacion
            dynamic_cast<nodeEvacuation*>(nodeInicio)->sumarPersonasEvacuadas();
            // cuenta el total de personas evacuadas
            nodeEvacuation::sumarTotalPersonasEvacuadas();
        }
        // eliminar la persona evacuada
        // auto& dbPedestrianTotal = pedestrians::get()->getDbPedestrianTotal();
        // auto it = std::find(dbPedestrianTotal.begin(), dbPedestrianTotal.end(), *this);
        // dbPedestrianTotal.erase(it);
    }
}
void pedestrian::algoritmoSarsa() {
    /* nodoInicioAnterior es la interseccion inicial de la calle anterior o justo
        antes que cambia a la nueva calle
        y nodoInicia es la intersecion incial actual empezando en la nueva calle*/
    // R
    sarsaAlgorithm.setR(&reward);
    // QPrevious
    // double QPrevious = stateMatrixPasado->getQsValue().getQsVector().at(stateMatrixPasado->getActionValue().getILinkConnection());
    sarsaAlgorithm.setQPrevious(QPrevious);
    // QCurrent
    // double QCurrent = stateMatrixActual->getQsValue().getQsVector().at(stateMatrixActual->getActionValue().getILinkConnection()); 
    sarsaAlgorithm.setQCurrent(QCurrent);
    // calcular Q
    sarsaAlgorithm.sarsaActualizarQ();
    // stateMatrixPasado->getQsValue().getQsVector().at(stateMatrixPasado->getActionValue().getILinkConnection()) = sarsaAlgorithm.getQPrevious();
    // reinica el reward de la persona
    reward = 0;
}
void pedestrian::calcularLevelDensityAtNode() {
    // obtengo en puntero de stateMatrix del nodo inicial
    std::map<state, stateMatrix*>* stateMatrixTableMap = &(nodeInicio->getStateMatrixTableMap());
    const std::vector<int*> densityLevels = nodeInicio->getDensityLevelNode();
   
    // Usar un bucle for para copiar los valores de los punteros a enteros
    std::vector<int> convertedVector;
    // Reservar memoria para evitar reallocaciones
    convertedVector.reserve(densityLevels.size());
    for (int* ptr : densityLevels) {
        if (ptr) {
            convertedVector.push_back(*ptr);
        }
    }
    // si encuentra un stateMatrix con el estado experimenta en el nodo, entra
    if (stateMatrixTableMap->find(convertedVector) != stateMatrixTableMap->end()) {
        // guarda el vector Qs actual
        QsActual = &stateMatrixTableMap->at(convertedVector)->getQsValue().getQsVector();
    }
    // no encuentro el estado, por tanto lo añado en tabla de estados del nodo
    else {
        // creo el stateMatrix
        stateMatrix* stateMatrixNuevo = new stateMatrix(convertedVector);
        // guarda el vector Qs actual
        QsActual = &stateMatrixNuevo->getQsValue().getQsVector();
        // guardo en el stateMatrix en la tabla de estados del nodo
        stateMatrixTableMap->emplace(convertedVector, stateMatrixNuevo);
    }
}
// void pedestrian::stateMatrixtoTableAtNode() {
//     // Inicializar action en el primer instante. 
//     stateMatrix stateMatrixEncontrado;
//     bool verificarStateMatrix = false;
//     int idq = 0;
//     nodeInicio->buscarStateMatrix(stateMatrixPedestrian, verificarStateMatrix, idq);
//     // si lo encuentra, significa que el estado ya se experimento por tanto no se agrega, se guarda la posicion de la tabla
//     if (verificarStateMatrix) {
//         stateMatrixPedestrian.setIStateMatrixTable(idq);
//     }
//     // no lo encuentra, se agrega el estado y se guarda la posicion de la tabla
//     else {
//         // crea el vector Q segun LinkConnection
//         stateMatrixPedestrian.getQsValue().getQsVector().resize(nodeInicio->getLinkConnection().size(), 0);
//         // crea el vector pedestrianMassState segun linkConnection
//         // stateMatrixPedestrian.getPedestrianMassState().resize(nodeInicio->getLinkConnection().size(), 0);
//         stateMatrixPedestrian.getPedestrianMassState().getPedestrianMassStateVector().resize(nodeInicio->getLinkConnection().size(), 0);
//         stateMatrixPedestrian.mostrarStateMatrix();
//         // agrega el nuevo estado
//         nodeInicio->getStateMatrixTable().push_back(stateMatrixPedestrian);
//         stateMatrixPedestrian.setIStateMatrixTable(nodeInicio->getStateMatrixTable().size()-1);
//     }
// }
void pedestrian::modelamientoPedestrian() {
    // personas que aun no estan evacuadas
    if (!evacuado) {
        int tiempoActual = tiempo::get()->getValorTiempo();
        if (tiempoActual == tiempoInicial) {
            // set la posicion de inicio del pedestrian
            setPosition({nodeInicio->getCoordenada().getX(), nodeInicio->getCoordenada().getY()});
            // calculo del stateMatrix para obtener datos de state.
            calcularLevelDensityAtNode();
            // eleccionde de la calle
            eleccionRandomLink();
            // guarda infomacion de stateMatrix de la persona en una tabla en nodo.
            // stateMatrixtoTableAtNode();
            // direccion de la persona en la calle.
            calcularDireccionPedestrian();
            // envio informacion de direccion al vector de velocidad.
            velocidad.setDireccion(getDireccionPedestrian());
        }
        if (tiempoActual > tiempoInicial) {
            caminar();
            // verifica el termino de la calle y actualiza a una nueva.
            cambioCalle();
        }
    }
}
void pedestrian::mostrarMovimientoPedestrian() const {
    /* muestra la interseccion de partida y final de una calle, cuando
        la persona.*/
    if (tiempo::get()->getValorTiempo() > tiempoInicial) {
        std::cout << idPedestrian << ' ';
        std::cout << std::setw(6) << nodeInicio->getIdNode() << ' ';
        std::cout << "start: ";
        // decimales para imprecion
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(5) << nodeInicio->getCoordenada().getX() << ' ';
        std::cout << std::setw(5) << nodeInicio->getCoordenada().getY() << ' ';
        std::cout << "now: ";
        std::cout << std::setw(5) << position.getX() << " ";
        std::cout << std::setw(5) << position.getY() << " ";
        std::cout << "end: ";
        
        std::cout << std::setw(5) << nodeFinal->getCoordenada().getX() << ' ';
        std::cout << std::setw(5) << nodeFinal->getCoordenada().getY() << ' ';
        // std::cout << std::setw(5) << getReward() << ' ';
        std::cout << std::endl;
        std::cout << *QCurrent;
        std::cout << std::endl;
    }
}
void pedestrian::imprimirPedestrianPosition(fileIO* file) const {
    // if (getEvacuado()) {
    // decimales para guardar en archivos.
    file->getFileFstream() << std::fixed << std::setprecision(2);
    file->getFileFstream() << position.getX() << " ";
    file->getFileFstream() << position.getY() << " ";
    file->getFileFstream() << std::endl;
    // }
}
void pedestrian::imprimirPedestrianVelocity(fileIO* file) const{
    file->getFileFstream() << velocidad.getMagnitud() << " ";
    file->getFileFstream() << std::endl;
}
