#include "pedestrian.h"

#include "node.h"
#include "link.h"
#include "sarsa.h"
#include "vector2D.h"
#include "velocidad.h"
#include <vector>

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
pedestrian::pedestrian(const int edad, const int gender, const int hhType, const int hhId, const node* nodeArranque)
    : idPedestrian(contador++),
      edad(edad),
      gender(gender),
      hhType(hhType),
      hhId(hhId),
      nodeArranque(nodeArranque),
      tiempoInicial(0),
      nodeFinalPtr(nullptr),
      direccionPedestrian(),
      velocidadPedestrian(),
      estado(pasivo),
      reward(0),
      tiempoProximaInterseccion(tiempoInicial),
      stateMatrixCurrentPtr(nullptr),
      stateMatrixPreviousPtr(nullptr),
      QCurrentPtr(nullptr),
      QPreviousPtr(nullptr),
      linkCurrentPtr(nullptr),
      linkPreviousPtr(nullptr)
{
    nodeInicioPtr = const_cast<node*>(nodeArranque);
    position = nodeInicioPtr->getCoordenada();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void pedestrian::setPosition(vector2D position) {
//     (*this).position = position;
// }
void pedestrian::setNodeInicio(node* nodeInicio){
    (*this).nodeInicioPtr = nodeInicio;
}
// void pedestrian::setNodeFinal(node* nodeFinal) {
//     (*this).nodeFinal = nodeFinal;
// }
// void pedestrian::setNodeInicioAnterior(node* nodeInicioAnterior) {
//     (*this).nodeInicioAnterior = nodeInicioAnterior;
// }
// void pedestrian::setLinkActual(link* linkActual) {
//     (*this).linkActual = linkActual;
// }
// void pedestrian::setLinkPasado(link *linkPasado) {
//     (*this).linkPasado = linkPasado;
// }
void pedestrian::setDireccionPedestrian(vector2D direccionPedestrian) {
    (*this).direccionPedestrian = direccionPedestrian;
}
// void pedestrian::setVelocidad(vector2DVelocidad velocidad) {
//     (*this).velocidad = velocidad;
// }
void pedestrian::setTiempoInicial(int tiempoInicial) {
    // al iniciar el tiempo de proxima interseccion siempre es el tiempoInicial
    (*this).tiempoInicial = tiempoInicial;
    (*this).tiempoProximaInterseccion = tiempoInicial;
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
const node* pedestrian::getNodeArranque() const {
    return nodeArranque;
}
const int pedestrian::getTiempoInicial() const {
    return tiempoInicial;
}
vector2D pedestrian::getPosition() const{
    return position;
}
node* pedestrian::getNodeInicio() const{
    return nodeInicioPtr;
}
node* pedestrian::getNodeFinal() const {
    return nodeFinalPtr;  
}
vector2D pedestrian::getDireccionPedestrian() const {
    return direccionPedestrian;
}
velocidad pedestrian::getVelocidadPedestrian() const {
    return velocidadPedestrian;
}
estadoPedestrian& pedestrian::getEstado() {
    return estado;
}
int pedestrian::getReward() const {
    return reward;  
}
link* pedestrian::getLinkCurrent() const {
    return linkCurrentPtr;
}
link* pedestrian::getLinkPrevious() const {
    return linkPreviousPtr;
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
    const vector2D velocidad = direccionPedestrian * velocidadPedestrian.getMagnitud();
    position += velocidad * tiempo::get()->getDeltaT();
}
double pedestrian::calcularIDoubleSublink() {
    /* Calcula la ubicacion de la persona en el array del subLink*/
    // distancia de la persona al nodeInicio de la persona
    double index_x = position.getX() - nodeInicioPtr->getCoordenada().getX();
    double index_y = position.getY() - nodeInicioPtr->getCoordenada().getY();
    double index_hipo = std::sqrt(std::pow(index_x,2) + pow(index_y, 2)) / static_cast<double>(linkCurrentPtr->getAnchoSubdivisiones());
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
        linkCurrentPtr->getSublink().at(index).getPedestriansInSublink().push_back(this);
    }
}
link* pedestrian::eleccionGeneralLink() const {
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
            return eleccionRandomLink();
        case 2:
            return eleccionSarsaLink();
    }
    return nullptr;
}
link* pedestrian::eleccionRandomLink() const {
    /* La persona esta en una interseccion y tiene multiples opciones para elegir una calle.
        segun aletoriedad se decide cual sera la calle a tomar y se guardará en linkActual.*/
    // Algoritmo Motor Mersenne Twister
    static std::random_device rd;
    static std::mt19937 generador(rd());
    // linkConnection del nodo de inicio 
    const std::vector<link*> linkConnection = nodeInicioPtr->getLinkConnectionsPtr();
    const int limite_max = linkConnection.size() - 1 ;
    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<size_t> distribucion(0, limite_max);
    // eleccion de una calle de forma aletoria
    const size_t numero_aleatorio = distribucion(generador);
    // eleccion de la calle nueva, parte principal de la funcion
    return linkConnection.at(numero_aleatorio);
}
link* pedestrian::eleccionSarsaLink() const {
    // busca el elemento mayor de Q del stateMatrix experimentado
    const Q* Qmax = stateMatrixCurrentPtr->buscarQMax();
    return const_cast<link*>(Qmax->getCallePtr());

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
    if (position.getX()*std::copysign(1, direccionPedestrian.getX()) >= nodeFinalPtr->getCoordenada().getX()*std::copysign(1, direccionPedestrian.getX()) and
    position.getY()*std::copysign(1, direccionPedestrian.getY()) >= nodeFinalPtr->getCoordenada().getY()*std::copysign(1, direccionPedestrian.getY())){
        terminoLink = true;
    }
    return terminoLink;
}
int pedestrian::calcularSignoNumero(double numero) {
    if (numero >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}
void pedestrian::calcularDireccionPedestrian() {
    setDireccionPedestrian(linkCurrentPtr->getOrientacionLink() * calcularSignoDireccion());
}
vector2D pedestrian::calcularSignoDireccion() {
    double x = calcularSignoNumero(nodeFinalPtr->getCoordenada().getX() - nodeInicioPtr->getCoordenada().getX());
    double y = calcularSignoNumero(nodeFinalPtr->getCoordenada().getY() - nodeInicioPtr->getCoordenada().getY());
    return vector2D(x,y);
}
int pedestrian::calcularReward() const {
    /* calculo del reward por paso*/
    switch (estado) {
        case evacuando:
        {
            const int tiempoDesplazamiento = calcularTiempoDesplazamiento();
            const int pasos = tiempoDesplazamiento / tiempo::get()->getDeltaT();
            return pasos * stepReward;
        }
        case evacuado:
            return surviveReward;
        case muerto:
            return deadReward;
        default:
            std::cout << "Estado: Desconocido" << std::endl;
            break;
    }
    return 0;
}
int pedestrian::calcularTiempoDesplazamiento() const {
    /* calcula el proximo tiempo donde el pedestrian estará en una interseccion*/
    nodeInicioPtr->mostrarNode();
    nodeFinalPtr->mostrarNode();
    const double distancia = nodeFinalPtr->calcularDistanciaA(nodeInicioPtr);
    return distancia/velocidadPedestrian.getMagnitud();
}
void pedestrian::algoritmoSarsa() {
    // /* nodoInicioAnterior es la interseccion inicial de la calle anterior o justo
    //     antes que cambia a la nueva calle
    //     y nodoInicia es la intersecion incial actual empezando en la nueva calle*/
    // // R
    // sarsaAlgorithm.setR(&reward);
    // // QPrevious
    // // double QPrevious = stateMatrixPasado->getQsValue().getQsVector().at(stateMatrixPasado->getActionValue().getILinkConnection());
    // sarsaAlgorithm.setQPrevious(QPrevious);
    // // QCurrent
    // // double QCurrent = stateMatrixActual->getQsValue().getQsVector().at(stateMatrixActual->getActionValue().getILinkConnection()); 
    // sarsaAlgorithm.setQCurrent(QCurrent);
    // // calcular Q
    // sarsaAlgorithm.sarsaActualizarQ();
    // // stateMatrixPasado->getQsValue().getQsVector().at(stateMatrixPasado->getActionValue().getILinkConnection()) = sarsaAlgorithm.getQPrevious();
    // // reinica el reward de la persona
    // reward = 0;
}
void pedestrian::modelamientoPedestrian() {
    const int tiempoActual = tiempo::get()->getValorTiempo();
    std::cout << tiempoActual << std::endl;
    // cuando la persona esta en pasivo, cambia el estado a evacuado cuando llegue su tiempo de salida
    if (estado == pasivo && tiempoInicial == tiempoActual) {
        estado = evacuando;
    }
    // realiza el movimiento solo cuando esta evacuando
    if (estado == evacuando) {
        // modelamiento cuando la persona esta en una interseccion
        if(tiempoProximaInterseccion ==  tiempoActual){
            // verifico si estoy en un punto de evacuacion
            estado = nodeInicioPtr->verificarNodoEvacuation();
            // si no ha evacuado realizar lo siguiente
            if(estado == evacuando){
                // si fuera un tiempo diferente al inicial, guardar lo presente en lo pasado
                if(!(tiempoInicial == tiempoActual)){
                    // reinicia el valor del reward
                    reward = 0;
                    // guarda calle actual antes que sea cambiado
                    linkPreviousPtr =  linkCurrentPtr;
                    // guarda el Qcurents antes que sea cambiado
                    QPreviousPtr = QCurrentPtr;
                    // busca y elimina esta persona en la calle pasada, porque esta a punto de estar en una calle nueva
                    std::vector<pedestrian*>& pedestrianLink = linkCurrentPtr->getPedestriansLinkPtr();
                    pedestrianLink.erase(std::remove(pedestrianLink.begin(), pedestrianLink.end(), this), pedestrianLink.end());
                    // busca y elimina esta persona en la calle pasada, porque esta a punto de estar en una calle nueva
                    // ahora la interseccion final es la interseccion inicial.
                    nodeInicioPtr = nodeFinalPtr;
                    // correcion de la posicion cuando se llega cerca al nodo.
                    position = {nodeInicioPtr->getCoordenada().getX(), nodeInicioPtr->getCoordenada().getY()};
                }
                // observa el estado del nodo
                const std::vector<int> stateObservado = nodeInicioPtr->stateObservado();
                // obtener stateMatrix
                stateMatrixCurrentPtr = stateMatrix::creacionObtencionStateMatrix(nodeInicioPtr, stateObservado);
                // eleccion de la calle
                linkCurrentPtr = eleccionGeneralLink();
                // obtener nodo final
                nodeFinalPtr = const_cast<node*>(nodeInicioPtr->buscarNodoFinal(linkCurrentPtr));
                // calcula el proximo tiempo en que la persona estara en una interseccion
                // por ahora no actualiza la velocidad
                tiempoProximaInterseccion += calcularTiempoDesplazamiento();
                // obtener Qcurrent
                QCurrentPtr = stateMatrixCurrentPtr->buscarQ(linkCurrentPtr);
                // excepto al iniciar
                if(!(tiempoInicial == tiempoActual)){
                    // calculo de reward
                    reward += calcularReward();
                    // algoritmo sarsa, actualiza en nodoAnterior
                    std::cout << "Qprevious: " << *(QPreviousPtr->getValor()) << std::endl;
                    std::cout << "Qcurrent: " << *(QCurrentPtr->getValor()) << std::endl;
                    // sarsa::sarsaActualizarQ(QPrevious->getValor(), QCurrent->getValor(), reward);
                }
                // direccion de la persona en la calle.
                calcularDireccionPedestrian();
                // envio informacion de direccion al vector de velocidad.
                // getVelocidadPedestrian().setDireccion(getDireccionPedestrian());
            }
        }
        // modelamiento cuando la persona esta dentro de la calle
        else {
            caminar();    
        }
    }
}
void pedestrian::mostrarMovimientoPedestrian() const {
    /* muestra la interseccion de partida y final de una calle, cuando
        la persona.*/
    if (estado == evacuando) {
        std::cout << idPedestrian << ' ';
        std::cout << std::setw(6) << nodeInicioPtr->getIdNode() << ' ';
        std::cout << "start: ";
        // decimales para imprecion
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(5) << nodeInicioPtr->getCoordenada().getX() << ' ';
        std::cout << std::setw(5) << nodeInicioPtr->getCoordenada().getY() << ' ';
        std::cout << "now: ";
        std::cout << std::setw(5) << position.getX() << " ";
        std::cout << std::setw(5) << position.getY() << " ";
        std::cout << "end: ";
        
        std::cout << std::setw(5) << nodeFinalPtr->getCoordenada().getX() << ' ';
        std::cout << std::setw(5) << nodeFinalPtr->getCoordenada().getY() << ' ';
        std::cout << std::setw(5) << getReward() << ' ';
        std::cout << std::endl;
        // std::cout << QCurrent->getValor();
        std::cout << std::endl;
    }
}
void pedestrian::mostrarPedestrian() const {
    std::cout << idPedestrian << ' ';
    std::cout << nodeInicioPtr->getIdNode() << ' ';
    std::cout << "ti: " << tiempoInicial;
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
    file->getFileFstream() << velocidadPedestrian.getMagnitud() << " ";
    file->getFileFstream() << std::endl;
}
