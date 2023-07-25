#ifndef node_h
#define node_h

#include <string>

class node {
private:
    int id;
    int coordX;
    int coordY;
    int evacuationCode;
    int rewardCode;
    

public:
    node();
    node(int id, int coordX, int coordY, int evacuationCode, int rewardCode);
    
    //setters
    void setId(int id);
    void setCoorX(int setcoordX);
    void setCoorY(int setcoordY);
    void setEvacuationCode(int evacuationCode);
    void setRewardCode(int rewardCode);

    // getters
    int getId() const;
    int getCoordX() const;
    int getCoordY() const;
    int getEvacuationCode() const;
    int getRewardCode() const;
    void imprimir();

    

};
#endif
