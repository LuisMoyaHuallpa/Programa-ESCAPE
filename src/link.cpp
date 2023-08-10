#include "link.h"
#include "node.h"
#include "vector2D.h"
#include <iostream>
#include <cmath>



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
    // (*this).node1 -> agregarLink(id);
    // (*this).node1 -> imprimirNode();
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

void link::mostrarLink(){
    std::cout << "link: ";
    std::cout << getIdLink() << " ";
    std::cout << "nodes: ";
    std::cout << getNode1() -> getIdNode() << " ";
    std::cout << getNode2() -> getIdNode() << " ";
    std::cout << std::endl;
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
