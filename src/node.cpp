#include "node.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
node::node() {
    (*this).idNode = 0;
    (*this).coordX = 0;
    (*this).coordY = 0;
}
node::node(int idNode, int coordX, int coordY) {
    setIdNode(idNode);
    setCoorX(coordX);
    setCoorY(coordY);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void node::setIdNode(int idNode) {
    (*this).idNode = idNode;
}
void node::setCoorX(double coordX){
    (*this).coordX = coordX;
}
void node::setCoorY(double coordY){
    (*this).coordY = coordY;
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
double node::getCoordX() const{
    return coordX;
}
double node::getCoordY() const {
    return coordY;
}
std::vector<int> node::getIdLinkConnection() {
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
// void node::buscarQ(stateActionQ qBuscando, bool* verificarQ, int idq) {
//     // Variable para seguir el estado de la búsqueda
//     bool qverificado = false;
//     for (int i = 0; i < (*getQTable()).size(); i++) {
//         if ((*getQTable()).at(i) == qBuscando) {
//             qverificado = true;
//             // qEncontrado = &getQTable().at(i);
//             break;
//         }
//     } 
//     // Establecer verificarQ basado en qEncontrado
//     *verificarQ = qverificado;
// }
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
    std::cout << "x: " << getCoordX() << " ";
    std::cout << "y: " << getCoordY() << std::endl;
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
// void node::imprimirQTable(std::fstream& file) {
//     // Impresion de sim.csv
//     stateMatrix stateMatrixElement;
//     state stateAnterior;
//     for (int i = 0; i < qTable.size(); i++) {
//         getQTable()->at(i).mostrarQ();
//         std::cout << std::endl;
//         // !-----------------------------------------------------------------------
//         // Primer stateActionQ
//         if (i == 0) {
//             // Set idNode en stateMatrixElement. Es el id del nodo de la interseccion.
//             stateMatrixElement.setIdNode(getQTable()->at(i).getA().getIdLink());
//             // Set stateValue en stateMatrixElement. Es el state de la interseccion. 
//             stateMatrixElement.setStateValue(getQTable()->at(i).getS());
//             // Set valor de Q en el vectorQ en la locacion i.
//             stateMatrixElement.agregarQ(getQTable()->at(i).getA().getILinkConnection(), getQTable()->at(i).getQ());
//         }
//         // !-----------------------------------------------------------------------
//         // Siguiente stateActionQ
//         else {
//             // !-----------------------------------------------------------------------
//             // Si no hay cambio de state realiza lo siguiente
//             if (!(verificarCambioState(stateAnterior, qTable[i].getS()))) {
//                 // Set valor de Q en el vectorQ en la locacion i.
//                 stateMatrixElement.agregarQ(qTable[i].getA().getILinkConnection(), qTable[i].getQ());
//             }
//             else {
//                 // !-----------------------------------------------------------------------
//                 // Imprime el stateMatrixElement final
//                 stateMatrixElement.imprimirStateMatrix(file);
//                 // !-----------------------------------------------------------------------
//                 // Continua con un nuevo stateMatrixElement
//                 // Set idNode en stateMatrixElement. Es el id del nodo de la interseccion.
//                 stateMatrixElement.setIdNode(qTable[i].getA().getIdLink());
//                 // Set stateValue en stateMatrixElement. Es el state de la interseccion. 
//                 stateMatrixElement.setStateValue(qTable[i].getS());
//             }
//         }
//         // Guarda el state del stateActionQ anterior.
//         stateAnterior = qTable[i].getS();
//         // Guardar stateMatrixElement y el vector dbStateMatrix
//     }
// }


