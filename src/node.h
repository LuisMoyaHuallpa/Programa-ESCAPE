#ifndef node_h
#define node_h
/*---------------------------------------------------------------------------*\
Punto de interseccion de calles.
\*---------------------------------------------------------------------------*/
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header generales
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <fstream>
#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include "pedestrian.h"
#include "state.h"
#include "unordered_map"
#include "map"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "stateMatrix.h"
#include "vector2D.h"

// forward declaration
class link;
// class pedestrian;

class node {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idNode            |-->| ID DE LA INTERSECCION
    // coordenada        |-->| COORDENADA X Y DEL NODO
    // linkConnection    |-->| PUNTERO A LAS CALLES CONECTADAS A LA INTERSECCION
    // stateMatrixTable  |-->| MAP Y TABLA DE STATEMATRIX DE LA INTERSECCION
    // densityLevelNode  |-->| PUNTERO A LA DENSIDAD DE LA CALLES CONECTADAS
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int idNode;
    const vector2D coordenada;
    mutable std::vector<link*> linkConnectionsPtr;
    std::vector<stateMatrix*> stateMatrixsExperimentosPtr;

public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    node(int id, vector2D coordenada);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // destrutor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // virtual ~node() {}

    virtual std::string getNodeType();
    

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getIdNode() const;
    const vector2D getCoordenada() const;
    const std::vector<link*> getLinkConnectionsPtr() const;
    std::vector<stateMatrix*>& getStateMatrixExperimentadosPtr();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void buscarStateMatrix(stateMatrix stateMatrixBuscando, bool& verificarStateMatrix, int& iStateMatrixTable);
    const node* buscarNodoFinal(link* callePtr) const;
    bool verificarCambioState(state stateAnterior, state stateActual);
    estadoPedestrian verificarNodoEvacuation() const;
    std::vector<int> stateObservado() const;
    double distanciaA(const node* nodo2) const;
    void addLink(link* calle);
    void mostrarNode() const;
    // void mostrarQTable() const;
    // void imprimirQTable(std::fstream& file) const;

};
#endif
