#ifndef node_h
#define node_h

#include <string>
#include <iostream>
#include <ostream>
#include <vector>
// class link; // Declaración previa de la clase links para que nodes lo reconozca

class node {
private:
    int idNode;
    int coordX;
    int coordY;
    // puede cambiar a bolean, el evacuationCode porque te dice
    // si el node es un punto de evacuacion
    int evacuationCode;
    int rewardCode;

public:
    std::vector<int> linkConnection;




public:
    // friend class link;
    node();
    node(int id, int coordX, int coordY, int evacuationCode, int rewardCode);
    
    //setters
    void setIdNode(int id);
    void setCoorX(int setcoordX);
    void setCoorY(int setcoordY);
    void setEvacuationCode(int evacuationCode);
    void setRewardCode(int rewardCode);
    void setLinkConnection(std::vector<int> idLink);

    // getters
    int getIdNode() const;
    int getCoordX() const;
    int getCoordY() const;
    int getEvacuationCode() const;
    int getRewardCode() const;
    std::vector<int> getLinkConnection();
    


    void agregarLink(int idLink);
    void imprimirNode();


    

};
#endif
