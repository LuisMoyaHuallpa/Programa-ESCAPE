#include "node.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// node::node() : coordenada() {
//     (*this).idNode = 0;
// }
node::node(int idNode, vector2D coordenada) :
    idNode(idNode){
    // setIdNode(idNode);
    setCoordenada(coordenada);
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
// void node::setIdNode(int idNode) {
//     (*this).idNode = idNode;
// }
void node::setCoordenada(vector2D coordenada) {
    (*this).coordenada = coordenada;
}
void node::setIdLinkConnection(std::vector<int> idLinkConnection) {
    (*this).idLinkConnection = idLinkConnection;
}
void node::setStateMatrixTable(std::vector<stateMatrix> stateMatrixTable) {
    (*this).stateMatrixTable = stateMatrixTable;  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int node::getIdNode() const{
    return idNode;
}
vector2D node::getCoordenada() const{
    return coordenada;
}
std::vector<int>& node::getIdLinkConnection() {
    return idLinkConnection;  
}
std::vector<stateMatrix>& node::getStateMatrixTable() {
    return stateMatrixTable;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void node::agregarLink(link* link) {
//     // linkConnection.push_back(link);
// }
void node::buscarStateMatrix(stateMatrix stateMatrixBuscando, bool& verificarStateMatrix, int& iStateMatrixTable) {
    /* recorre la tabla de stateMatrix en busqueda del elemento stateMatrixBuscando  */
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // stateMatrixBuscando   |-->| ELEMENTO stateMatrix a buscar 
    // verificarStateMatrix  |-->| SI ENCUENTRA EL ELEMENTO, ES VERDADERO 
    for (int i = 0; i < stateMatrixTable.size(); i++) {
        if (stateMatrixTable.at(i) == stateMatrixBuscando) {
            verificarStateMatrix = true;
            iStateMatrixTable = i;
            return;
        }
    } 
    // Establecer verificarQ basado en qEncontrado
    verificarStateMatrix = false;
}
// void node::addqQTable(stateActionQ qElemento) {
//     qTable.push_back(qElemento); 
// }
void node::addIdLinkConnection(int idLink) {
    // Añade un idLink, identificador de calle, al vector de idLinkConnection,
    // donde estas todas las calles con posible coneccion
    idLinkConnection.push_back(idLink); 
}
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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mostrar
void node::mostrarNode() {
    // Muestra en el terminal datos del nodo:
    // IdNode
    // x y
    // idLinkConnections
    std::cout << "Node: " << getIdNode() << std::endl;
    std::cout << "x: " << getCoordenada().getX() << " ";
    std::cout << "y: " << getCoordenada().getY() << std::endl;
    std::cout << "linkConnections: ";
    for (int i = 0; i < idLinkConnection.size(); i++) {
        std::cout << idLinkConnection.at(i) << " "; 
    }
    std::cout << std::endl;
}
void node::mostrarQTable() {
    // Muestra en el terminal datos de la tabla de stateMatrix:
    // IdNode
    // x y
    std::cout << "# q:" << stateMatrixTable.size() << std::endl;
    for (int i = 0; i < stateMatrixTable.size(); i++) {
        std::cout << i << " ";
        stateMatrixTable.at(i).mostrarStateMatrix();
        std::cout << std::endl;
    }
}
void node::imprimirQTable(std::fstream& file) {
    // Impresion de sim.csv
    for (auto it = stateMatrixTable.begin(); it != stateMatrixTable.end(); ++it) {
        // Imprimir id del nodo o intersección
        file << idNode << ",";
        it->imprimirStateMatrix(file);
    }
}


