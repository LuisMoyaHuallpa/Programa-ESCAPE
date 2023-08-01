#include "node.h"
#include <iostream>
#include <vector>

node::node() {
    (*this).idNode = 0;
    (*this).coordX = 0;
    (*this).coordY = 0;
    (*this).evacuationCode = 0;
    (*this).rewardCode = 0;

}
node::node(int id, int coordX, int coordY, int evacuationCode, int rewardCode) {
    setIdNode(id);
    setCoorX(coordX);
    setCoorY(coordY);
    setEvacuationCode(evacuationCode);
    setRewardCode(rewardCode);
}
// setters
void node::setIdNode(int id) {
    (*this).idNode = id;
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
void node::setLinkConnection(std::vector<int> linkConnection){
    (*this).linkConnection =linkConnection;
}

// getter
int node::getIdNode() const{
    return idNode;
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
std::vector<int> node::getLinkConnection() {
    return linkConnection;
}

void node::agregarLink(int idLink) {
    linkConnection.push_back(idLink); 
}
void node::imprimirNode() {
    std::cout << "node: ";
    std::cout << getIdNode() << " ";
    std::cout << " links: ";
    for (int i = 0; i < linkConnection.size(); i++) {
        std::cout << linkConnection.at(i) << " "; 
    }
    std::cout << std::endl;
}


