#include "link.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int link::numberDivisiones = 10;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
link::link() : orientacionLink() {
    (*this).idLink = 0;
    (*this).idNode1 = 0;
    (*this).idNode2 = 0;
    (*this).length = 0;
    (*this).width = 0;
    (*this).densityLevel = 0;
}
link::link(int idLink, int idNode1, int idNode2, int length, int width)  {
    setIdLink(idLink);
    setIdNode1(idNode1);
    setIdNode2(idNode2);
    // calcula la orientacion de la calle segun el node 1 y 2.
    calcularOrientacionLink();
    setLength(length);
    setWidth(width);
    setDensityLevel(0);
    calcularAnchoDivisiones();
    pedestriansInSublink.resize(link::numberDivisiones, 0);
    densityInSublink.resize(link::numberDivisiones, 0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void link::setIdLink(int idLink) {
    (*this).idLink = idLink;  
}
void link::setIdNode1(int idNode1) {
    (*this).idNode1 = idNode1;
}
void link::setIdNode2(int idNode2) {
    (*this).idNode2 = idNode2;  
}
void link::setLength(int length){
    (*this).length = length;
}
void link::setWidth(int width){
    (*this).width = width;
}
void link::setOrientacionLink(vector2D orientacionLink) {
    (*this).orientacionLink = orientacionLink;
}
void link::setPedestriansInSublink(std::vector<int> pedestriansInSublink) {
    (*this).pedestriansInSublink = pedestriansInSublink;
}
void link::setDensityInSublink(std::vector<double> densityInSublink) {
    (*this).densityInSublink = densityInSublink;
}
void link::setDensityLevel(int densityLevel) {
    (*this).densityLevel = densityLevel;
}
void link::setAnchoDivisiones(double anchoDivisiones) {
    (*this).anchoDivisiones = anchoDivisiones;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int link::getIdLink() const {
    return idLink;  
}
int link::getIdNode1() const{
    return idNode1;
}
int link::getIdNode2() const{
    return idNode2;
}
int link::getLength() const{
    return length;
}
int link::getWidth() const{
    return width;
}
vector2D link::getOrientacionLink() const {
    return orientacionLink;
}
std::vector<int>& link::getPedestriansInSublink() {
    return pedestriansInSublink;
}
std::vector<double>& link::getDensityInSublink() {
    return densityInSublink;
}
int link::getDensityLevel() {
    return densityLevel;
}
double link::getAnchoDivisiones() {
    return anchoDivisiones;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void link::calcularOrientacionLink() {
    /* deberia esta calcular orientacion pero necesita acceder a dbLink
        por ello se calculara la direccione en pedestrian*/
    double x = nodes::get()->getDbNodeTotal().at(getIdNode2())->getCoordenada().getX() - nodes::get()->getDbNodeTotal().at(getIdNode1())->getCoordenada().getX();
    double y = nodes::get()->getDbNodeTotal().at(getIdNode2())->getCoordenada().getY() - nodes::get()->getDbNodeTotal().at(getIdNode1())->getCoordenada().getY();
    // Calcula la magnitud del vector de dirección
    double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    // Normaliza el vector de dirección (divide cada e por la magnitud)
    orientacionLink.setX(std::abs(x / magnitud));
    orientacionLink.setY(std::abs(y / magnitud));
}
void link::calcularAnchoDivisiones() {
    /* Calcula el ancho de divisiones de la calle segun el numero de divisiones preestablecidas*/
    double ancho_x = nodes::get()->getDbNodeTotal().at(idNode1)->getCoordenada().getX() - nodes::get()->getDbNodeTotal().at(idNode2)->getCoordenada().getX();
    double ancho_y = nodes::get()->getDbNodeTotal().at(idNode1)->getCoordenada().getY() - nodes::get()->getDbNodeTotal().at(idNode2)->getCoordenada().getY();
    double ancho = std::sqrt(pow(ancho_x, 2) + pow(ancho_y, 2)) / static_cast<double>(link::numberDivisiones);
    anchoDivisiones = ancho;
}
void link::calcularDensity() {
    /* calculo de la densidad en cada sublink de la calle*/
    for (int i = 0; i < pedestriansInSublink.size(); i++) {
        densityInSublink.at(i) = pedestriansInSublink.at(i) / (anchoDivisiones * width);
    }
}
void link::calcularDensityLevel() {
    /* calcula el nivel de densidad de la calle */
    double densidadMayorSubLink = 0.0;
    // Encontrar el sublink con mayor densidad de la calle
    for (int i = 0; i < densityInSublink.size(); i++) {
        if (densityInSublink.at(i) > densidadMayorSubLink) {
            densidadMayorSubLink = densityInSublink.at(i);
        }
    }
    // elecion del nivel de densidad segun rangos preestablecidos
    if(densidadMayorSubLink <= 0.5){
        densityLevel = 0;
    }  
    else if (densidadMayorSubLink <= 3.0) {
        densityLevel = 1;
    }
    else {
        densityLevel = 2;
    }
}

void link::mostrarLink(){
    std::cout << "link: ";
    std::cout << getIdLink() << " ";
    std::cout << "nodes: ";
    std::cout << getIdNode1() << " ";
    std::cout << getIdNode2() << " ";
    std::cout << anchoDivisiones << std::endl;
    std::cout << std::endl;
}
void link::imprimirLink(std::fstream& file) {
    file << std::fixed << std::setprecision(2);
    file << nodes::get()->getDbNodeTotal().at(getIdNode1())->getCoordenada().getX() << " ";
    file << nodes::get()->getDbNodeTotal().at(getIdNode1())->getCoordenada().getY() << " ";
    file << nodes::get()->getDbNodeTotal().at(getIdNode2())->getCoordenada().getX() << " ";
    file << nodes::get()->getDbNodeTotal().at(getIdNode2())->getCoordenada().getY() << " ";
    file << std::endl;
}
void link::mostrarSubLink() {
    std::cout << getIdLink() << "  ";
    for (int i = 0; i < pedestriansInSublink.size(); i++) {
        std::cout << pedestriansInSublink.at(i) << " ";
    }
    std::cout << std::endl;
}
