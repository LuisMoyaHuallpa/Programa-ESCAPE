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

class pedestrian;
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
    const int idLink;
    const node* node1;
    const node* node2;
    const int length;
    const int width;
    const vector2D orientacionLink;
    std::vector<pedestrian*> pedestriansLink;
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
    link(int idLink, node* node1, node* node2, int length, int width);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setPedestriansLink(std::vector<pedestrian*> pedestriansLink);
    void setPedestriansInSublink(std::vector<int> pedestriansInSublink);
    void setDensityInSublink(std::vector<double> densityInSublink);
    void setDensityLevel(int densityLevel);
    void setAnchoDivisiones(double anchoDivisiones);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getIdLink() const;
    const node* getNode1() const;
    const node* getNode2() const;
    const int getLength() const;
    const int getWidth() const;
    const vector2D getOrientacionLink() const;
    std::vector<pedestrian*>& getPedestriansLink();
    std::vector<int>& getPedestriansInSublink();
    std::vector<double>& getDensityInSublink();
    int* getDensityLevel();
    double getAnchoDivisiones();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    vector2D calcularOrientacionLink();
    void calcularAnchoDivisiones();
    void calcularDensity();
    void calcularDensityLevel();
    void mostrarLink() const;
    void mostrarSubLink() const;
    void imprimirLink(std::fstream& file) const;
};
#endif

