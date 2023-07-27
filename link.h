#ifndef link_h
#define link_h

#include "node.h"

// class dbNode;
class link{
    
private:
    int id;
    node node1;
    node node2;
    int length;
    int width;

    int numberPartion;
    

public:
    static int unitWidthPartion;
    link();
    link(int id, int idNode1, int idNode2, int length, int width);

    /* setters */
    void setId(int id);
    void setNode1(int idNode1);
    void setNode2(int idNode2);
    void setLength(int length);
    void setWidth(int width);

   /* getters  */
    int getId() const;
    node getNode1() const;
    node getNode2() const;
    int getLength() const;
    int getWidth() const;


    
    void calcularHistParam();

};
    #endif

