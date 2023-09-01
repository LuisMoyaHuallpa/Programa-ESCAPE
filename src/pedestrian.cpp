#include "pedestrian.h"

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
pedestrian::pedestrian(int edad, int gender, int hhType, int hhId, node* nodeInicio)  {
    setIdPedestrian(contador++);
    setEdad(edad);
    setGender(gender);
    setHHType(hhType);
    setHHId(hhId);
    setNodeInicio(nodeInicio);
    setEmpezoCaminar(false);
    setPrimerTiempo(true);
    setSaltoLink(false);
    double x = nodeInicio->getCoordX();
    double y = nodeInicio->getCoordY();
    vector2D position(x, y);
    setPosition(position);
    eleccionRandomLinkActual();
    setLinkPasado(linkActual);
    calcularNodeFinal();
    calcularOrientacion();
    velocidad.setOrientacion(orientacion);
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
void pedestrian::setPosition(vector2D position) {
    (*this).position = position;
}
void pedestrian::setLinkActual(link *linkActual) {
    (*this).linkActual = linkActual;
}
void pedestrian::setLinkPasado(link *linkPasado) {
    (*this).linkPasado = linkPasado;
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
vector2D pedestrian::getPosition() {
    return position;
}
link *pedestrian::getLinkActual() {
    return linkActual;
}
link *pedestrian::getLinkPasado() {
    return linkPasado;
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
    // velocidad.calcularVectorVelocidad();
    position += velocidad * tiempo::deltaTiempo;
    if (verificarEndLink1()) {
        correctionPosition();
    }
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
    // link* linkSeleccionado = nodeInicio->getLinkConnection().at(numero_aleatorio);
    link* linkSeleccionado = getNodeInicio()->getLinkConnection().at(numero_aleatorio);
    setLinkActual(linkSeleccionado);
}
// verifica si el nodo ya sali o esta punto final
bool pedestrian::verificarEndLink() {
    bool terminoLink = false;
    if (position.getX()*orientacion.getX() >= nodeFinal->getCoordX()*orientacion.getX() and
    position.getY()*orientacion.getY() >= nodeFinal->getCoordY()*orientacion.getY()){
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
    if (verificarEndLink1()) {
        setNodeInicio(nodeFinal);
        eleccionRandomLinkActual();
        calcularNodeFinal();
        calcularOrientacion();
        velocidad.setOrientacion(orientacion);
    }
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
    if (nodeInicio->getEvacuationCode() == 0) {
        retorno += stepReward;
    }
    else {
        retorno += surviveReward;
    }
}
bool pedestrian::verificarEvacuationNode(){
    if (nodeInicio->getEvacuationCode() == 1) {
        return true;
    }
    return false;
}
void pedestrian::contarPedestrainSubdivision() {
    int idContador;
    double row = (position.getX() - linkActual->getNode1()->getCoordX()) / static_cast<double>(linkActual->getUnitWidthPartion());
    double col = (position.getY() - linkActual->getNode1()->getCoordY()) / static_cast<double>(linkActual->getUnitWidthPartion());
    int idx_hipo = std::trunc(std::sqrt(std::pow(row,2) + pow(col, 2)));
    if (idx_hipo > linkActual->getSubLinks().size()-1) {
        idx_hipo = idx_hipo - 1;
    }
    idContador = idx_hipo;
    
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
    linkActual->mostrarSubLinks();
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
        std::cout << "arriba";
        return true; 
    }
    else if (position.getX() <= nodeFinal->getCoordX() and position.getY() <= nodeFinal->getCoordY()
    and getOrientacion().getX() <= 0 and getOrientacion().getY() <= 0) {
        std::cout << "abajo";
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
