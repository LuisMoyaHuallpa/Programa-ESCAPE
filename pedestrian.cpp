#include "pedestrian.h"
#include "dbLink.h"

const int pedestrian::surviveReward = 100000;
const int pedestrian::deadReward = -1000; 
const int pedestrian::stepReward = -1;

pedestrian::pedestrian() : nearNode() {
    (*this).id = 0;
    (*this).edad = 0;
    (*this).hhType = 0;
    (*this).hhId = 0;
}
pedestrian::pedestrian(int id, int edad, int hhType, int hhId, int idNearNode) {

    setId(id);
    setEdad(edad);
    setHHType(hhType);
    setHHId(hhId);
    setIdNearNode(idNearNode);
}

void pedestrian::setId(int id){
    (*this).id = id;
}
void pedestrian::setEdad(int edad){
    (*this).edad = edad;
}
void pedestrian::setHHType(int hhType){
    (*this).hhType = hhType;
}
void pedestrian::setHHId(int hhId){
    (*this).hhId = hhId;
}
void pedestrian::setIdNearNode(int idNearNode){
    (*this).nearNode = dbLink::listaNode.extracionNode(idNearNode);
}

int pedestrian::getId() const {
    return id;
}
int pedestrian::getEdad() const{
    return edad;
}
int pedestrian::getHHType() const{
    return hhType;
}
int pedestrian::getHHId() const{
    return hhId;
}
node pedestrian::getNearNode() const{
    return nearNode;
}

