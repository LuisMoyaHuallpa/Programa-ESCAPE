#include "pedestrian.h"
#include "nodeEvacution.h"
#include "stateActionQ.h"
#include "sarsa.h"
#include "state.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <vector>

const int pedestrian::surviveReward = 100000;
const int pedestrian::deadReward = -1000; 
const int pedestrian::stepReward = -1;
int pedestrian::contador = 1;

pedestrian::pedestrian() : nodeInicio () {
    (*this).idPedestrian = 0;
    (*this).edad = 0;
    (*this).hhType = 0;
   (*this).hhId = 0;
}
pedestrian::pedestrian(int edad, int gender, int hhType, int hhId, node* nodeInicio) : sarsaAlgorithm() {
    setIdPedestrian(contador++);
    setEdad(edad);
    setGender(gender);
    setHHType(hhType);
    setHHId(hhId);
    setNodeInicio(nodeInicio);
    // setNodeAnterior(nodeInicio);
    setEmpezoCaminar(false);
    setPrimerTiempo(true);
    setSaltoLink(false);
    setEvacuado(false);
    setRetorno(0);
    double x = nodeInicio->getCoordX();
    double y = nodeInicio->getCoordY();
    vector2D position(x, y);
    setPosition(position);
    eleccionRandomLinkActual();
    setLinkPasado(linkActual);
    calcularNodeFinal();
    calcularOrientacion();
    velocidad.setOrientacion(orientacion);
    qStateAction = new stateActionQ;
    // qStateAction->setA(linkActual->getIdLink());
    // qStateAction->setS(calcularLevelDensityLinks());
}

void pedestrian::setIdPedestrian(int id){
    (*this).idPedestrian = id;
}
void pedestrian::setEdad(int edad){
    (*this).edad = edad;
}
void pedestrian::setGender(int gender) {
    (*this).gender = gender;  
}
void pedestrian::setHHType(int hhType){
    (*this).hhType = hhType;
}
void pedestrian::setHHId(int hhId){
    (*this).hhId = hhId;
}
void pedestrian::setNodeInicio(node* nodeInicio){
    (*this).nodeInicio = nodeInicio;
}
void pedestrian::setNodeFinal(node* nodeFinal) {
    (*this).nodeFinal = nodeFinal;
}
// void pedestrian::setNodeAnterior(node* nodeAnterior) {
//     (*this).nodeAnterior = nodeAnterior;
// }
void pedestrian::setPosition(vector2D position) {
    (*this).position = position;
}
void pedestrian::setLinkActual(link *linkActual) {
    (*this).linkActual = linkActual;
}
void pedestrian::setLinkPasado(link *linkPasado) {
    (*this).linkPasado = linkPasado;
}
void pedestrian::setqStateAction(stateActionQ* qStateAction) {
    (*this).qStateAction = qStateAction;
}
void pedestrian::setOrientacion(vector2D orientacion) {
    (*this).orientacion = orientacion;
}
void pedestrian::setOrientacionLinkPasado(vector2D orientacionLinkPasado) {
    (*this).orientacionLinkPasado = orientacionLinkPasado;
}
void pedestrian::setVelocidad(vector2DVelocidad velocidad) {
    (*this).velocidad = velocidad;
}
void pedestrian::setTiempoInicial(int tiempoInicial) {
    (*this).tiempoInicial = tiempoInicial;
}
void pedestrian::setTiempoFinal(int tiempoFinal) {
    (*this).tiempoFinal = tiempoFinal;
}
void pedestrian::setEmpezoCaminar(bool empezoCaminar) {
    (*this).empezoCaminar = empezoCaminar;
}
void pedestrian::setPrimerTiempo(bool primerTiempo) {
    (*this).primerTiempo = primerTiempo;
}
void pedestrian::setSaltoLink(bool saltoLink) {
    (*this).saltoLink = saltoLink;
}
void pedestrian::setRetorno(int retorno) {
    (*this).retorno = retorno;
}
void pedestrian::setEvacuado(bool evacuado) {
    (*this).evacuado = evacuado;
}

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
node* pedestrian::getNodeInicio() const{
    return nodeInicio;
}
node* pedestrian::getNodeFinal() {
    return nodeFinal;  
}
// node* pedestrian::getNodeAnterior() {
//     return nodeAnterior;  
// }
vector2D pedestrian::getPosition() {
    return position;
}
link* pedestrian::getLinkActual() {
    return linkActual;
}
link* pedestrian::getLinkPasado() {
    return linkPasado;
}
stateActionQ* pedestrian::getqStateAction() {
    return qStateAction;
}
vector2D pedestrian::getOrientacion() {
    return orientacion;
}
vector2D pedestrian::getOrientacionLinkPasado() {
    return orientacionLinkPasado;
}
vector2DVelocidad pedestrian::getVelocidad() {
    return velocidad;
}
int pedestrian::getTiempoInicial() {
    return tiempoInicial;
}
int pedestrian::getTiempoFinal() {
    return tiempoFinal;  
}
bool pedestrian::getEmpezoCaminar() {
    return empezoCaminar;
}
bool pedestrian::getPrimerTiempo() {
    return primerTiempo;  
}
bool pedestrian::getSaltoLink() {
    return saltoLink;  
}
int pedestrian::getRetorno() {
    return retorno;  
}
bool pedestrian::getEvacuado() {
    return evacuado;
}

