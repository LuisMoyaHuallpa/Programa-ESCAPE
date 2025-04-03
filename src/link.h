// MIT License
// Copyright (c) 2025 
// Luis Angel Moya Huallpa, Julio Cesar Ramirez Paredes, Erick Mas, Shunichi Koshimura
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
    const int cantidadSubdivisiones;
    int densityLevel;
    std::vector<subLink> subdivisiones;
    
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
    const int getCantidadSubdivisiones() const;
    int getDensityLevel();
    std::vector<subLink>& getSubdiviones();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const vector2D calcularOrientacionLink() const;
    const double calcularAnchoSubdivision(const std::string &opcionSubdivision) const;
    const int calcularCantidadSubdivisiones(const std::string &opcionSubdivision);
    void calcularDensityGeneral();
    int calcularPedestriansLink() const;
    int calcularDensityLink() const;
    int calcularDensityLevelLink(const double densidadLink) const;
    void agregarPedestrianSublink(pedestrian* const persona, const int idSublink);
    void quitarPedestrianSublink(pedestrian* const persona, const int idSublink);
    subLink* calcularSublink(const vector2D &position) const;
    void reiniciarSubdivisiones();
    void mostrarSubdivisiones() const;
    void mostrarLink() const;
    void imprimirLink(std::fstream& file);
};
#endif
