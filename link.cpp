#include "link.h"
#include "dbLink.h"

int unitLongitudPartion = 2;

link::link() : node1(), node2(){
    (*this).id = 0;
    (*this).length = 0;
    (*this).width = 0;
}
link::link(int id, int idNode1, int idNode2, int length, int width) {
    setId(id);
    setNode1(idNode1);
    setNode2(idNode2);
    setLength(length);
    setWidth(width);
}

void link::setId(int id) {
    (*this).id = id;  
}
void link::setNode1(int idNode1){
    (*this).node1 = dbLink::listaNode.extracionNode(idNode1);
}
void link::setNode2(int idNode2){
    (*this).node2 = dbLink::listaNode.extracionNode(idNode2);
}
void link::setLength(int length){
    (*this).length = length;
}
void link::setWidth(int width){
    (*this).width = width;
}

// getters
int link::getId() const {
    return id;  
}
node link::getNode1() const{
    return node1;
}
node link::getNode2() const{
    return node2;
}
int link::getLength() const{
    return length;
}
int link::getWidth() const{
    return width;
}

// longitud de cada
void link::calcularHistParam() {
   numberPartion = width/unitLongitudPartion;
}
