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

#include "subLink.h"
#include "dictionary.h"
#include "link.h"
#include "pedestrian.h"
#include <iomanip>
// #include "pedestrian.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
subLink::subLink(const link *calle)
    : calle(calle),
      densidadSublink(0)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void subLink::setPedestriansInSublink(std::vector<pedestrian*> pedestriansInSublink) {
    (*this).pedestriansInSublink = pedestriansInSublink;
}
void subLink::setDensidadSublink(double densidadSublink) {
    (*this).densidadSublink = densidadSublink;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<pedestrian*>& subLink::getPedestriansInSublink() {
    return pedestriansInSublink;
}
double subLink::getDensidadSublink() const {
    return densidadSublink;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void subLink::actualizarVelocidadPedestrianInSublink(double &velocidad) {
    for (pedestrian* persona: pedestriansInSublink) {
        persona->setVelocidadPedestrian(velocidad);
    }
}
double subLink::calcularDensidadSubdivision() const{
    /* calcula la densidad de la subdivision*/
    return pedestriansInSublink.size() / (calle->getAnchoSubdivisiones() * calle->getWidth()); 
}
void subLink::agregarPedestrian(pedestrian* const persona) {
//     /* agregar persona en el sublink*/
    pedestriansInSublink.push_back(persona);
}
void subLink::quitarPedestrian(pedestrian *const persona) {
    /* quitar persona en el sublink porque se cambia a otro sublink*/
    pedestriansInSublink.erase(std::remove(pedestriansInSublink.begin(), pedestriansInSublink.end(), persona), pedestriansInSublink.end());
}
double subLink::calcularCantidadPedestrians() const {
    return pedestriansInSublink.size();
}
void subLink::reiniciar() {
    pedestriansInSublink.clear();
    densidadSublink = 0;
}
void subLink::mostrarsubdivision() const {
    std::cout << std::setw(2) << pedestriansInSublink.size() << " ";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << densidadSublink;
    std::cout << "|";
}
