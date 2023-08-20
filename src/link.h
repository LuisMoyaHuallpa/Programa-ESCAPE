#ifndef link_h
#define link_h

// #include "node.h"
#include "subLink.h"
#include "vector2D.h"
#include "vector"
#include <fstream>
#include <vector>
class node;

class link{
    
private:
    int idLink;
    node* node1;
    node* node2;
    int length;
    int width;

    int numberPartion;
    std::vector<subLink> subLinks;


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
    void setSubLinks(std::vector<subLink> subLinks);

   /* getters  */
    int getIdLink() const;
    node* getNode1() const;
    node* getNode2() const;
    int getLength() const;
    int getWidth() const;
    int getNumberPartion();
    std::vector<subLink>& getSubLinks();

    void mostrarLink();
    void imprimirLink(std::fstream& file);
    void calcularHistParam();
    vector2D calcularDirectionLink();
    void creacionLinkConnection();
    void calcularNumberPartion();
    void mostrarSubLinks();
    // void calcularSubdivision();
    // void guardarLinkConnection();
};
#endif

