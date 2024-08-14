#include "stateMatrix.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "Q.h"
#include "nodeEvacuation.h"
#include "pedestrian.h"
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
stateMatrix::stateMatrix(const nodeEvacuation* const nodeEvacuationPtr, const std::vector<int> state)
    :
    id(0),
    nodoPtr(nodeEvacuationPtr),
    state(state),
    Qs(1, Q())
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
    // const std::vector<link*> linkConnectionsPtr = nodoPtr->getLinkConnectionsPtr();
    // for (link* linkConnection : linkConnectionsPtr) {
    //     Qs.emplace_back(linkConnection);
    // } 
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
    // cuando es nodeEvacuacion la calle apunta a un nullptr
    // solo trenda un Q
    if(callePtr == nullptr)
    {
        return &(Qs.at(0));
    }
    else {
    /* Obtener Q segun la calle ejecutada*/
        for (Q& q : Qs) {
            // Comparar el puntero calle del objeto Q con callePtr
            if (q.getCallePtr() == callePtr) {
                // Retornar un puntero al objeto Q encontrado
                return &q;
            }
        }
    }
    return nullptr;
}
// Q* stateMatrix::buscarQMax() {
//     /* seleciona el mayor valor Q del vector Qs,
//         en caso sean todos iguales elegir aletoriamente*/
//    auto maxElementIt = std::max_element(Qs.begin(), Qs.end(),
//    [](const Q& a, const Q& b)
//        {
//            return a.getValor() < b.getValor();
//        });
//    return  maxElementIt.base();
// }
const Q* stateMatrix::buscarQMax() {
    // Encontrar el valor máximo
    auto maxElementIt = std::max_element(Qs.begin(), Qs.end(),
                                         [](const Q& a, const Q& b) {
                                             return a.getValor() < b.getValor();
                                         });
    double maxValue = *(maxElementIt->getValor());
    // Recopilar todos los elementos que tienen el valor máximo
    std::vector<const Q*> maxElements;
    for (const auto& q : Qs) {
        if (q.getValor() == maxValue) {
            maxElements.push_back(&q);
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, maxElements.size() - 1);
    // Generar un índice aleatorio
    int randomIndex = dis(gen);
    // Obtener el elemento aleatorio
    const Q* randomElement = maxElements[randomIndex];
    return randomElement; // Devolver uno de los máximos aleatorios
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
    file << nodoPtr->getIdNode() << ",";
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
    std::vector<stateMatrix*>* stateMatrixExperimentados = nodo->getStateMatrixExperimentadosPtr();
    // loop para buscar cada lista de stateMatrix
    for (stateMatrix* stateMatrixExperimentado : *stateMatrixExperimentados) {
       // si stateMatrixExperiemntado es igual al stateObservado entonces si existe ese stateMatrix
        if (stateMatrixExperimentado->getState() == stateObservado) {
            return stateMatrixExperimentado; 
        }
    }
    // creacion del stateMatrix experimentado
    stateMatrix* nuevoStateMatrix = (dynamic_cast<nodeEvacuation*>(nodo)) 
        ? new stateMatrix(static_cast<nodeEvacuation*>(nodo), stateObservado)
        : new stateMatrix(nodo, stateObservado);
    std::vector<stateMatrix*>& dbStateMatrix = stateMatrixs::get()->getDbStateMatrixs();
    dbStateMatrix.emplace_back(nuevoStateMatrix);
    nodo->addStateMatrixExperimentadosPtr(nuevoStateMatrix);
    return nuevoStateMatrix;
}
