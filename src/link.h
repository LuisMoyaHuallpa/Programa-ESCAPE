#ifndef link_h
#define link_h
/*---------------------------------------------------------------------------*\
Una calle.
\*---------------------------------------------------------------------------*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header generales
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <fstream>
#include <vector>
#include <cmath>
#include <iostream>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "subLink.h"
#include "vector2D.h"
#include "vector"

class link{
    
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idLink           |-->| ID DE LA CALLE
    // idNode1          |-->| INTERSECCION DE LA CALLE  
    // idNode2          |-->| LA OTRA INTERSECCION DE LA CALLE 
    // length           |-->| LARGO DE LA CALLE
    // width            |-->| ANCHO DE LA CALLE
    // orientacionLink  |-->| ANGULO QUE FORMA LA HORIZONTAL CON LA CALLE
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int idLink;
    int idNode1;
    int idNode2;
    int length;
    int width;
    vector2D orientacionLink;
    int numberPartion;
    std::vector<subLink> subLinks;
    int densityLevel;
    
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static int unitWidthPartion;
    int static getUnitWidthPartion();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    link();
    link(int idLink, int idNode1, int idNode2, int length, int width);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setIdLink(int idLink);
    void setIdNode1(int idNode1);
    void setIdNode2(int idNode2);
    void setLength(int length);
    void setWidth(int width);
    void setOrientacionLink(vector2D orientacionLink);
    void setSubLinks(std::vector<subLink> subLinks);
    void setDensityLevel(int densityLevel);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getIdLink() const;
    int getIdNode1() const;
    int getIdNode2() const;
    int getLength() const;
    int getWidth() const;
    vector2D getOrientacionLink() const;
    int getNumberPartion();
    std::vector<subLink>& getSubLinks();
    int getDensityLevel();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void calcularHistParam();
    vector2D calcularDirectionLink();
    void creacionLinkConnection();
    void calcularOrientacionLink();
    int calcularNumberPartion();
    void calcularDensityLevel();
    void mostrarLink();
    void imprimirLink(std::fstream& file);
    void mostrarSubLinks();

    // void calcularSubdivision();
    // void guardarLinkConnection();
};
#endif