void pedestrian::mostrarPedestrian(){
    std::cout << getIdPedestrian() << ' ';
    std::cout << std::setw(6) << getNodeInicio()->getIdNode() << ' ';
    std::cout << "start: ";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(5) << getNodeInicio()->getCoordX() << ' ';
    std::cout << std::setw(5) << getNodeInicio()->getCoordY() << ' ';
    std::cout << "now: ";
    std::cout << std::setw(5) << getPosition().getX() << " ";
    std::cout << std::setw(5) << getPosition().getY() << " ";
    std::cout << "end: ";
    std::cout << std::setw(5) << getNodeFinal()->getCoordX() << ' ';
    std::cout << std::setw(5) << getNodeFinal()->getCoordY() << ' ';
    std::cout << std::setw(5) << getRetorno() << ' ';
    std::cout << std::endl;
}
void pedestrian::imprimirPedestrianPosition(std::fstream& file){
    file << getPosition().getX() << " ";
    file << getPosition().getY() << " ";
    file << std::endl;
}
void pedestrian::imprimirPedestrianVelocity(std::fstream& file){
    file << getVelocidad().getMagnitud() << " ";
    file << std::endl;
}
void pedestrian::caminar() {
    position += velocidad * tiempo::deltaTiempo;
}
void pedestrian::eleccionRandomLinkActual() {
    // Obtener una semilla aleatoria del hardware
    std::random_device rd;
    // Algoritmo Motor Mersenne Twister
    std::mt19937 generador(rd());
    int limite_max = nodeInicio->getLinkConnection().size() - 1 ;
    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<int> distribucion(0, limite_max);
    int numero_aleatorio = distribucion(generador);
    link* linkSeleccionado = getNodeInicio()->getLinkConnection().at(numero_aleatorio);
    setLinkActual(linkSeleccionado);
}
int pedestrian::iEleccionRandomLinkActual() {
    // Eleccion de la calle de los posibles de la variables LinkConnection
    // cuando se esta en una intersección.
    // Obtener una semilla aleatoria del hardware
    std::random_device rd;
    // Algoritmo Motor Mersenne Twister
    std::mt19937 generador(rd());
    int limite_max = nodeInicio->getLinkConnection().size() - 1 ;
    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<int> distribucion(0, limite_max);
    // int numero_aleatorio = distribucion(generador);
    return distribucion(generador);
}
void pedestrian::updateLinkActual(int iLinkConnection) {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // iLinkConnection          |-->| POSICION EN EL ARREGLO linkConection
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Actualizar la calle o linkActual, que es la calle por donde ira la persona. 
    link* linkSeleccionado = getNodeInicio()->getLinkConnection().at(iLinkConnection);
    setLinkActual(linkSeleccionado);
}
void pedestrian::updateStateAction(int iLinkConnection) {
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // iLinkConnection          |-->| POSICION EN EL ARREGLO linkConection
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Crear la action con idLink y iLinkConnection
    action a(linkActual->getIdLink(), iLinkConnection);
    qStateAction->setA(a);
}
// Eleccion del caminar mas recomendable 
void pedestrian::eleccionProbalistica() {
    double Qmayor = 0;
    int idMayor = 0;
    for (int i = 0; i < nodeInicio->getLinkConnection().size(); i++) {
        if (nodeInicio->getQTable()->at(i).getQ()> Qmayor) {
            Qmayor = nodeInicio->getQTable()->at(i).getQ();
            idMayor = i;
        }
    }
    link* linkSeleccionado = getNodeInicio()->getLinkConnection().at(idMayor);
    setLinkActual(linkSeleccionado);
}
// verifica si el nodo ya sali o esta punto final
bool pedestrian::verificarEndLink() {
    bool terminoLink = false;
    // std::cout << getOrientacion().getX() << " ";
    // std::cout << getOrientacion().getY() << std::endl;
    if (position.getX()*std::copysign(1, orientacion.getX()) >= nodeFinal->getCoordX()*std::copysign(1, orientacion.getX()) and
    position.getY()*std::copysign(1, orientacion.getY()) >= nodeFinal->getCoordY()*std::copysign(1, orientacion.getY())){
        terminoLink = true;
    }
    return terminoLink;
}
void pedestrian::calcularNodeFinal() {
    // busqueda del node final
    if(nodeInicio == linkActual->getNode1()){
        setNodeFinal(linkActual->getNode2());
    }
    else {
        setNodeFinal(linkActual->getNode1());
    }
}
void pedestrian::updateLinkParameter() {
    if (verificarEndLink()) {
        algoritmoSarsa();
    }
}
// void pedestrian::updateLinkParameter(sarsa* sarsaAlgorithm) {
//     if (verificarEndLink()) {
//         setNodeInicio(nodeFinal);
//         verificarPedestrianEvacuation();
//         position.setX(getNodeInicio()->getCoordX());
//         position.setY(getNodeInicio()->getCoordY());
//         eleccionRandomLinkActual();
//         calcularNodeFinal();
//         // calcularQ(sarsaAlgorithm);
//         calcularOrientacion();
//         velocidad.setOrientacion(orientacion);
//         velocidad.calcularVectorVelocidad();
//         // falta mejor para que ajuste tambien esta velcoida
//     }
// }
void pedestrian::updateCalle() {
    // Actualizacion del parametros del peaton cuando ya esta en nueva calle.
    setNodeInicio(nodeFinal);
    verificarPedestrianEvacuation();
    position.setX(getNodeInicio()->getCoordX());
    position.setY(getNodeInicio()->getCoordY());
    eleccionRandomLinkActual();
    calcularNodeFinal();
    calcularOrientacion();
    velocidad.setOrientacion(orientacion);
    velocidad.calcularVectorVelocidad();
    // falta mejor para que ajuste tambien esta velcoida
}
void pedestrian::updateParametrosPeaton() {
    // Actualizacion del parametros del peaton cuando ya esta en nueva calle.
    setNodeInicio(nodeFinal);
    verificarPedestrianEvacuation();
    position.setX(getNodeInicio()->getCoordX());
    position.setY(getNodeInicio()->getCoordY());
    int iLinkConnection = iEleccionRandomLinkActual();
    updateLinkActual(iLinkConnection);
    updateStateAction(iLinkConnection);
    // eleccionRandomLinkActual();
    calcularNodeFinal();
    calcularOrientacion();
    velocidad.setOrientacion(orientacion);
    velocidad.calcularVectorVelocidad();
    // falta mejor para que ajuste tambien esta velcoida
}
void pedestrian::calcularOrientacion() {
    double x = nodeFinal->getCoordX() - nodeInicio->getCoordX();
    double y = nodeFinal->getCoordY() - nodeInicio->getCoordY();
    // Calcula la magnitud del vector de dirección
    double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    // Normaliza el vector de dirección (divide cada e por la magnitud)
    orientacion.setX(x / magnitud);
    orientacion.setY(y / magnitud);
}
void pedestrian::calcularRetorno() {
    if (evacuado == true) {
        retorno += surviveReward;
    }
    else {
        retorno += stepReward;
    }
}
void pedestrian::verificarPedestrianEvacuation(){
    const nodeEvacuation* evacuationNode = dynamic_cast<const nodeEvacuation*>(nodeInicio);
    if (evacuationNode) {
        evacuado = "True";
        evacuationNode->sumarPersonaEvacuda();
    }
}
void pedestrian::contarPedestrainSubdivision() {
    int idContador;
    double index_x = (position.getX() - linkActual->getNode1()->getCoordX()) / static_cast<double>(linkActual->getUnitWidthPartion());
    double index_y = (position.getY() - linkActual->getNode1()->getCoordY()) / static_cast<double>(linkActual->getUnitWidthPartion());
    int index_hipo = std::trunc(std::sqrt(std::pow(index_x,2) + pow(index_y, 2)));
    if (index_hipo > linkActual->getSubLinks().size()-1) {
        index_hipo = linkActual->getSubLinks().size()-1;
    }
    idContador = index_hipo;
    
    if (verificarSaltoLink()) {
        if (linkActual == linkPasado) {
            if (getOrientacion().getX() >= 0 and getOrientacion().getY() >= 0 and !(idContador == 0)) {
                linkActual->getSubLinks().back().quitarPedestrianId(getIdPedestrian());
            }
            else if (getOrientacion().getX() <= 0 and getOrientacion().getY() <= 0 and !(idContador == linkActual->getSubLinks().size()-1)) {
                linkActual->getSubLinks().begin()->quitarPedestrianId(getIdPedestrian());
            }
        }
        if (getOrientacionLinkPasado().getX() >= 0 and getOrientacionLinkPasado().getY() >= 0  and !getPrimerTiempo() and (idContador == 0 or idContador == linkActual->getSubLinks().size()-1)) {
            linkPasado->getSubLinks().back().quitarPedestrianId(getIdPedestrian());
        }
        else if (getOrientacionLinkPasado().getX() <= 0 and getOrientacionLinkPasado().getY() <= 0 and !getPrimerTiempo() and (idContador == 0 or idContador == linkActual->getSubLinks().size()-1) ) {
            linkPasado->getSubLinks().at(0).quitarPedestrianId(getIdPedestrian());
        }
    }

    if (!verificarEndLink1()) {
        if (!linkActual->getSubLinks().at(idContador).verificarPedestrianId(getIdPedestrian())) {
            linkActual->getSubLinks().at(idContador).agregarPedestrianId(getIdPedestrian());
            linkActual->getSubLinks().at(idContador).calcularDensidad(linkActual->getLength(), linkActual->getWidth());
            velocidad.actualizarVelocidad(linkActual->getSubLinks().at(idContador).getDensidad());
            
            if (getOrientacion().getX() >= 0 and getOrientacion().getY() >= 0 and !(idContador == 0)) {
                linkActual->getSubLinks().at(idContador-1).quitarPedestrianId(getIdPedestrian());
                setSaltoLink(false);
            }
            else if (getOrientacion().getX() <= 0 and getOrientacion().getY() <= 0 and !(idContador == linkActual->getSubLinks().size()-1)) {
                linkActual->getSubLinks().at(idContador+1).quitarPedestrianId(getIdPedestrian());
                setSaltoLink(false);
            }
        }
    }    
    else {
        linkPasado = linkActual;
        orientacionLinkPasado = orientacion;
        setSaltoLink(true);
    }
    // linkActual->mostrarSubLinks();
    // mostrarPedestrian();
}
// verifica si link concide con node1 y nodeinicia
bool pedestrian::verificarDirectionLink() {
    return nodeInicio == linkActual->getNode1();
}
void pedestrian::encontrarPrimerTiempo() {
    if (primerTiempo) {
        primerTiempo = false;
    }   
}
bool pedestrian::verificarEndLink1() {
    if (position.getX() >= nodeFinal->getCoordX() and position.getY() >= nodeFinal->getCoordY()
    and getOrientacion().getX() >= 0 and getOrientacion().getY() >= 0) {
        return true; 
    }
    else if (position.getX() <= nodeFinal->getCoordX() and position.getY() <= nodeFinal->getCoordY()
    and getOrientacion().getX() <= 0 and getOrientacion().getY() <= 0) {
        return true; 
    }
    return false;
}
bool pedestrian::verificarSaltoLink() {
    if (getSaltoLink() == true) {
        return true;
    }
    return false;
}
void pedestrian::correctionPosition() {
    position.setX(nodeFinal->getCoordX());
    position.setY(nodeFinal->getCoordY());
}
void pedestrian::algoritmoSarsa() {
    // R
    sarsaAlgorithm.setR(getRetorno());
    // QPrevious
    bool verificarQ = false;
    int idQPrevious = 0;
    nodeInicio->buscarQ(*qStateAction, &verificarQ, idQPrevious);
    if (verificarQ) {
        sarsaAlgorithm.setQPrevious(nodeInicio->getQTable()->at(idQPrevious).getQ());
    }
    // Actualizacion del parametros del peaton cuando ya esta en nueva calle.
    // updateCalle();
    updateParametrosPeaton();
    // // Actualización de action y state
    // qStateAction->setA(linkActual->getIdLink());
    // crearqState(nodeInicio);
    // qStateAction->mostrarQ();
    // QCurrent
    // Busco en el nodeCurrent si existe qStateAction, si no esta lo agrego.
    verificarQ = false;
    int idQCurrent = 0;
    nodeInicio->buscarQ(*qStateAction, &verificarQ, idQCurrent);
    if (verificarQ) {
        sarsaAlgorithm.setQCurrent(nodeInicio->getQTable()->at(idQCurrent).getQ());
    }
    else {
        nodeInicio->addqQTable(*qStateAction);
        sarsaAlgorithm.setQCurrent(qStateAction->getQ());
    }
    // calcular Q
    nodeInicio->getQTable()->at(idQPrevious).setQ(sarsaAlgorithm.sarsaActualizarQ());
    nodeInicio->mostrarQTable();
}
// std::vector<int> pedestrian::calcularLevelDensityLinks() {
//     std::vector<int> densityLinks;
//     std::cout << nodeInicio->getLinkConnection().size()<< std::endl;
//     for (int i = 0; i < nodeInicio->getLinkConnection().size(); i++) {
//         nodeInicio->getLinkConnection().at(i)->calcularDensityLevel();
//         // std::cout << nodeInicio->getLinkConnection().at(i)->getDensityLevel();
//         densityLinks.push_back(nodeInicio->getLinkConnection().at(i)->getDensityLevel());
//     }
//     return densityLinks;
// }
void pedestrian::crearqState(node* nodeActual) {
    // Es un setter del state de la variable qStateAction. 
    std::vector<int> densityLinks;
    densityLinks.resize(nodeActual->getLinkConnection().size(),0);
    // std::cout << nodeInicio->getIdNode() << std::endl;
    // std::cout << nodeInicio->getLinkConnection().size() << std::endl;
    for (int i = 0; i < nodeActual->getLinkConnection().size(); i++) {
        nodeActual->getLinkConnection().at(i)->calcularDensityLevel();
        // densityLinks.push_back(nodeInicio->getLinkConnection().at(i)->getDensityLevel());
        // densityLinks.insert(densityLinks.cbegin()+ i,nodeInicio->getLinkConnection().at(i)->getDensityLevel());
        densityLinks[i] = nodeActual->getLinkConnection().at(i)->getDensityLevel();
    }
    qStateAction->setS(densityLinks);
}
void pedestrian::inicializarq() {
    // Inicializar action en el primer instante. 
    qStateAction->setA(linkActual->getIdLink());
    crearqState(nodeInicio);
    stateActionQ* qEncontrado = nullptr;
    bool verificarQ = false;
    int idq = 0;
    nodeInicio->buscarQ(*qStateAction, &verificarQ, idq);
    if (verificarQ) {
    }
    else {
        nodeInicio->addqQTable(*qStateAction);
    }
}
// void pedestrian::crearStateAction() {
// //     qAnterior.setA(linkActual->getIdLink());
// //     qAnterior.setS(calcularLevelDensityLinks());
// //     nodeInicio->addqQTable(qAnterior);
// }

