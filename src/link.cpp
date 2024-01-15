#include "link.h"
#include "nodes.h"

int link::unitWidthPartion = 10;
int link::getUnitWidthPartion() {
    return unitWidthPartion;  
}

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
    // calcula el numero de particiones y particiona la calle en subLink.
    subLinks.resize(calcularNumberPartion());
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
void link::setSubLinks(std::vector<subLink> subLinks) {
    (*this).subLinks = subLinks;
}
void link::setDensityLevel(int densityLevel) {
    (*this).densityLevel = densityLevel;
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
int link::getNumberPartion() {
    return numberPartion;  
}
std::vector<subLink>& link::getSubLinks() {
    return subLinks;
}
int link::getDensityLevel() {
    return densityLevel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// longitud de cada
// void link::calcularHistParam() {
//     numberPartion = width/getUnitWidthPartion();
// }
// vector2D link::calcularDirectionLink() {
//     vector2D direction;
//     double x = node2->getCoordX() - node1->getCoordX();
//     double y = node2->getCoordY() - node1->getCoordY();
//     direction.setX(x);
//     direction.setY(y);
//     // Calcula la magnitud del vector de dirección
//     double magnitud = std::sqrt(std::pow(direction.getX(), 2) + std::pow(direction.getY(), 2));
//     // Normaliza el vector de dirección (divide cada e por la magnitud)
//     direction.setX(direction.getX() / magnitud);
//     direction.setY(direction.getY() / magnitud);
//     return direction;
// }
void link::calcularOrientacionLink() {
    /* deberia esta calcular orientacion pero necesita acceder a dbLink
        por ello se calculara la direccione en pedestrian*/
    double x = nodes::dbNodeTotal.at(getIdNode2())->getCoordX() - nodes::dbNodeTotal.at(getIdNode1())->getCoordX();
    double y = nodes::dbNodeTotal.at(getIdNode2())->getCoordY() - nodes::dbNodeTotal.at(getIdNode1())->getCoordY();
    // Calcula la magnitud del vector de dirección
    double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    // Normaliza el vector de dirección (divide cada e por la magnitud)
    orientacionLink.setX(x / magnitud);
    orientacionLink.setY(y / magnitud);
}
int link::calcularNumberPartion() {
    /* calcula el numero de particiones para la calle */
    return std::floor(static_cast<double>(length) / static_cast<double>(unitWidthPartion));
}
void link::calcularDensityLevel() {
    double densidadMayorSubLink = 0.0;
    for (int i = 0; i < subLinks.size(); i++) {
        if (subLinks.at(i).getDensidad() > densidadMayorSubLink) {
            densidadMayorSubLink = subLinks.at(i).getDensidad();
        }
    }
    if(densidadMayorSubLink <= 0.5){
        densityLevel = 0;
    }  
    else if (densidadMayorSubLink <= 3.0) {
        densityLevel = 1;
    }
    else {
        densityLevel = 2;
    }
    std::cout << "den: " << densityLevel << std::endl;
}
void link::mostrarLink(){
    std::cout << "link: ";
    std::cout << getIdLink() << " ";
    std::cout << "nodes: ";
    std::cout << getIdNode1() << " ";
    std::cout << getIdNode2() << " ";
    std::cout << std::endl;
}
void link::imprimirLink(std::fstream& file) {
    file << nodes::dbNodeTotal.at(getIdNode1())->getCoordX() << " ";
    file << nodes::dbNodeTotal.at(getIdNode1())->getCoordY() << " ";
    file << nodes::dbNodeTotal.at(getIdNode2())->getCoordX() << " ";
    file << nodes::dbNodeTotal.at(getIdNode2())->getCoordY() << " ";
    file << std::endl;
}
void link::mostrarSubLinks() {
    std::cout << getIdLink() << "  ";
    for (int i = 0; i < subLinks.size(); i++) {
        subLinks.at(i).mostrarSubLink();
    }
    std::cout << std::endl;
}
