#include "node.h"

node::node() {
    (*this).id = 0;
    (*this).coordX = 0;
    (*this).coordY = 0;
    (*this).evacuationCode = 0;
    (*this).rewardCode = 0;
}
node::node(int id, int coordX, int coordY, int evacuationCode, int rewardCode) {
    setId(id);
    setCoorX(coordX);
    setCoorY(coordY);
    setEvacuationCode(evacuationCode);
    setRewardCode(rewardCode);
}
// setters
void node::setId(int id) {
    (*this).id = id;
}
void node::setCoorX(int coordX){
    (*this).coordX = coordX;
}
void node::setCoorY(int coordY){
    (*this).coordY = coordY;
}
void node::setEvacuationCode(int evacuationCode){
    (*this).evacuationCode = evacuationCode;
}
void node::setRewardCode(int rewardCode){
    (*this).rewardCode = rewardCode;
}

// getter
int node::getId() const{
    return id;
}
int node::getCoordX() const{
    return coordX;
}
int node::getCoordY() const{
    return coordY;
}
int node::getEvacuationCode() const{
    return evacuationCode;
}
int node::getRewardCode() const{
    return rewardCode;
}

void node::imprimir() {
    std::cout << getId() << std::endl;
}

