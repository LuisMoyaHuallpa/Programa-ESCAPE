#include "link.h"
#include "node.h"
#include "subLink.h"
#include "vector2D.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>



int link::unitWidthPartion = 2;
int link::getUnitWidthPartion() {
    return unitWidthPartion;  
}

link::link() : node1(), node2(){
    (*this).idLink = 0;
    (*this).length = 0;
    (*this).width = 0;
}
link::link(int id, node* node1, node* node2, int length, int width) {
    setIdLink(id);
    setNode1(node1);
    setNode2(node2);
    setLength(length);
    setWidth(width);
    calcularNumberPartion();
    subLinks.resize(numberPartion);
}

void link::setIdLink(int id) {
    (*this).idLink = id;  
}
void link::setNode1(node* node1){
    (*this).node1 = node1;
}
void link::setNode2(node* node2){
    (*this).node2 = node2;
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
// void link::setSubDivision(int numeroPartion) {
//     (*this).subdivision = subdivision;
// }

// getters
int link::getIdLink() const {
    return idLink;  
}
node* link::getNode1() const{
    return node1;
}
node* link::getNode2() const{
    return node2;
}
int link::getLength() const{
    return length;
}
int link::getWidth() const{
    return width;
}
std::vector<subLink>& link::getSubLinks() {
    return subLinks;
}
// subLink link::getSubDivision() {
//     return subdivision;
// }

void link::mostrarLink(){
    std::cout << "link: ";
    std::cout << getIdLink() << " ";
    std::cout << "nodes: ";
    std::cout << getNode1() -> getIdNode() << " ";
    std::cout << getNode2() -> getIdNode() << " ";
    std::cout << std::endl;
}
void link::imprimirLink(std::fstream& file) {
    file << getNode1()->getCoordX() << " ";
    file << getNode1()->getCoordY() << " ";
    file << getNode2()->getCoordX() << " ";
    file << getNode2()->getCoordY() << " ";
    file << std::endl;
}
// longitud de cada
void link::calcularHistParam() {
    numberPartion = width/getUnitWidthPartion();
}
vector2D link::calcularDirectionLink() {
    vector2D direction;
    double x = node2->getCoordX() - node1->getCoordX();
    double y = node2->getCoordY() - node1->getCoordY();
    direction.setX(x);
    direction.setY(y);

    // Calcula la magnitud del vector de dirección
    double magnitud = std::sqrt(std::pow(direction.getX(), 2) + std::pow(direction.getY(), 2));

    // Normaliza el vector de dirección (divide cada e por la magnitud)
    direction.setX(direction.getX() / magnitud);
    direction.setY(direction.getY() / magnitud);

    return direction;
}
void link::creacionLinkConnection() {
    getNode1()->agregarLink(&*this);
    getNode2()->agregarLink(&*this);
}
void link::calcularNumberPartion() {
    numberPartion = std::floor(static_cast<double>(length) / static_cast<double>(unitWidthPartion));
}
// void link::calcularSubdivision() {
//     std::vector<vector2D> puntos;
//     for (int i = 1; i <= numberPartion; ++i) {
//         double ratio = static_cast<double>(i) / static_cast<double>(numberPartion);
//         double x = node1->getCoordX() + ratio * (node2->getCoordX() - node1->getCoordX());
//         double y = node1->getCoordY() + ratio * (node2->getCoordY() - node1->getCoordY());
//         puntos.push_back(vector2D(x, y));
//         subdivision.setPuntoFinal(puntos);
//         // std::cout << subdivision1.getPuntoFinal().back().getX() << " ";
//     }
//     // std::cout << std::endl;
// }
void link::mostrarSubLinks() {
    for (int i = 0; i < subLinks.size(); i++) {
        std::cout << subLinks.at(i).getCantidadPedestrian() << " ";
    }
    std::cout << std::endl;
}
