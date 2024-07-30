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
#include "subLink.h"
#include "vector2D.h"
#include "vector"
#include "nodes.h"
#include "dictionary.h"

class pedestrian;
class link{
    
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idLink            |-->| ID DE LA CALLE
    // idNode1           |-->| INTERSECCION DE LA CALLE  
    // idNode2           |-->| LA OTRA INTERSECCION DE LA CALLE 
    // length            |-->| LARGO DE LA CALLE
    // width             |-->| ANCHO DE LA CALLE
    // orientacionLink   |-->| ANGULO QUE FORMA LA HORIZONTAL CON LA CALLE
    // anchoSubdivision  |-->| ANCHO DE UNA SUBDIVISION DE LA CALLE
    // densityLevel      |-->| NIVEL DE DENSIDAD DE LA CALLE
    // pedestriansLink   |-->| PERSONAS EN LA CALLE
    // subdivisiones     |-->| SUBDIVISIONES DE LA CALLE
    // numberLinkDivision|-->| NUMERO DE DIVISIONES O SUBLINK DE UNA CALLE
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int idLink;
    const node* node1;
    const node* node2;
    const int length;
    const int width;
    const vector2D orientacionLink;
    const double anchoSubdivision;
    int densityLevel;
    std::vector<pedestrian*> pedestriansLink;
    std::vector<subLink> subdivisiones;
    
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static const int numberLinkDivision;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    link(int idLink, node* node1, node* node2, int length, int width);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setDensityLevel(int densityLevel);
    void setPedestriansLink(std::vector<pedestrian*> pedestriansLink);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getIdLink() const;
    const node* getNode1() const;
    const node* getNode2() const;
    const int getLength() const;
    const int getWidth() const;
    const vector2D getOrientacionLink() const;
    const double getAnchoSubdivisiones() const;
    int& getDensityLevel();
    
    std::vector<pedestrian*>& getPedestriansLink();
    std::vector<subLink>& getSublink();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const vector2D calcularOrientacionLink() const;
    const double calcularAnchoDivisiones() const;
    void calcularDensity();
    void calcularDensityLevel();
    void mostrarPedestriansLink() const;
    void mostrarSubdivisiones() const;
    void mostrarLink();
    void imprimirLink(std::fstream& file);
};
#endif
