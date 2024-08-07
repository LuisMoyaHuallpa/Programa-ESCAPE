#include "node.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// extras
#include "link.h"
#include "pedestrian.h"
#include "stateMatrix.h"
#include <vector>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
node::node(const int idNode, const vector2D coordenada) :
    idNode(idNode), coordenada(coordenada){
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// destrutor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// node::~node(){}

std::string node::getNodeType() {
    return "node";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void node::setIdLinkConnection(std::vector<int> idLinkConnection) {
//     (*this).idLinkConnection = idLinkConnection;
// }
// void node::setStateMatrixTable(std::vector<stateMatrix> stateMatrixTable) {
//     (*this).stateMatrixTable = stateMatrixTable;  
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int node::getIdNode() const{
    return idNode;
}
const vector2D node::getCoordenada() const{
    return coordenada;
}
const std::vector<link*> node::getLinkConnectionsPtr() const {
    return linkConnectionsPtr;  
}
std::vector<stateMatrix*>* node::getStateMatrixExperimentadosPtr() {
    return &stateMatrixsExperimentadosPtr;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const node* node::buscarNodoFinal(link *callePtr) const {
    /* busqueda del node final segun la calle que se encuentre
        cada calle tiene un nodo de inicio y final dependiendo
        si esta de ida o vuelta delvolvera el nodo final esto seria ida */
    // Si el nodo donde estoy es el nodo 1 de la calle entonce nodo final es el nodo 2
    if(callePtr->getNode1Ptr() == this){
        return callePtr->getNode2Ptr();
    }
    // Si el nodo donde estoy es el nodo 2 de la calle entonce nodo final es el nodo 1
    else {
        return callePtr->getNode1Ptr();    
    }
}
// void node::buscarStateMatrix(stateMatrix stateMatrixBuscando, bool& verificarStateMatrix, int& iStateMatrixTable) {
//     /* recorre la tabla de stateMatrix en busqueda del elemento stateMatrixBuscando  */
//     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     // stateMatrixBuscando   |-->| ELEMENTO stateMatrix a buscar 
//     // verificarStateMatrix  |-->| SI ENCUENTRA EL ELEMENTO, ES VERDADERO 
//     for (int i = 0; i < stateMatrixTable.size(); i++) {
//         if (stateMatrixTable.at(i) == stateMatrixBuscando) {
//             verificarStateMatrix = true;
//             iStateMatrixTable = i;
//             return;
//         }
//     } 
//     // Establecer verificarQ basado en qEncontrado
//     verificarStateMatrix = false;
// }
// void node::addqQTable(stateActionQ qElemento) {
//     qTable.push_back(qElemento); 
// }
// void node::ordenarQTable() {
//     std::sort(qTable.begin(), qTable.end(), stateActionQ::compararId);
// }
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
// void node::crearStateMatrix() {
//     stateMatrix stateMatrixElement;
//     for (int i = 0; i < qTable.size(); i++) {
//         qTable[i].getQ();
//     }
// }
estado node::verificarNodoEvacuation() const {
    return evacuando;    
}
std::vector<int> node::stateObservado() const {
    // vector de estado
    std::vector<int> stateObservado;
    // Reserva espacio en el vector
    stateObservado.reserve(linkConnectionsPtr.size());
    // asignacion de estados
    for (link* calle : linkConnectionsPtr) {
        stateObservado.push_back(calle->getDensityLevel());
    }
    return stateObservado;
}
double node::calcularDistanciaA(const node* nodo2) const {
    /* calcula la distancia entre dos nodos*/
    return coordenada.distanciaA(nodo2->getCoordenada());
}
void node::addLink(link *calle) {
    /* agrega una calle en el vector de linkConnections*/
    linkConnectionsPtr.push_back(calle);
}
void node::addStateMatrixExperimentadosPtr(stateMatrix *stateMatrixExperimentado){
    /* agrega un stateMatrixExperimentado en el vector stateMatrixsExperimentado*/
    stateMatrixsExperimentadosPtr.push_back(stateMatrixExperimentado);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mostrar
void node::mostrarNode() const {
    /* Muestra en el terminal datos del nodo:
    // IdNode
    // x y
    // idLinkConnections*/
    std::cout << "Node: " << idNode << std::endl;
    std::cout << "x: " << coordenada.getX() << " ";
    std::cout << "y: " << coordenada.getY() << std::endl;
    std::cout << "linkConnections: ";
    for (int i = 0; i < linkConnectionsPtr.size(); i++) {
        std::cout << linkConnectionsPtr.at(i)->getIdLink() << " "; 
    }
    std::cout << std::endl;
}
void node::mostrarStateMatrixTable() const {
    /* muestra la tabla de stateMatrix experimentado*/
    std::cout << "Qtable: " << std::endl;
    for (const stateMatrix* const elemento : stateMatrixsExperimentadosPtr) {
        elemento->mostrarStateMatrix();
    } 
}
