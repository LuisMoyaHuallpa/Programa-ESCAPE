#include "node.h"
#include <fstream>
#include <vector>
#include "iostream"
// #include "q.h"
#include "state.h"
#include "stateMatrix.h"
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
std::vector<stateActionQ>* node::getQTable() {
    return &qTable;
}

void node::agregarLink(link* link) {
    linkConnection.push_back(link);
}
void node::buscarQ(stateActionQ qBuscando, bool* verificarQ, int idq) {
    // Variable para seguir el estado de la búsqueda
    bool qverificado = false;
    for (int i = 0; i < (*getQTable()).size(); i++) {
        if ((*getQTable()).at(i) == qBuscando) {
            qverificado = true;
            // qEncontrado = &getQTable().at(i);
            break;
        }
    } 
    // Establecer verificarQ basado en qEncontrado
    *verificarQ = qverificado;

}
void node::addqQTable(stateActionQ qElemento) {
    qTable.push_back(qElemento); 
}
void node::ordenarQTable() {
    std::sort(qTable.begin(), qTable.end(), stateActionQ::compararId);
}
// void node::buscarQ(stateActionQ qBuscando, bool* verificarQ) {
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
void node::crearStateMatrix() {
    stateMatrix stateMatrixElement;
    for (int i = 0; i < qTable.size(); i++) {
        qTable[i].getQ();
    }
}
bool node::verificarCambioState(state stateAnterior, state stateActual) {
    // Verificar si existe cambio de state entre diferentes stateActionQ.
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // stateActual       |-->| STATE DEL stateActionQ ACTUAL DE LA QTABLE
    // stateAnterior     |-->| STATE DEL stateActionQ ANTERIOR DE LA QTABLE 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (stateAnterior == stateActual) {
        return true;
    }
    return false;  
}
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
    std::cout <<"Node:" << getIdNode();
    std::cout << std::endl;
    std::cout << "# q:" << qTable.size() << std::endl;
    for (int i = 0; i < qTable.size(); i++) {
        std::cout << i << " ";
        qTable.at(i).mostrarQ();
        std::cout << std::endl;
    }
}
void node::imprimirQTable(std::fstream& file) {
    // Impresion de sim.csv
    stateMatrix stateMatrixElement;
    state stateAnterior;
    for (int i = 0; i < qTable.size(); i++) {
        getQTable()->at(i).mostrarQ();
        std::cout << std::endl;
        // !-----------------------------------------------------------------------
        // Primer stateActionQ
        if (i == 0) {
            // Set idNode en stateMatrixElement. Es el id del nodo de la interseccion.
            stateMatrixElement.setIdNode(getQTable()->at(i).getA().getIdLink());
            // Set stateValue en stateMatrixElement. Es el state de la interseccion. 
            stateMatrixElement.setStateValue(getQTable()->at(i).getS());
            // Set valor de Q en el vectorQ en la locacion i.
            stateMatrixElement.agregarQ(getQTable()->at(i).getA().getILinkConnection(), getQTable()->at(i).getQ());
        }
        // !-----------------------------------------------------------------------
        // Siguiente stateActionQ
        else {
            // !-----------------------------------------------------------------------
            // Si no hay cambio de state realiza lo siguiente
            if (!(verificarCambioState(stateAnterior, qTable[i].getS()))) {
                // Set valor de Q en el vectorQ en la locacion i.
                stateMatrixElement.agregarQ(qTable[i].getA().getILinkConnection(), qTable[i].getQ());
            }
            else {
                // !-----------------------------------------------------------------------
                // Imprime el stateMatrixElement final
                stateMatrixElement.imprimirStateMatrix(file);
                // !-----------------------------------------------------------------------
                // Continua con un nuevo stateMatrixElement
                // Set idNode en stateMatrixElement. Es el id del nodo de la interseccion.
                stateMatrixElement.setIdNode(qTable[i].getA().getIdLink());
                // Set stateValue en stateMatrixElement. Es el state de la interseccion. 
                stateMatrixElement.setStateValue(qTable[i].getS());
            }
        }
        // Guarda el state del stateActionQ anterior.
        stateAnterior = qTable[i].getS();
        // Guardar stateMatrixElement y el vector dbStateMatrix
    }
}


