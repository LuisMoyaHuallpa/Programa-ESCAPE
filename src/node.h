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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "stateMatrix.h"
#include "vector2D.h"

// forward declaration
class link;

class node {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idNode            |-->| ID DE LA INTERSECCION
    // coordX            |-->| COORDENADA X DEL NODO 
    // coordY            |-->| COORDENADA Y DEL NODO
    // idLinkConnection  |-->| 
    // stateMatrixTable  |-->| 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int idNode;
    const vector2D coordenada;
    // std::vector<int> idLinkConnection;
    std::vector<link*> linkConnection;
    std::vector<stateMatrix> stateMatrixTable;

public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    node(int id, vector2D coordenada);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // destrutor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // virtual ~node() {}

    // virtual ~node();
    virtual std::string getNodeType();
    


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void setIdNode(int idNode);
    // void setIdLinkConnection(std::vector<int> idLinkConnection);
    void setStateMatrixTable(std::vector<stateMatrix> stateMatrixTable);
    // void setRewardCode(int rewardCode);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getIdNode() const;
    const vector2D getCoordenada() const;
    // std::vector<int>& getIdLinkConnection();
    std::vector<link*>& getLinkConnection();
    std::vector<stateMatrix>& getStateMatrixTable();
    // int getRewardCode() const;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void buscarStateMatrix(stateMatrix stateMatrixBuscando, bool& verificarStateMatrix, int& iStateMatrixTable);
    // void addqQTable(stateActionQ qElemento);
    // void ordenarQTable();
    // void crearStateMatrix();
    bool verificarCambioState(state stateAnterior, state stateActual);
    void mostrarNode();
    void mostrarQTable();
    void imprimirQTable(std::fstream& file);

};
#endif
