#include "pedestrian.h"

#include "node.h"
#include "link.h"
#include "nodeEvacuation.h"
#include "sarsa.h"
#include "stateMatrix.h"
#include "stateMatrixs.h"
#include "tiempo.h"
#include "vector2D.h"
#include "velocidad.h"
#include <iostream>
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int pedestrian::contador = 1;
const int pedestrian::meanRayleigh = std::get<int>(dictionary::get()->lookup("meanRayleigh"));
const int pedestrian::surviveReward = 100000;
const int pedestrian::deadReward = -1000; 
const int pedestrian::stepReward = -1;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrian::pedestrian(const int edad, const int gender, const int hhType, const int hhId, node* nodeArranque)
    : idPedestrian(contador++),
      edad(edad),
      gender(gender),
      hhType(hhType),
      hhId(hhId),
      nodeArranque(nodeArranque),
      tiempoInicial(calcularRayleighDistribution(calcularScaleRayleigh())),
      position(nodeArranque->getCoordenada()),
      nodeInicioPtr(nodeArranque),
      nodeFinalPtr(nullptr),
      direccionPedestrian(),
      velocidadPedestrian(),
      estadoPedestrian(pasivo),
      reward(0),
      tiempoAnteriorInterseccion(0),
      interseccion(true),
      stateMatrixCurrentPtr(nullptr),
      QCurrentPtr(nullptr),
      QPreviousPtr(nullptr),
      linkCurrentPtr(nullptr)
{
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
void pedestrian::setVelocidadPedestrian(double velocidadPedestrian) {
    (*this).velocidadPedestrian.setMagnitud(velocidadPedestrian);
}
void pedestrian::setEstadoPedestrian(estado estadoPedestrian) {
    (*this).estadoPedestrian = estadoPedestrian;
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
void pedestrian::setInterseccion(bool interseccion) {
    (*this).interseccion = interseccion;
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
velocidad& pedestrian::getVelocidadPedestrian() {
    return velocidadPedestrian;
}
estado& pedestrian::getEstadoPedestrian() {
    return estadoPedestrian;
}
int pedestrian::getReward() const {
    return reward;  
}
int pedestrian::getTiempoAnteriorInterseccion() const{
    return tiempoAnteriorInterseccion;
}
bool pedestrian::getInterseccion() const {
    return interseccion;    
}
link* pedestrian::getLinkCurrent() const {
    return linkCurrentPtr;
}
stateMatrix *pedestrian::getStateMatrixCurrent() const {
    return stateMatrixCurrentPtr;    
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
double pedestrian::calcularIdSublink() {
    /* Calcula la ubicacion de la persona en el array del subLink*/
    // distancia de la persona al nodeInicio de la persona
    // double index_x = position.getX() - nodeInicioPtr->getCoordenada().getX();
    const double index_x = position.getX() - linkCurrentPtr->getNode1Ptr()->getCoordenada().getX();
    // double index_y = position.getY() - nodeInicioPtr->getCoordenada().getY();
    const double index_y = position.getY() - linkCurrentPtr->getNode1Ptr()->getCoordenada().getY();
    int index_hipo = std::sqrt(std::pow(index_x,2) + pow(index_y, 2)) / linkCurrentPtr->getAnchoSubdivisiones();
    if (index_hipo>= 10) {
        index_hipo=9;    
    }
    return index_hipo;
}
// bool pedestrian::verificarEndLink() const {
//     // Da verdadero si la persona se encuentra ubicada en el termino de calle.
//     bool terminoLink = false;
//     if (position.getX()*std::copysign(1, direccionPedestrian.getX()) >= nodeFinalPtr->getCoordenada().getX()*std::copysign(1, direccionPedestrian.getX()) and
//     position.getY()*std::copysign(1, direccionPedestrian.getY()) >= nodeFinalPtr->getCoordenada().getY()*std::copysign(1, direccionPedestrian.getY())){
//         terminoLink = true;
//     }
//     return terminoLink;
// }
bool pedestrian::verificarEndLink() const {
    // Calcula la distancia euclidiana entre las coordenadas actuales y el punto objetivo
    const double umbral = velocidadPedestrian.getMagnitud();
    const double distancia = std::sqrt(std::pow(position.getX() - nodeFinalPtr->getCoordenada().getX(), 2) + std::pow(position.getY() - nodeFinalPtr->getCoordenada().getY(), 2));
    // Verifica si la distancia es menor o igual al umbral
    return distancia <= umbral;
}
int pedestrian::calcularIdEndSublink() const {
    /* Permite saber cual es el ultimo sublink*/
    // averguio si estoy al final o al inicio
    if (nodeInicioPtr == linkCurrentPtr->getNode1Ptr()) {
        // si estoy al inicio es el ultimo subdivione
        return linkCurrentPtr->getSubdiviones().size() - 1; 
    } 
    // esta al inicio
    else {
        return 0;
    }
}
link* pedestrian::eleccionGeneralLink() const {
    // la primera eleccion debe ser random
    if (tiempo::get()->getValorTiempo() == tiempoInicial and std::get<std::string>(dictionary::get()->lookupDefault("sarsaProcesses")) == "calibration") {
        return eleccionRandomLink();
    }
    if (estadoPedestrian == evacuado) {
        return nullptr;
    }
    // Configurar el generador de números aleatorios
    else {
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
int pedestrian::calcularSignoNumero(double numero) {
    if (numero >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}
void pedestrian::calcularDireccionPedestrian() {
    direccionPedestrian = linkCurrentPtr->getOrientacionLink() * calcularSignoDireccion();
}
vector2D pedestrian::calcularSignoDireccion() {
    double x = calcularSignoNumero(nodeFinalPtr->getCoordenada().getX() - nodeInicioPtr->getCoordenada().getX());
    double y = calcularSignoNumero(nodeFinalPtr->getCoordenada().getY() - nodeInicioPtr->getCoordenada().getY());
    return vector2D(x,y);
}
int pedestrian::calcularReward() const {
    /* calculo del reward por paso*/
    const int tiempoDesplazamiento = calcularTiempoDesplazamiento();
    const int pasos = tiempoDesplazamiento / tiempo::get()->getDeltaT();
    return pasos * stepReward;
}
int pedestrian::calcularTiempoDesplazamiento() const {
   /* calcula el proximo tiempo donde el pedestrian estará en una interseccion*/
    const int tiempoDesplazado = tiempo::get()->getValorTiempo() - tiempoAnteriorInterseccion;
    return  tiempoDesplazado;
}
void pedestrian::modelamientoPedestrian() {
    if(!(estadoPedestrian == evacuado)){
        const int tiempoActual = tiempo::get()->getValorTiempo();
        // cuando la persona esta en pasivo, cambia el estado a evacuado cuando llegue su tiempo de salida
        if (estadoPedestrian == pasivo && tiempoInicial == tiempoActual) {
            estadoPedestrian = evacuando;
        }
        // realiza el movimiento solo cuando esta evacuando
        if (estadoPedestrian == evacuando or estadoPedestrian==evacuado) {
                // modelamiento cuando la persona esta en una interseccion
            if (interseccion) {
                // si no ha evacuado realizar lo siguiente
                // si fuera un tiempo diferente al inicial, guardar lo presente en lo pasado
                if(!(tiempoInicial == tiempoActual)){
                    // reinicia el valor del reward
                    reward = 0;
                    // elimina esta persona en la calle pasada, porque esta a punto de estar en una calle nueva
                    // linkCurrentPtr->quitarPedestrian(this);
                    // guarda calle actual antes que sea cambiado
                    // linkPreviousPtr =  linkCurrentPtr;
                    // guarda el Qcurents antes que sea cambiado
                    stateMatrixPreviousPtr = stateMatrixCurrentPtr;
                    QPreviousPtr = QCurrentPtr;
                    // ahora la interseccion final es la interseccion inicial.
                    nodeInicioPtr = nodeFinalPtr;
                    // correcion de la posicion cuando se llega cerca al nodo.
                    position = {nodeInicioPtr->getCoordenada().getX(), nodeInicioPtr->getCoordenada().getY()};
                    // verifico si estoy en un punto de evacuacion
                }
                // nodeInicioPtr->mostrarNode();
                estadoPedestrian = nodeInicioPtr->estadoPedestrianEnNodo();
                // observa el estado del nodo o nodeEvacuation
                const std::vector<int> stateObservado = nodeInicioPtr->stateObservado();
                // obtener stateMatrix
                stateMatrixCurrentPtr = stateMatrix::creacionObtencionStateMatrix(nodeInicioPtr, stateObservado);
               // stateMatrixCurrentPtr->mostrarStateMatrix();
                // eleccion de la calle
                linkCurrentPtr = eleccionGeneralLink();
                if (estadoPedestrian == evacuando) {
                    // // agrego a la personas en la calle
                    // linkCurrentPtr->agregarPedestrian(this);
                    // obtener nodo final
                    nodeFinalPtr = const_cast<node*>(nodeInicioPtr->buscarNodoFinal(linkCurrentPtr));
                    // direccion de la persona en la calle.
                    calcularDireccionPedestrian();
                    // calcular idEndSublink
                    idEndSublink = calcularIdEndSublink();
                }
                // obtener Qcurrent
                QCurrentPtr = stateMatrixCurrentPtr->buscarQ(linkCurrentPtr);
                // aumentar observacion
                QCurrentPtr->aumentar1Observacion();
                // excepto al iniciar
                if (estadoPedestrian == evacuado) {
                    dynamic_cast<nodeEvacuation*>(nodeInicioPtr)->contabilizarPersona(this);
                }

                if (std::get<std::string>(dictionary::get()->lookupDefault("sarsaProcesses")) == "calibration"){
                    if(!(tiempoInicial == tiempoActual)){
                        // std::cout << "current: " << std::endl;
                        // stateMatrixCurrentPtr->mostrarStateMatrix();
                        // std::cout << "previous: " << std::endl;
                        // stateMatrixPreviousPtr->mostrarStateMatrix();

                        reward = calcularReward();
                        sarsa::sarsaActualizarQ(QPreviousPtr->getValor(), QCurrentPtr->getValor(), reward);
                        // std::cout << "previous: " << std::endl;
                        // stateMatrixPreviousPtr->mostrarStateMatrix();
                    }
                }
                // guarda la anteror interseccion
                tiempoAnteriorInterseccion = tiempoActual;
                // paso a la calle
                interseccion=false;
            }
            else {
                // modelamiento cuando la persona esta dentro de la calle
                if (estadoPedestrian == evacuando) {
                    // camina la persona
                    velocidadPedestrian.calcularAjusteRandom();
                    caminar();    
                   // calcula posicion en subdivion 
                    const int idSublink = calcularIdSublink();
                    // agrega persona en sublink
                    linkCurrentPtr->agregarPedestrianSublink(this, idSublink);
                    // cuando esta en un sublink cercano a nodoFinal
                    if (idSublink == idEndSublink) {
                        // verifica cuando esta cerca a una interseccion
                        interseccion = verificarEndLink();
                    }
                }
            }
        }
    }
}
void pedestrian::reiniciar() {
    /* reiniciar valores para proxima simulacion*/
    nodeInicioPtr = const_cast<node*>(nodeArranque);
    position = nodeInicioPtr->getCoordenada();
    estadoPedestrian = pasivo;
    interseccion = true;
    // reward = 0;
}
void pedestrian::mostrarMovimientoPedestrian() const {
    /* muestra la interseccion de partida y final de una calle, cuando
        la persona.*/
    if (estadoPedestrian == evacuando or estadoPedestrian== evacuado) {
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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const double pedestrian::calcularScaleRayleigh() {
    return static_cast<double>(meanRayleigh) * std::pow((2.0/M_PI), 0.5);
}
double generate_uniform_random(std::mt19937& gen) {
    // Generar un número aleatorio uniforme en el rango (0, 1)
    return std::generate_canonical<double, std::numeric_limits<double>::digits>(gen);
}
double pedestrian::calcularRayleighDistribution(const double sigma) {
    /* calcula un numero segun la distribucion rayliegh, como parametro necesita
        la variable sigma que es la scaleRayleigh */
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generar un número aleatorio uniforme
    double u = generate_uniform_random(gen);
    // Calcular el número aleatorio según la distribución Rayleigh
    return sigma * std::sqrt(-2.0 * std::log(1.0 - u));
}
