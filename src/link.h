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
#include <stdexcept>
#include "iomanip"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// #include "subLink.h"
#include "vector2D.h"
#include "vector"
#include "nodes.h"
#include "dictionary.h"

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
    std::vector<int> pedestriansInSublink;
    int densityLevel;
    double anchoDivisiones;
    
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static int numberDivisiones;

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
    void setPedestriansInSublink(std::vector<int> pedestriansInSublink);
    void setDensityLevel(int densityLevel);
    void setAnchoDivisiones(double anchoDivisiones);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getIdLink() const;
    int getIdNode1() const;
    int getIdNode2() const;
    int getLength() const;
    int getWidth() const;
    vector2D getOrientacionLink() const;
    std::vector<int>& getPedestriansInSublink();
    int getDensityLevel();
    double getAnchoDivisiones();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void calcularHistParam();
    vector2D calcularDirectionLink();
    void creacionLinkConnection();
    void calcularOrientacionLink();
    int calcularNumberPartion();
    void calcularDensityLevel();
    void calcularAnchoDivisiones();
    void mostrarLink();
    void imprimirLink(std::fstream& file);
    void mostrarSubLink();

    // void calcularSubdivision();
    // void guardarLinkConnection();
};
#endif

