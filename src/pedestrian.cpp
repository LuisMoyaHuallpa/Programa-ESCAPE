#include "pedestrian.h"
#include "tiempo.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
pedestrian::pedestrian(int edad, int gender, int hhType, int hhId,node* nodeArranque)
    : idPedestrian(contador++), edad(edad), gender(gender), hhType(hhType), hhId(hhId),
      nodeArranque(nodeArranque), nodeInicio(nullptr), nodeFinal(nullptr), nodeInicioAnterior(nullptr),
      direccionPedestrian(),
      velocidad(), stateMatrixPedestrian(), stateMatrixPedestrianAnterior(), sarsaAlgorithm() {
    setNodeInicio(nodeArranque);
    setTiempoInicial(0);
    // setNodeAnterior(nodeInicio);
    // setEmpezoCaminar(false);
    // setPrimerTiempo(true);
    // setSaltoLink(false);
    setEvacuado(false);
    setReward(0);
    verificarPedestrianEvacuation();
    // setRetorno(0);
    // double x = nodeInicio->getCoordX();
    // double y = nodeInicio->getCoordY();
    // vector2D position(x, y);
    // setPosition(position);
    // eleccionRandomLinkActual();
    // setLinkPasado(linkActual);
    // calcularNodeFinal();
    // calcularOrientacion();
    // velocidad.setOrientacion(orientacion);
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
    (*this).tiempoInicial = tiempoInicial;
}
void pedestrian::setStateMatrixPedestrian(stateMatrix stateMatrixPedestrian) {
    (*this).stateMatrixPedestrian = stateMatrixPedestrian;
}
void pedestrian::setStateMatrixPedestrianAnterior(stateMatrix stateMatrixPedestrianAnterior) {
    (*this).stateMatrixPedestrianAnterior = stateMatrixPedestrianAnterior;
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
int pedestrian::getIdPedestrian() const {
    return idPedestrian;
}
int pedestrian::getEdad() const{
    return edad;
}
int pedestrian::getGender() {
    return gender;
}
int pedestrian::getHHType() const{
    return hhType;
}
int pedestrian::getHHId() const{
    return hhId;
}
vector2D pedestrian::getPosition() {
    return position;
}
const node* pedestrian::getNodeArranque() {
    return nodeArranque;
}
node* pedestrian::getNodeInicio() const{
    return nodeInicio;
}
node* pedestrian::getNodeFinal() {
    return nodeFinal;  
}
node* pedestrian::getNodeInicioAnterior() {
    return nodeInicioAnterior;  
}
link* pedestrian::getLinkActual() {
    return linkActual;
}
link* pedestrian::getLinkPasado() {
    return linkPasado;
}
vector2D pedestrian::getDireccionPedestrian() {
    return direccionPedestrian;
}
vector2DVelocidad& pedestrian::getVelocidad() {
    return velocidad;
}
int pedestrian::getTiempoInicial() {
    return tiempoInicial;
}
stateMatrix& pedestrian::getStateMatrixPedestrian() {
    return stateMatrixPedestrian;
}
stateMatrix& pedestrian::getStateMatrixPedestrianAnterior() {
    return stateMatrixPedestrianAnterior;
}
// vector2D pedestrian::getOrientacionLinkPasado() {
//     return orientacionLinkPasado;
// }

// int pedestrian::getTiempoFinal() {
//     return tiempoFinal;  
// }
// bool pedestrian::getEmpezoCaminar() {
//     return empezoCaminar;
// }
// bool pedestrian::getPrimerTiempo() {
//     return primerTiempo;  
// }
// bool pedestrian::getSaltoLink() {
//     return saltoLink;  
// }
bool pedestrian::getEvacuado() {
    return evacuado;
}
int pedestrian::getReward() {
    return reward;  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrian::caminar() {
    /* formula de desplazamiento*/
    position += velocidad * tiempo::get()->getDeltaT();
}
double pedestrian::calcularIDoubleSublink() {
    /* Calcula la ubicacion de la persona en el array del subLink*/
    // distancia de la persona al nodeInicio de la persona
    // position.mostrarVector();
    // nodes::get()->getDbNodeTotal().at(linkActual->getIdNode1())->getCoordenada().mostrarVector();
    double index_x = position.getX() - nodeInicio->getCoordenada().getX();
    double index_y = position.getY() - nodeInicio->getCoordenada().getY();
    double index_hipo = std::sqrt(std::pow(index_x,2) + pow(index_y, 2)) / static_cast<double>(linkActual->getAnchoDivisiones());
    // if (direccionPedestrian.getX()<0) {
    //     index_hipo = link::numberDivisiones-1-index_hipo;
    // }
    return index_hipo;
}
void pedestrian::contarPedestrianInSublink() {
  /* Cada persona tiene una posicion por lo tanto sabe donde agregar el conteo,
      esto significa que no cuenta en todo las calles, solo en las calles que hay
      personas */
    double index_d = calcularIDoubleSublink();
    int index = std::floor(index_d);
    // verifica si la persona esta en intersecciones, al inicio o final
    if (!(index == 0 or index == link::numberDivisiones)) {
        // convierto index_d a int debido a que quiero los index del vector sublink, y contar
        linkActual->getPedestriansInSublink().at(index)++;
    }
}
void pedestrian::eleccionLinkActual() {
    if (nodeInicio->getStateMatrixTable().size() == 0) {
        std::cout  << "primera "<< std::endl;
        eleccionRandomLinkActual();
    }    // si son dos calle continuas
    // else if (nodeInicio->b) {
    //     eleccionDosCallesContinuas();
    // }
    // existan mas de dos calles para elegir
    else {
        eleccionRandomLinkActual();
        // eleccionRandomSarsa();
    }
}
void pedestrian::eleccionRandomLinkActual() {
    /* La persona esta en una interseccion y tiene multiples opciones para elegir una calle.
        segun aletoriedad se decide cual sera la calle a tomar y se guardará en linkActual.*/
    std::random_device rd;
    // Algoritmo Motor Mersenne Twister
    std::mt19937 generador(rd());
    int limite_max = nodeInicio->getIdLinkConnection().size() - 1 ;
    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<int> distribucion(0, limite_max);
    int numero_aleatorio = distribucion(generador);
    setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(numero_aleatorio)).get());
    // enviando informacion de action al stateMatrix
    stateMatrixPedestrian.getActionValue().setILinkConnection(numero_aleatorio);
    stateMatrixPedestrian.getActionValue().setIdLink(linkActual->getIdLink());
    // sabiendo la calle defino el nodo final.
    calcularNodeFinal();
    // verificar si el nodo final es un nodo de evacucion.
    verificarPedestrianEvacuation();
}
void pedestrian::eleccionDosCallesContinuas() {
    // linkActual es la calle a punto de cambiar
    if (!(nodeInicio->getIdLinkConnection().at(0) == linkActual->getIdLink())) {
        // setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(0)));
        setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(0)).get());
        // enviando informacion de action al stateMatrix
        stateMatrixPedestrian.getActionValue().setILinkConnection(0);
        stateMatrixPedestrian.getActionValue().setIdLink(linkActual->getIdLink());
        // sabiendo la calle defino el nodo final.
        calcularNodeFinal();
        // verificar si el nodo final es un nodo de evacucion.
        verificarPedestrianEvacuation();
    }
    else {
        // setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(1)));
        setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(1)).get());
        // enviando informacion de action al stateMatrix
        getStateMatrixPedestrian().getActionValue().setILinkConnection(1);
        getStateMatrixPedestrian().getActionValue().setIdLink(linkActual->getIdLink());
        // sabiendo la calle defino el nodo final.
        calcularNodeFinal();
        // verificar si el nodo final es un nodo de evacucion.
        verificarPedestrianEvacuation();
    }
}
void pedestrian::eleccionSarsa() {
    // empieza con valores del primer elemento de QsVector
    double Qmenor = nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQsValue().getQsVector().at(0);
    int iQmenor = 0;
    // nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQsValue().mostrarQs();
    for (int i = 0; i < nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQsValue().getQsVector().size(); i++) {
        if (nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQsValue().getQsVector().at(i) > Qmenor) {
            Qmenor= nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQsValue().getQsVector().at(i);
            iQmenor = i;
        }
    }
    // nodeInicio->getStateMatrixTable().at(size_type __n)
    // std::cout << "Qmenor: " << nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQsValue().getQsVector().at(iQmenor) << std::endl;
    // setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(iQmenor)));
    setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(iQmenor)).get());
    // enviando informacion de action al stateMatrix
    getStateMatrixPedestrian().getActionValue().setILinkConnection(iQmenor);
    getStateMatrixPedestrian().getActionValue().setIdLink(linkActual->getIdLink());
    // sabiendo la calle defino el nodo final.
    calcularNodeFinal();
    // verificar si el nodo final es un nodo de evacucion.
    verificarPedestrianEvacuation();
}
void pedestrian::eleccionGeneralLinkActual() {
   // Configurar el generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    // Generar un número aleatorio en el rango [0.0, 1.0)
    double randomNumber = dis(gen);
    // compara el numero aletorio con optima choice rate
    // este ultimo debe ir descendiendo cuando halla mas simulaciones
    // a mayor simulaciones mas uso de la elecion sarsa
    switch (randomNumber <= tiempo::get()->getRandomChoiceRate() ? 1 : 2) {
        case 1:
            eleccionRandomLinkActual();
            break;
        case 2:
            eleccionSarsa();
            break;
    }
}
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
        // guarda el la intersesccional inicial anterior antes que sea cambiada
        setNodeInicioAnterior(nodeInicio);
        // guarda el stateMatrix para calculos del algoritmo sarsa.
        setStateMatrixPedestrianAnterior(stateMatrixPedestrian);
        // ahora la interseccion final es la interseccion inicial.
        setNodeInicio(nodeFinal);
        // correcion de la posicion cuando se llega cerca al nodo.
        setPosition({getNodeInicio()->getCoordenada().getX(), getNodeInicio()->getCoordenada().getY()});
        // calculo del stateMatrix para obtener datos de state.
        calcularLevelDensityAtNode();
        // stateMatrixPedestrian.mostrarStateMatrix();
        // eleccionde de la calle
        // eleccionRandomLinkActual();
        eleccionGeneralLinkActual();
        // eleccionLinkActual();
        // guarda infomacion de stateMatrix de la persona en una tabla en nodo.
        // stateMatrixtoTableAtNode();
        // algoritmo sarsa, actualiza en nodoAnterior
        algoritmoSarsa();
        // direccion de la persona en la calle.
        calcularDireccionPedestrian();
        // envio informacion de direccion al vector de velocidad.
        getVelocidad().setDireccion(getDireccionPedestrian());
        // falta mejor para que ajuste tambien esta velcoida
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
        evacuado= true;
        nodeEvacuation::sumarPersonaEvacuada();
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
    sarsaAlgorithm.setR(reward);
    // QPrevious
    double QPrevious = nodeInicioAnterior->getStateMatrixTable().at(stateMatrixPedestrianAnterior.getIStateMatrixTable()).getQsValue().getQsVector().at(stateMatrixPedestrianAnterior.getActionValue().getILinkConnection());
    sarsaAlgorithm.setQPrevious(QPrevious);
    // QCurrent
    double QCurrent = nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQsValue().getQsVector().at(stateMatrixPedestrian.getActionValue().getILinkConnection());
    sarsaAlgorithm.setQCurrent(QCurrent);
    // calcular Q
    sarsaAlgorithm.sarsaActualizarQ();
    nodeInicioAnterior->getStateMatrixTable().at(stateMatrixPedestrianAnterior.getIStateMatrixTable()).getQsValue().getQsVector().at(stateMatrixPedestrianAnterior.getActionValue().getILinkConnection()) = sarsaAlgorithm.getQPrevious();
    // reinica el reward de la persona
    setReward(0);
}
void pedestrian::calcularLevelDensityAtNode() {
    /* cuando una persona llega a una interseccion debe saber los estados de las
        diferentes calle, esta informacion se enviará a objeto stateMatrix */
    // crear el vector densidad segun el tamaño del LinkConnection de donde nodo donde esta
    stateMatrixPedestrian.getStateValue().getDensityLinks().resize(nodeInicio->getIdLinkConnection().size(), 0);
    // stateMatrixPedestrian.getQsValue().getQsVector().resize(nodeInicio->getIdLinkConnection().size(), 0);
    // ya sabiendo los estados de cada calle, utilizo los de linkConnection y los envio al stateMatrixPedestrian
    for (int i = 0; i < nodeInicio->getIdLinkConnection().size(); i++) {
        stateMatrixPedestrian.getStateValue().getDensityLinks().at(i) = links::get()->getDbLinkTotal().at(nodeInicio->getIdLinkConnection().at(i))->getDensityLevel();
    }
    // con el stateMatrixPedestrian lo busco en la tabla de Q del nodo de Inicio de la nueva calle
    bool verificarStateMatrix = false;
    int idq = 0;
    nodeInicio->buscarStateMatrix(stateMatrixPedestrian, verificarStateMatrix, idq);
    // si lo encuentra, significa que el estado ya se experimento por tanto no se agrega, se guarda la posicion de la tabla
    if (verificarStateMatrix) {
        stateMatrixPedestrian.setIStateMatrixTable(idq);
    }
    // no lo encuentra, se agrega el estado y se guarda la posicion de la tabla
    else {
        // crea el vector Q segun LinkConnection
        stateMatrixPedestrian.getQsValue().getQsVector().resize(nodeInicio->getIdLinkConnection().size(), 0);
        // agrega el nuevo estado
        nodeInicio->getStateMatrixTable().push_back(stateMatrixPedestrian);
        // se setea iStateMatrixTable despues de agregarlo al stateMatrixTable para que cuente bien
        // como lo agrega al final, guarda istateMatrixTable en stateMatrixPedestrian 
        stateMatrixPedestrian.setIStateMatrixTable(nodeInicio->getStateMatrixTable().size()-1);
    }
}
void pedestrian::stateMatrixtoTableAtNode() {
    // Inicializar action en el primer instante. 
    stateMatrix stateMatrixEncontrado;
    bool verificarStateMatrix = false;
    int idq = 0;
    nodeInicio->buscarStateMatrix(stateMatrixPedestrian, verificarStateMatrix, idq);
    // si lo encuentra, significa que el estado ya se experimento por tanto no se agrega, se guarda la posicion de la tabla
    if (verificarStateMatrix) {
        stateMatrixPedestrian.setIStateMatrixTable(idq);
    }
    // no lo encuentra, se agrega el estado y se guarda la posicion de la tabla
    else {
        // crea el vector Q segun LinkConnection
        stateMatrixPedestrian.getQsValue().getQsVector().resize(nodeInicio->getIdLinkConnection().size(), 0);
        // agrega el nuevo estado
        nodeInicio->getStateMatrixTable().push_back(stateMatrixPedestrian);
        stateMatrixPedestrian.setIStateMatrixTable(nodeInicio->getStateMatrixTable().size()-1);
    }
}
void pedestrian::modelamientoPedestrian() {
    // personas que aun no estan evacuadas
    if (!evacuado) {
        if (tiempo::get()->getValorTiempo() == tiempoInicial) {
            // set la posicion de inicio del pedestrian
            setPosition({nodeInicio->getCoordenada().getX(), nodeInicio->getCoordenada().getY()});
            // calculo del stateMatrix para obtener datos de state.
            calcularLevelDensityAtNode();
            // eleccionde de la calle
            eleccionRandomLinkActual();
            // guarda infomacion de stateMatrix de la persona en una tabla en nodo.
            // stateMatrixtoTableAtNode();
            // direccion de la persona en la calle.
            calcularDireccionPedestrian();
            // envio informacion de direccion al vector de velocidad.
            velocidad.setDireccion(getDireccionPedestrian());
        }
        if (tiempo::get()->getValorTiempo() > tiempoInicial) {
            caminar();
            // calculo del reward
            calcularReward();
            // verifica el termino de la calle y actualiza a una nueva.
            cambioCalle();
        }
    }
}
void pedestrian::mostrarMovimientoPedestrian(){
    /* muestra la interseccion de partida y final de una calle, cuando
        la persona.*/
    std::cout << getIdPedestrian() << ' ';
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
}
void pedestrian::imprimirPedestrianPosition(std::fstream& file){
    // if (getEvacuado()) {
    // decimales para guardar en archivos.
    file << std::fixed << std::setprecision(2);
    file << position.getX() << " ";
    file << position.getY() << " ";
    file << std::endl;
    // }
}
void pedestrian::imprimirPedestrianVelocity(std::fstream& file){
    file << velocidad.getMagnitud() << " ";
    file << std::endl;
}
