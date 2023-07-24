#include <string>
class node {
private:
    int number;
    int coordX;
    int coordY;
    int evacuationCode;
    int rewardCode;
    

public:
    node();
    node(int number, int coordX, int coordY, int evacuationCode, int rewardCode);
    
    //setters
    void setNumber(int number);
    void setCoorX(int setcoordX);
    void setCoorY(int setcoordY);
    void setEvacuationCode(int evacuationCode);
    void setRewardCode(int rewardCode);

    // getters
    int getNumber() const;
    int getCoordX() const;
    int getCoordY() const;
    int getEvacuationCode() const;
    int getRewardCode() const;
    void imprimir();

    

};
