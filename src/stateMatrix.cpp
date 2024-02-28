#include "stateMatrix.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int stateMatrix::tamanoVectorIO = 10;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrix::stateMatrix() : stateValue() {
    setIStateMatrixTable(0);
    // otrosVector.resize(tamanoVector,0);
}
stateMatrix::stateMatrix(state stateValue, std::vector<double> QVector, std::vector<int> otrosVector) {
    setStateValue(stateValue);
    setOtrosVector(otrosVector);
    setIStateMatrixTable(0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void stateMatrix::setStateValue(state stateValue) {
    (*this).stateValue = stateValue;  
}
void stateMatrix::setQsValue(Qs QsValue) {
    (*this).QsValue = QsValue;
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
state& stateMatrix::getStateValue() {
    return stateValue;
}
Qs &stateMatrix::getQsValue() {
    return QsValue;
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
// static getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int stateMatrix::getTamanoVector() {
    return tamanoVectorIO;
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
    std::cout << "iTable: ";
    std::cout << getIStateMatrixTable();
    std::cout << "Qs: ";
    getQsValue().mostrarQs();
    std::cout << std::endl;


}
void stateMatrix::imprimirStateMatrix(std::fstream& file){
   // Imprimir una fila del elemento stateMatrix.
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de state y se completa con 0 para llegar a
    // 10 elementos.
    stateValue.imprimirState(file);
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de Q y se completa con 0 para llegar a
    QsValue.imprimirQs(file);
    file << std::endl;
}
