#ifndef link_h
#define link_h

// #include "node.h"
class node;

class link{
    
private:
    int idLink;
    node* node1;
    node* node2;
    int length;
    int width;

    int numberPartion;


    
public:
    static int unitWidthPartion;
    int static getUnitWidthPartion();

    link();
    link(int id, node* node1, node* node2, int length, int width);

    /* setters */
    void setIdLink(int id);
    void setNode1(node* node1);
    void setNode2(node* node2);
    void setLength(int length);
    void setWidth(int width);

   /* getters  */
    int getIdLink() const;
    node* getNode1() const;
    node* getNode2() const;
    int getLength() const;
    int getWidth() const;

    void mostrarLink();
    void calcularHistParam();
    // void guardarLinkConnection();
};
#endif

