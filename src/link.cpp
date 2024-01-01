#include "link.h"

int link::unitWidthPartion = 10;
int link::getUnitWidthPartion() {
    return unitWidthPartion;  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
link::link() {
    (*this).idLink = 0;
    (*this).idNode1 = 0;
    (*this).idNode2 = 0;
    (*this).length = 0;
    (*this).width = 0;
}
link::link(int idLink, int idNode1, int idNode2, int length, int width) {
    setIdLink(idLink);
    setIdNode1(idNode1);
    setIdNode2(idNode2);
    setLength(length);
    setWidth(width);
    calcularNumberPartion();
    subLinks.resize(numberPartion);
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
void link::setSubLinks(std::vector<subLink> subLinks) {
    (*this).subLinks = subLinks;
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
int link::getNumberPartion() {
    return numberPartion;  
}
std::vector<subLink>& link::getSubLinks() {
    return subLinks;
}
int link::getDensityLevel() {
    return densityLevel;
}

// longitud de cada
void link::calcularHistParam() {
    numberPartion = width/getUnitWidthPartion();
}
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
void link::creacionLinkConnection() {
    // getNode1()->agregarLink(&*this);
    // getNode2()->agregarLink(&*this);
}
void link::calcularNumberPartion() {
    numberPartion = std::floor(static_cast<double>(length) / static_cast<double>(unitWidthPartion));
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
}
void link::mostrarLink(){
    std::cout << "link: ";
    std::cout << getIdLink() << " ";
    std::cout << "nodes: ";
    std::cout << getIdNode1() << " ";
    std::cout << getIdNode2() << " ";
    std::cout << std::endl;
}
// void link::imprimirLink(std::fstream& file) {
//     file << getNode1()->getCoordX() << " ";
//     file << getNode1()->getCoordY() << " ";
//     file << getNode2()->getCoordX() << " ";
//     file << getNode2()->getCoordY() << " ";
//     file << std::endl;
// }
void link::mostrarSubLinks() {
    std::cout << getIdLink() << "  ";
    for (int i = 0; i < subLinks.size(); i++) {
        subLinks.at(i).mostrarSubLink();
    }
    std::cout << std::endl;
}
