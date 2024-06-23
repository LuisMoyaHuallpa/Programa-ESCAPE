#include "stateMatrix.h"
#include "pedestrianMassState.h"
#include <vector>

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
stateMatrix::stateMatrix(state stateValue) {
    setStateValue(stateValue);  
    QsValue.getQsVector().resize(stateValue.getDensityLinks().size(), 0);
    pedestrianMassStateValue.getPedestrianMassStateVector().resize(stateValue.getDensityLinks().size(), 0);
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
void stateMatrix::setPedestrianMassState(pedestrianMassState pedestrianMassStateValue) {
    (*this).pedestrianMassStateValue = pedestrianMassStateValue;
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
pedestrianMassState &stateMatrix::getPedestrianMassState() {
    return pedestrianMassStateValue;  
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
    if (stateValue.getDensityLinks().size() == stateMatrix2.getStateValue().getDensityLinks().size()) {
        // la comparacion es con el state, el state es como id del stateMatrix en un mismo nodo
        if (stateValue == stateMatrix2.getStateValue()) {
            return true;
        }
    }
    return false;
}
// struct stateM {
//     si
// }

// void stateMatrix::enviarDataNode(node* nodeAGuardar) {
    // Envia los datos leidos del csv al QTable de cada nodo.
    // for (int i = 0; i < stateValue.getDensityLinks().size(); i++) {
    //     stateActionQ qAGuardar(stateValue, nodeAGuardar->getLinkConnection().at(i)->getIdLink(),QVector[i]);
    //     nodeAGuardar->addqQTable(qAGuardar);
    // }
// }
void stateMatrix::mostrarStateMatrix() const {
    /* muestra en la terminal cada linea del stateMatrix. */
    // state value
    stateValue.mostrarState();
    /* imprime 0 en donde no hay state debido a que siempre imprime 10 elementos state. */
    // for (int i = 0; i < tamanoVector - getStateValue().getDensityLinks().size(); i++) {
    //     std::cout << "0,";
    // }
    std::cout << "action: ";
    actionValue.mostrarAction();
    std::cout << "iTable: ";
    std::cout << iStateMatrixTable;
    std::cout << "Qs: ";
    QsValue.mostrarQs();
    std::cout << "pedestrianMassState: ";
    pedestrianMassStateValue.mostrarPedestrianMassStateVector();
    std::cout << std::endl;


}
void stateMatrix::imprimirStateMatrix(std::fstream& file) const {
   // Imprimir una fila del elemento stateMatrix.
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de state y se completa con 0 para llegar a
    // 10 elementos.
    stateValue.imprimirState(file);
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de Q y se completa con 0 para llegar a
    // 10 elementos.
    QsValue.imprimirQs(file);
    // Imprimir todos los elementos de pedestrianMassState y se completa con 0 para llegar a
    // 10 elementos.
    pedestrianMassStateValue.imprimirPedestrianMassStateVector(file);
    file << std::endl;
}
