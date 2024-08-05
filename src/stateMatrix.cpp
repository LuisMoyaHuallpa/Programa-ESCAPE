#include "stateMatrix.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "Q.h"
#include "state.h"
#include "stateMatrixs.h"
#include <vector>
#include "link.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int stateMatrix::tamanoVectorIO = 10;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrix::stateMatrix()
    :
    id(0),
    nodoPtr(nullptr)
{
  
}
stateMatrix::stateMatrix(const node* const node, const std::vector<int> state)
    :
    id(0),
    nodoPtr(node),
    state(state)
{
    const std::vector<link*> linkConnectionsPtr = nodoPtr->getLinkConnectionsPtr();
    for (link* linkConnection : linkConnectionsPtr) {
        Qs.emplace_back(linkConnection);
    } 
}
stateMatrix::stateMatrix(const node *const nodePtr, const std::vector<int> state, std::vector<Q> Qs)
    : id(0), nodoPtr(nodePtr), state(state), Qs(Qs){
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
const node* const stateMatrix::getNodePtr() const {
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
Q* stateMatrix::buscarQMax() {

    /* calcular el maximo Q del vector de Qs*/
    // double qmax = 0;
    // for (auto q : Qs) {
    //     if (*(q.getValor())>qmax) {
    //         qmax = *(q.getValor());
    //         Q* ref = &q;
    //     }
    // }
    // return ref;
   auto maxElementIt = std::max_element(Qs.begin(), Qs.end(),
   [](const Q& a, const Q& b)
       {
           return a.getValor() < b.getValor();
       });
   // return nullptr;
}
void stateMatrix::mostrarStateMatrix() const {
    /* muestra en la terminal cada linea del stateMatrix. */
    // id del nodo
    std::cout << "id:" << nodoPtr->getIdNode() << " ";
    // state 
    std::cout << "s:";
    for (const int &value : state) {
        std::cout << value << " ";
    }
    // Q
    std::cout << "Qs: ";
    for(const Q &q : Qs){
        q.mostrarQs(); 
    }
    // salto de linea
    std::cout << std::endl;
}
void stateMatrix::imprimirState(std::fstream &file) const {
    /* impresion de estados en un arreglo de 10 columnas*/
    for (int i = 0; i < stateMatrix::tamanoVectorIO; i++) {
        if (i < state.size()) {
            file << state.at(i) << ',';
        } else {
            file << "0,";
        }
    }
}
void stateMatrix::imprimirQs(std::fstream &file) const {
    /* impresion de Q en un arreglo de 10 columnas*/
    for (int i = 0; i < stateMatrix::tamanoVectorIO; i++) {
        if (i < Qs.size()) {
            file << Qs.at(i).getValor() << ',';
        } else {
            file << "0,";
        }
    }  
}
void stateMatrix::imprimirStateMatrix(std::fstream& file) const {
   // Imprimir una fila del elemento stateMatrix.
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de state y se completa con 0 para llegar a
    // 10 elementos.
    imprimirState(file);
    // !-----------------------------------------------------------------------
    // Imprimir todos los elementos de Q y se completa con 0 para llegar a
    // 10 elementos.
    imprimirQs(file);
    // Imprimir todos los elementos de pedestrianMassState y se completa con 0 para llegar a
    // 10 elementos.
    // pedestrianMassStateValue.imprimirPedestrianMassStateVector(file);
    file << std::endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrix* stateMatrix::creacionObtencionStateMatrix(
    node* const nodo,
    const std::vector<int> stateObservado)
{
    /* cuando una persona llega a un nodo, con lo observado busca en el nodo
        donde esta si el stateMatrixExperimentado se encuentra en caso contrario lo crea
        */
    std::vector<stateMatrix*> stateMatrixExperimentados = nodo->getStateMatrixExperimentadosPtr();
    // loop para buscar cada lista de stateMatrix
    for (stateMatrix* stateMatrixExperimentado : stateMatrixExperimentados) {
       // si stateMatrixExperiemntado es igual al stateObservado entonces si existe ese stateMatrix
        if (stateMatrixExperimentado->getState() == stateObservado) {
            return stateMatrixExperimentado; 
        }
    }
    // creacion del stateMatrix experimentado
    stateMatrix* nuevoStateMatrix = new stateMatrix(nodo, stateObservado);
    std::vector<stateMatrix*>& dbStateMatrix = stateMatrixs::get()->getDbStateMatrixs();
    dbStateMatrix.emplace_back(nuevoStateMatrix);
    stateMatrixExperimentados.push_back(nuevoStateMatrix);
    return nuevoStateMatrix;
}
