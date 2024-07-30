#include "node.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// extras
#include "link.h"
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
const std::vector<link*> node::getLinkConnection() const {
    return linkConnection;  
}
std::vector<stateMatrix*>& node::getStateMatrixExperimentados() {
    return stateMatrixExperimentos;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
std::vector<int> node::stateObservado() const {
    // vector de estado
    std::vector<int> stateObservado;
    // Reserva espacio en el vector
    stateObservado.reserve(linkConnection.size());
    // asignacion de estados
    for (link* calle : linkConnection) {
        stateObservado.push_back(calle->getDensityLevel());
    }
    return stateObservado;
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
    for (int i = 0; i < linkConnection.size(); i++) {
        std::cout << linkConnection.at(i)->getIdLink() << " "; 
    }
    std::cout << std::endl;
}
void node::mostrarQTable() const {
    // Muestra en el terminal datos de la tabla de stateMatrix:
    // IdNode
    // x y
    // std::cout << "# q:" << stateMatrixTable.size() << std::endl;
    std::cout << "# q:" << stateMatrixTableMap.size() << std::endl;
    // for (int i = 0; i < stateMatrixTableMap.size(); i++) {
    for (auto& s : stateMatrixTableMap) {
        s.second->mostrarStateMatrix(); 
        std::cout << std::endl;
    }
}
void node::imprimirQTable(std::fstream& file) const {
   // Impresion de sim.csv
    // for (auto it = stateMatrixTable.begin(); it != stateMatrixTable.end(); ++it) {
    //     // Imprimir id del nodo o intersección
    //     file << idNode << ",";
    //     it->imprimirStateMatrix(file);
    // }
    //alternativa
    for (auto& s : stateMatrixTableMap) {
        // Imprimir id del nodo o intersección
        file << idNode << ",";
        s.second->imprimirStateMatrix(file);
    }
}


