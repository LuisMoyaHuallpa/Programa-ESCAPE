#ifndef stateMatrix_h
#define stateMatrix_h
/*---------------------------------------------------------------------------*\
Una fila de archivo de entrada o salida.
\*---------------------------------------------------------------------------*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header generales
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <fstream>
#include <vector>
#include "variant"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "pedestrianMassState.h"
#include "Q.h"

// forward declaration
class node;
class nodeEvacuation;


class stateMatrix {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // id        |-->| ID DEL STATEMATRIX
    // nodeId    |-->| PUNTERO A NODO DONDE SE PUEDE EXPERIMENTAR LOS ESTADOS
    // state     |-->| ESTADO EXPERIMENTADO ESTA COMPUESTO DE LAS DENSIDADES DE LOS LINK CONECTADOS
    // Qs        |-->| Q DE LOS LINK EN UN STATE EXPERIMENTADO
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int id;
    const node* const nodoPtr;
    const std::vector<int> state;
    std::vector<Q> Qs;
    
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static const int tamanoVectorIO;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    stateMatrix();
    stateMatrix(const node* const nodePtr, const std::vector<int> state);
    stateMatrix(const nodeEvacuation* const nodeEvacuationPtr, const std::vector<int> state);
    stateMatrix(const node* const nodePtr, const std::vector<int> state, std::vector<Q> Qs);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getter
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getId() const;
    const node* const getNodePtr() const;
    const std::vector<int> getState() const;
    std::vector<Q>& getQs();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static getter
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int static getTamanoVector();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    bool operator==(stateMatrix stateMatrix2);
    stateMatrix* buscarStateMatrix(std::vector<int> state) const;
    Q* buscarQ(link* callePtr);
    const Q* buscarQMax() ;
    void mostrarStateMatrix() const;
    void imprimirState(std::fstream& file) const;
    void imprimirQs(std::fstream& file) const;
    void imprimirStateMatrix(std::fstream& file) const;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static stateMatrix* creacionObtencionStateMatrix(
        node* const nodo,
        const std::vector<int> stateObservado);


};
#endif
