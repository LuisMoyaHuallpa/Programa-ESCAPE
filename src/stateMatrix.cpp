#include "stateMatrix.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int stateMatrix::tamanoVector = 10;
int stateMatrix::getTamanoVector() {
    return tamanoVector;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrix::stateMatrix() : stateValue() {
    (*this).idNode = 0;
    QVector.resize(tamanoVector, 0);
    setIStateMatrixTable(0);
    // otrosVector.resize(tamanoVector,0);
}
stateMatrix::stateMatrix(int idNode, state stateValue, std::vector<double> QVector, std::vector<int> otrosVector) {
    setIdNode(idNode);
    setStateValue(stateValue);
    setQVector(QVector);
    setOtrosVector(otrosVector);
    setIStateMatrixTable(0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void stateMatrix::setIdNode(int idNode) {
    (*this).idNode = idNode;
}
void stateMatrix::setStateValue(state stateValue) {
    (*this).stateValue = stateValue;  
}
void stateMatrix::setQVector(std::vector<double> QVector) {
    (*this).QVector = QVector;
}
void stateMatrix::setOtrosVector(std::vector<int> otrosVector) {
    (*this).otrosVector = otrosVector;
}
void stateMatrix::setActionValue(action actionValue) {
    (*this).stateValue = stateValue;
}
void stateMatrix::setIStateMatrixTable(int iStateMatrixTable) {
    (*this).iStateMatrixTable = iStateMatrixTable;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int stateMatrix::getIdNode() {
    return idNode;  
}
state& stateMatrix::getStateValue() {
    return stateValue;
}
std::vector<double>& stateMatrix::getQVector() {
    return QVector;
}
std::vector<int>& stateMatrix::getotrosVector() {
    return otrosVector;
}
action& stateMatrix::getActionValue() {
    return actionValue;
}
int stateMatrix::getIStateMatrixTable() {
    return iStateMatrixTable;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool stateMatrix::operator==(stateMatrix stateMatrix2) {
    /* compara si dos stateMatrix son iguales */
    // primero compara si el tamaño de los states son iguales
    if (getStateValue().getDensityLinks().size() == stateMatrix2.getStateValue().getDensityLinks().size()) {
        // compara la action y el state
        if (getStateValue() == stateMatrix2.getStateValue()) {
            return true;
        }
    }
    return false;
}
void stateMatrix::agregarQ(int i, double Q) {
    QVector[i] = Q;
    std::cout << Q << std::endl;
    std::cout << QVector[i] << std::endl;
    std::cout << i << std::endl;
    for (int i = 0; i < QVector.size(); i++) {
        std::cout << getQVector().at(i) << ",";
    }

}
// void stateMatrix::enviarDataNode(node* nodeAGuardar) {
    // Envia los datos leidos del csv al QTable de cada nodo.
    // for (int i = 0; i < stateValue.getDensityLinks().size(); i++) {
    //     stateActionQ qAGuardar(stateValue, nodeAGuardar->getLinkConnection().at(i)->getIdLink(),QVector[i]);
    //     nodeAGuardar->addqQTable(qAGuardar);
    // }
// }
void stateMatrix::mostrarStateMatrix() {
    /* muestra en la terminal cada linea del stateMatrix. */
    // state value
    getStateValue().mostrarState();
    /* imprime 0 en donde no hay state debido a que siempre imprime 10 elementos state. */
    // for (int i = 0; i < tamanoVector - getStateValue().getDensityLinks().size(); i++) {
    //     std::cout << "0,";
    // }
    std::cout << "action: ";
    actionValue.mostrarAction();
    std::cout << "itable: ";
    std::cout << getIStateMatrixTable();
    std::cout << "Qs: ";
    for (int i = 0; i < QVector.size(); i++) {
        std::cout << QVector[i] << ",";
    }
    std::cout << std::endl;


}
void stateMatrix::imprimirStateMatrix(std::fstream& file){
   // Imprimir una fila del elemento stateMatrix.
    // !-----------------------------------------------------------------------
    // Imprimir id del nodo.
    file << getIdNode() << ",";
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de state y se completa con 0 para llegar a
    // 10 elementos.
    stateValue.imprimirState(file);
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de state y se completa con 0 para llegar a
    // Falta verificar
    for (int i = 0; i < QVector.size(); i++) {
        file << getQVector().at(i) << ",";
    }
    file << std::endl;
}
