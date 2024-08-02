#include "stateMatrix.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "stateMatrixs.h"
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int stateMatrix::tamanoVectorIO = 10;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrix::stateMatrix()
    :
    id(0)
{
  
}
stateMatrix::stateMatrix(const node *node, const std::vector<int> state)
    :
    id(0),
    nodoPtr(node),
    state(state)
{
  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int stateMatrix::getId() const {
    return id;
}
const node* stateMatrix::getNodePtr() const {
    return nodoPtr;
}
const std::vector<int> stateMatrix::getState() const {
    return state;    
}
std::vector<Q> &stateMatrix::getQs() {
    return Qs;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int stateMatrix::getTamanoVector() {
    return tamanoVectorIO;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// method 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// void stateMatrix::mostrarStateMatrix() {
//     /* muestra en la terminal cada linea del stateMatrix. */
//     // state value
//     stateValue.mostrarState();
//     /* imprime 0 en donde no hay state debido a que siempre imprime 10 elementos state. */
//     // for (int i = 0; i < tamanoVector - getStateValue().getDensityLinks().size(); i++) {
//     //     std::cout << "0,";
//     // }
Q* stateMatrix::buscarQ(link *callePtr) {
    /* Obtener Q segun la calle ejecutada*/
    for (Q& q : Qs) {
        // Comparar el puntero calle del objeto Q con callePtr
        if (q.getCallePtr() == callePtr) {
            // Retornar un puntero al objeto Q encontrado
            return &q;
        }
    }
    return nullptr;
}
void stateMatrix::mostrarStateMatrix() const {
    /* muestra en la terminal cada linea del stateMatrix. */
    // id del nodo
    std::cout << nodoPtr->getIdNode();
    // state value
    /* imprime 0 en donde no hay state debido a que siempre imprime 10 elementos state. */
    // for (int i = 0; i < tamanoVector - getStateValue().getDensityLinks().size(); i++) {
    //     std::cout << "0,";
    // }
    // std::cout << "action: ";
    // actionValue.mostrarAction();
    std::cout << "Qs: ";
    for(Q q : Qs){
        q.mostrarQs(); 
    }
    std::cout << std::endl;


}
// void stateMatrix::imprimirStateMatrix(std::fstream& file) {
//    // Imprimir una fila del elemento stateMatrix.
//     // !-----------------------------------------------------------------------
//     // Imprimir todos los elementos de state y se completa con 0 para llegar a
//     // 10 elementos.
//     stateValue.imprimirState(file);
//     // !-----------------------------------------------------------------------
//     // Imprimir todos los elementos de Q y se completa con 0 para llegar a
//     // 10 elementos.
//     QsValue.imprimirQs(file);
//     // Imprimir todos los elementos de pedestrianMassState y se completa con 0 para llegar a
//     // 10 elementos.
//     pedestrianMassStateValue.imprimirPedestrianMassStateVector(file);
//     file << std::endl;
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrix* stateMatrix::creacionObtencionStateMatrix(
    node* nodo,
    const std::vector<int>& stateObservado)
{
    std::vector<stateMatrix*> stateMatrixExperimentados = nodo->getStateMatrixExperimentadosPtr();
    // loop para buscar cada lista de stateMatrix
    for (stateMatrix* stateMatrixExperimentado : stateMatrixExperimentados) {
        // si stateMatrixExperiemntado es igual al stateObservado entonces si existe ese stateMatrix
        if (stateMatrixExperimentado->getState() == stateObservado) {
            return stateMatrixExperimentado; 
        }
    }
    std::vector<stateMatrix>& dbStateMatrix = stateMatrixs::get()->getDbStateMatrixs();
    dbStateMatrix.emplace_back(nodo, stateObservado);
    return &dbStateMatrix.back();
}
