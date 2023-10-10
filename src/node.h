#ifndef node_h
#define node_h

#include <string>
#include <iostream>
#include <ostream>
#include <vector>
#include "link.h"
#include "qTable.h"

class link;
class node {
private:
    int idNode;
    int coordX;
    int coordY;
    std::vector<link*> linkConnection;
    qTable q;

public:
    node();
    node(int id, int coordX, int coordY);

    virtual ~node() {} // Destructor virtual

    
    //setters
    void setIdNode(int id);
    void setCoorX(int setcoordX);
    void setCoorY(int setcoordY);
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
    qTable getQ();


    void agregarLink(link* link);
    void imprimirNode();

};
#endif
