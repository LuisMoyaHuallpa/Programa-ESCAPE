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
    const int idNode1;
    const int idNode2;
    int length;
    int width;
    vector2D orientacionLink;
    std::vector<int> pedestriansInSublink;
    std::vector<double> densityInSublink;
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
    // link();
    link(int idLink, int idNode1, int idNode2, int length, int width);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setIdLink(int idLink);
    void setLength(int length);
    void setWidth(int width);
    void setOrientacionLink(vector2D orientacionLink);
    void setPedestriansInSublink(std::vector<int> pedestriansInSublink);
    void setDensityInSublink(std::vector<double> densityInSublink);
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
    std::vector<double>& getDensityInSublink();
    int getDensityLevel();
    double getAnchoDivisiones();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void calcularOrientacionLink();
    void calcularAnchoDivisiones();
    void calcularDensity();
    void calcularDensityLevel();
    void mostrarLink();
    void mostrarSubLink();
    void imprimirLink(std::fstream& file);

    // void calcularSubdivision();
    // void guardarLinkConnection();
};
#endif

