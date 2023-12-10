#include "stateMatrix.h"
#include "action.h"
#include <fstream>
#include <vector>

stateMatrix::stateMatrix() {
  
}
stateMatrix::stateMatrix(int idNode, state stateValue, std::vector<double> QVector, std::vector<int> otrosVector) {
    setIdNode(idNode);
    setStateValue(stateValue);
    setQVector(QVector);
    setOtrosVector(otrosVector);
}

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

int stateMatrix::getIdNode() {
    return idNode;  
}
state stateMatrix::getStateValue() {
    return stateValue;
}
std::vector<double> stateMatrix::getQVector() {
    return QVector;
}
std::vector<int> stateMatrix::getotrosVector() {
    return otrosVector;
}

void stateMatrix::enviarDataNode(node* nodeAGuardar) {
    // Envia los datos leidos del csv al QTable de cada nodo.
    for (int i = 0; i < stateValue.getDensityLinks().size(); i++) {
        stateActionQ qAGuardar(stateValue, nodeAGuardar->getLinkConnection().at(i)->getIdLink(),QVector[i]);
        nodeAGuardar->addqQTable(qAGuardar);
    }
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
        file << QVector[i] << ",";
    }
    std::cout << std::endl;
}
