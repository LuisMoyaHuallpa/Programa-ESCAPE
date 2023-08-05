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
pedestrian::pedestrian(int edad, int gender, int hhType, int hhId, node* nodeInicio) {
    setIdPedestrian(contador++);
    setEdad(edad);
    setGender(gender);
    setHHType(hhType);
    setHHId(hhId);
    setNodeInicio(nodeInicio);
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
vector2D pedestrian::getPosition() {
    return position;
}

void pedestrian::mostrarPedestrian(){
    std::cout << getIdPedestrian() << ' ';
    std::cout << getNodeInicio()->getIdNode() << ' ';
    std::cout << "node incio: ";
    std::cout << getNodeInicio()->getCoordX() << ' ';
    std::cout << getNodeInicio()->getCoordY() << ' ';
    std::cout << "position: ";
    std::cout << getPosition().getX() << " ";
    std::cout << getPosition().getY() << " ";
    std::cout << std::endl;
}
void pedestrian::posibleCaminos() {
    // int idlink =getNodeInicio()->getLinkConnection().at(0);
}
void pedestrian::caminar() {
    position += velocidad*tiempo::deltaTiempo;
}
