#ifndef node_h
#define node_h

#include <fstream>
#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include "link.h"
#include "q.h"
// #include "states.h"

class link;
class node {
private:
    int idNode;
    int coordX;
    int coordY;
    std::vector<link*> linkConnection;
    std::vector<q> qTable;

public:
    node();
    node(int id, int coordX, int coordY);

    virtual ~node() {} // Destructor virtual

    //setters
    void setIdNode(int id);
    void setCoorX(int coordX);
    void setCoorY(int coordY);
    void setEvacuationCode(int evacuationCode);
    void setRewardCode(int rewardCode);
    void setLinkConnection(std::vector<link*> linkConnection);

    // getters
    int getIdNode() const;
    int getCoordX() const;
    int getCoordY() const;
    int getEvacuationCode() const;
    int getRewardCode() const;
    std::vector<link*> getLinkConnection();
    std::vector<q>getQTable();
    
    void agregarLink(link* link);
    void buscarQ(q qBuscando, bool* verificarQ, int idq);
    void addqQTable(q qElemento);
    void ordenarQTable();
    void mostrarNode();
    void mostrarQTable();
    void imprimirQTable(std::fstream& file);
};
#endif
