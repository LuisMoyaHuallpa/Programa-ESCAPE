#include "node.H"
#include <iostream>
#include <ostream>

node::node(int number, int coordX, int coordY, int evacuationCode, int rewardCode) {
    setNumber(number);
    std::cout << number <<std::endl;
    setCoorX(coordX);
    setCoorY(coordY);
    setEvacuationCode(evacuationCode);
    setRewardCode(rewardCode);
}
// setters
void node::setNumber(int number) {
    (*this).number = number;
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
int node::getNumber() const{
    return number;
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
    std::cout << getNumber() << std::endl;
}

