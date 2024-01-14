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

class node {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idNode            |-->| ID DE LA INTERSECCION
    // coordX            |-->| COORDENADA X DEL NODO 
    // coordY            |-->| COORDENADA Y DEL NODO
    // idLinkConnection  |-->| 
    // stateMatrixTable  |-->| 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int idNode;
    double coordX;
    double coordY;
    std::vector<int> idLinkConnection;
    std::vector<stateMatrix> stateMatrixTable;

public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    node();
    node(int id, int coordX, int coordY);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setIdNode(int idNode);
    void setCoorX(double coordX);
    void setCoorY(double coordY);
    void setIdLinkConnection(std::vector<int> idLinkConnection);
    void setStateMatrixTable(std::vector<stateMatrix> stateMatrixTable);
    // void setRewardCode(int rewardCode);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getIdNode() const;
    double getCoordX() const;
    double getCoordY() const;
    std::vector<int> getIdLinkConnection();
    std::vector<stateMatrix>& getStateMatrixTable();
    // int getRewardCode() const;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void agregarLink(link* link);
    void buscarStateMatrix(stateMatrix stateMatrixBuscando, bool& verificarStateMatrix, int idq);
    // void addqQTable(stateActionQ qElemento);
    void addIdLinkConnection(int idLink);
    // void ordenarQTable();
    // void crearStateMatrix();
    bool verificarCambioState(state stateAnterior, state stateActual);
    void mostrarNode();
    void mostrarQTable();
    // void imprimirQTable(std::fstream& file);

};
#endif
