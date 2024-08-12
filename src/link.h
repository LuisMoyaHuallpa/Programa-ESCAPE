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
#include "pedestrian.h"


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
    // pedestriansLinkPtr|-->| PERSONAS EN LA CALLE
    // subdivisiones     |-->| SUBDIVISIONES DE LA CALLE
    // numberLinkDivision|-->| NUMERO DE DIVISIONES O SUBLINK DE UNA CALLE
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int idLink;
    const node* const node1Ptr;
    const node* const node2Ptr;
    const int length;
    const int width;
    const vector2D orientacionLink;
    const double anchoSubdivision;
    int densityLevel;
    std::vector<pedestrian*> pedestriansLinkPtr;
    std::vector<subLink> subdivisiones;
    
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static const int numberLinkDivision;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    link(const int idLink, const node* const node1Ptr, const node* const node2Ptr, const int length, const int width);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setDensityLevel(int densityLevel);
    void setPedestriansLink(std::vector<pedestrian*> pedestriansLink);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getIdLink() const;
    const node* const getNode1Ptr() const;
    const node* const getNode2Ptr() const;
    const int getLength() const;
    const int getWidth() const;
    const vector2D getOrientacionLink() const;
    const double getAnchoSubdivisiones() const;
    int getDensityLevel();
    
    std::vector<pedestrian*>& getPedestriansLinkPtr();
    std::vector<subLink>& getSublink();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const vector2D calcularOrientacionLink() const;
    const double calcularAnchoDivisiones() const;
    void calcularDensityGeneral();
    int calcularDensityLink(double densidadMaxima) const;
    void agregarPedestrian(pedestrian* const persona);
    void agregarPedestrianSublink(pedestrian* const persona, const int idSublink);
    void quitarPedestrian(pedestrian* const persona);
    void resetLink();
    void mostrarPedestriansLink() const;
    void mostrarSubdivisiones() const;
    void mostrarLink() const;
    void imprimirLink(std::fstream& file);
};
#endif
