#include "node.h"

node::node() {
    (*this).idNode = 0;
    (*this).coordX = 0;
    (*this).coordY = 0;

}
node::node(int id, int coordX, int coordY) {
    setIdNode(id);
    setCoorX(coordX);
    setCoorY(coordY);
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
void node::setLinkConnection(std::vector<link*> linkConnection){
    (*this).linkConnection = linkConnection;
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
std::vector<link*> node::getLinkConnection() {
    return linkConnection;
}

void node::agregarLink(link* link) {
    linkConnection.push_back(link);
}
void node::imprimirNode() {
    std::cout << "node: ";
    std::cout << getIdNode() << " ";
    std::cout << " links: ";
    for (int i = 0; i < linkConnection.size(); i++) {
        std::cout << linkConnection.at(i)->getIdLink() << " "; 
    }
    std::cout << std::endl;
}


