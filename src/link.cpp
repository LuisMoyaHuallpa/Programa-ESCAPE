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

#include "link.h"
#include "pedestrian.h"
#include "subLink.h"
#include "tiempo.h"
#include "vector2D.h"
#include "velocidad.h"
#include <iomanip>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
link::link(const int idLink, const node* const node1, const node* const node2, const int length, const int width)
    : idLink(idLink), node1Ptr(node1), node2Ptr(node2), length(length), width(width),
      orientacionLink(calcularOrientacionLink()),
      anchoSubdivision(calcularAnchoSubdivision(std::get<std::string>(dictionary::get()->lookupDefault("opcionSubdivision")))),
      cantidadSubdivisiones(calcularCantidadSubdivisiones(std::get<std::string>(dictionary::get()->lookupDefault("opcionSubdivision")))),
      subdivisiones(cantidadSubdivisiones, subLink(this)),
      densityLevel(0)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void link::setDensityLevel(int densityLevel) {
    (*this).densityLevel = densityLevel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int link::getIdLink() const {
    return idLink;  
}
const node* const link::getNode1Ptr() const {
    return node1Ptr;
}
const node* const link::getNode2Ptr() const {
    return node2Ptr;
}
const int link::getLength() const{
    return length;
}
const int link::getWidth() const{
    return width;
}
const vector2D link::getOrientacionLink() const {
    return orientacionLink;
}
int link::getDensityLevel() {
    return densityLevel;
}
std::vector<subLink>& link::getSubdiviones() {
    return subdivisiones;  
}
const double link::getAnchoSubdivisiones() const {
    return anchoSubdivision;
}
const int link::getCantidadSubdivisiones() const {
    return cantidadSubdivisiones;    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const vector2D link::calcularOrientacionLink() const{
    /* deberia esta calcular orientacion pero necesita acceder a dbLink
        por ello se calculara la direccione en pedestrian*/
    /* calcula la direccion de la calle con los nodos inicial y final*/
    const double x = node2Ptr->getCoordenada().getX() - node1Ptr->getCoordenada().getX();
    const double y = node2Ptr->getCoordenada().getY() - node1Ptr->getCoordenada().getY();
    // Calcula la magnitud del vector de dirección
    const double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    // Normaliza el vector de dirección (divide cada e por la magnitud)
    return {std::abs(x / magnitud), std::abs(y / magnitud)};
}
const double link::calcularAnchoSubdivision(const std::string &opcionSubdivision) const{
    // la opcionSubdivision es cantidadSubvisiones,
    // es decir le voy a dar la cantidad de subdiviones que debo tener
    // en un link por tanto calculo el ancho
    if (opcionSubdivision == "cantidadSubdivisiones") {
        /* Calcula el ancho de divisiones de la calle segun el numero de divisiones preestablecidas*/
        const vector2D nodo1Coordenada = node1Ptr->getCoordenada();
        const vector2D nodo2Coordenada = node2Ptr->getCoordenada();
        const double ancho_x = nodo1Coordenada.getX() - nodo2Coordenada.getX();
        const double ancho_y = nodo1Coordenada.getY() - nodo2Coordenada.getY();
        const double ancho = std::sqrt(ancho_x * ancho_x + ancho_y * ancho_y) / static_cast<double>(std::get<int>(dictionary::get()->lookupDefault("cantidadSubdivisiones")));
        return ancho;
    }
    // se el ancho, el default es 2 metros
    else {
        // calcula la cantidad de subdivisiones segun el ancho dado, luego calcula el ancho de nuevo
        const int cantSec = std::round(length / std::get<double>(dictionary::get()->lookupDefault("anchoSubdivision")));
        return length / static_cast<double>(cantSec);
    }
}
const int link::calcularCantidadSubdivisiones(const std::string &opcionSubdivision) {
    // si la opcionSubdivision es cantidadSubvisiones, es decir le voy a dar la cantidad de subdiviones que debe haber
    // en un link no es necesario hacer calculo porque ya se cantidad de subdivision
    if (opcionSubdivision == "cantidadSubdivisiones") {
        return std::get<int>(dictionary::get()->lookupDefault("cantidadSubdivisiones"));
    }
    // se el ancho de subdivision, debo calcular la cantidad de subdiviones.
    else {
        // la cantidad de secciones es un promedio de el largo entre ancho de subseccion
        return std::round(length / anchoSubdivision);
    }
}
void link::calcularDensityGeneral() {
    /* calculo de la densidad en cada sublink de la calle*/
    // subdivion es it
    double densidadMaxima = 0;
    for (auto it = subdivisiones.begin(); it != subdivisiones.end(); ++it) {
        // calcula la densidad segun la cantidad de personas
        double densidadSublink = it->calcularDensidadSubdivision();
        // guardar densidadMaxima
        if (densidadSublink > densidadMaxima) {
            densidadMaxima = densidadSublink;
        }
        // verifica si aun un cambio en la densidad de sublink
        if (it->getDensidadSublink() != densidadSublink) {
            double velocidadEnSublink = velocidad::actualizarVelocidad(densidadSublink);
            // verifica si aun un cambio en la velocidad de las personas dentro del sublink
            if (!(it->getPedestriansInSublink().empty())) {
                if (it->getPedestriansInSublink().at(0)->getVelocidadPedestrian().getMagnitud() != velocidadEnSublink) {
                    it->actualizarVelocidadPedestrianInSublink(velocidadEnSublink);
                }
            }
        }
        // guarda las densidades para el proximo calculo
        it->setDensidadSublink(densidadSublink);
    }
    densityLevel = calcularDensityLevelLink(densidadMaxima);
}
int link::calcularDensityLink() const{
    /* calcula la densidad de la calle segun la cantidad de personas dentra*/
    return calcularPedestriansLink() / (anchoSubdivision * width);
}
int link::calcularDensityLevelLink(const double densidadLink) const {
    /* calcula el nivel de densidad segun la densidad de la calle*/
    // elecion del nivel de densidad segun rangos preestablecidos
    if(densidadLink <= 0.5){
        return 0;
    }  
    else if (densidadLink <= 3.0) {
        return 1;
    }
    else {
        return 2;
    }
}
void link::agregarPedestrianSublink(pedestrian* const persona, const int idSublink) {
    subdivisiones.at(idSublink).agregarPedestrian(persona);
}
void link::quitarPedestrianSublink(pedestrian* const persona, const int idSublink) {
    subdivisiones.at(idSublink).agregarPedestrian(persona);
}
// subLink* link::calcularSublink(const vector2D &position) const {
//      /* Calcula la ubicacion de la persona en el array del subLink*/
//     // distancia de la persona al nodeInicio de la persona
//     // double index_x = position.getX() - nodeInicioPtr->getCoordenada().getX();
//     const double index_x = position.getX() - node1Ptr->getCoordenada().getX();
//     // double index_y = position.getY() - nodeInicioPtr->getCoordenada().getY();
//     const double index_y = position.getY() - node1Ptr->getCoordenada().getY();
//     int index_hipo = std::sqrt(std::pow(index_x,2) + pow(index_y, 2)) / anchoSubdivision;
//     if (index_hipo>= 10) {
//         index_hipo=9;    
//     }
//     return &subdivisiones.at(index_hipo);
   
// }
int link::calcularPedestriansLink() const {
    int personasEnCalle = 0 ;
    for (auto& subdivion : subdivisiones) {
        personasEnCalle += subdivion.calcularCantidadPedestrians();
    }
  return personasEnCalle; 
}
void link::reiniciarSubdivisiones() {
    // reiniciar el vector de subdiviones
    for (auto& sublink : subdivisiones) {
        // Llamamos al método reiniciar() de cada subLink
        sublink.reiniciar();
    }
}
// void link::mostrarPedestriansLink() const {
//     std::cout << "pedestrianLink: ";
//     for (int i = 0; i < pedestriansLinkPtr.size(); i++) {
//         std::cout << pedestriansLinkPtr.at(i)->getIdPedestrian() << " ";
//     }
// }
void link::mostrarSubdivisiones() const {
    std::cout << "l: ";
    std::cout << std::setw(2) << idLink << " ";
    for (int i = 0; i < subdivisiones.size(); i++) {
        subdivisiones.at(i).mostrarsubdivision();
    }
    std::cout << "dl: " << densityLevel;
    std::cout << "p: " << calcularPedestriansLink();
    // std::cout << "p: " << pedestriansLinkPtr.size() << std::endl;
}
void link::mostrarLink() const {
    std::cout << "link: ";
    std::cout << idLink << " ";
    std::cout << "nodes: ";
    std::cout << node1Ptr->getIdNode() << " ";
    std::cout << node2Ptr->getIdNode() << " ";
    // mostrarPedestriansLink();
    mostrarSubdivisiones();
    std::cout << std::endl;
}
void link::imprimirLink(std::fstream& file) {
    file << std::fixed << std::setprecision(2);
    file << node1Ptr->getCoordenada().getX() << " ";
    file << node1Ptr->getCoordenada().getY() << " ";
    file << node2Ptr->getCoordenada().getX() << " ";
    file << node2Ptr->getCoordenada().getY() << " ";
    file << std::endl;
}
