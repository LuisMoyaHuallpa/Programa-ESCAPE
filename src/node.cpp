#include "node.h"
#include <vector>
#include "iostream"
#include "q.h"
#include <algorithm>

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
std::vector<q> node::getQTable() {
    return qTable;
}

void node::agregarLink(link* link) {
    linkConnection.push_back(link);
}

void node::buscarQ(q qBuscando, bool* verificarQ, int idq) {
    // Variable para seguir el estado de la búsqueda
    bool qverificado = false;
    for (int i = 0; i < getQTable().size(); i++) {
        if (getQTable().at(i) == qBuscando) {
            qverificado = true;
            // qEncontrado = &getQTable().at(i);
            break;
        }
    } 
    // Establecer verificarQ basado en qEncontrado
    *verificarQ = qverificado;

}

// void node::buscarQ(q qBuscando, bool* verificarQ) {
//     std::cout << "buscando.." << std::endl;
//     verificarQ = false;
//     for (int i = 0; i < getQTable().size(); i++) {
//         if (getQTable().at(i) == qBuscando) {
//             std::cout << "hola";
//             // qEncontrado = &getQTable().at(i);
//             *verificarQ = true;
//             std::cout << *verificarQ << std::endl;
//             break;
//         }
//     } 
//     *verificarQ = false;
// }
void node::mostrarNode() {
    std::cout << "node: ";
    std::cout << getIdNode() << " ";
    std::cout << " links: ";
    for (int i = 0; i < linkConnection.size(); i++) {
        std::cout << linkConnection.at(i)->getIdLink() << " "; 
    }
    std::cout << std::endl;
}
void node::mostrarQTable() {
    std::cout << std::endl;
    std::cout <<"Node:" << getIdNode();
    std::cout << std::endl;
    std::cout << "# q:" << qTable.size() << std::endl;
    for (int i = 0; i < qTable.size(); i++) {
        std::cout << i << " ";
        qTable.at(i).mostrarQ();
        std::cout << std::endl;
    }
}
void node::addqQTable(q qElemento) {
    qTable.push_back(qElemento); 
}
