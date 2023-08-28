#include "subLink.h"
#include "link.h"
#include "vector2D.h"
#include <iostream>
#include <vector>

subLink::subLink() {
    (*this).cantidadPedestrian = 0;
    (*this).densidad = 0;
    calcularDensidad();
}
subLink::subLink(link* parenLink) {
    (*this).parentLink = parenLink; 
    (*this).cantidadPedestrian = 0;
    (*this).densidad = 0;
    // calcularDensidad();
}


void subLink::setIdSubLink(int idSubLink) {
    (*this).idSubLink = idSubLink;
}
void subLink::setPuntoFinal(vector2D puntoFinal) {
    (*this).puntoFinal = puntoFinal; 
}
void subLink::setCantidadPedestrian(int cantidadPedestrian) {
    (*this).cantidadPedestrian = cantidadPedestrian;
}
void subLink::setDensidad(double densidad) {
    (*this).densidad = densidad;
}
void subLink::setPedestriansIdsInSubLink(
    std::vector<int> pedestrianIdsInSubLink) {
    (*this).pedestriansIdsInSubLink = pedestrianIdsInSubLink;
}

int subLink::getIdSubLink() {
    return idSubLink;  
}
vector2D subLink::getPuntoFinal() {
    return puntoFinal;
}
int subLink::getCantidadPedestrian() {
    return cantidadPedestrian;
}
double subLink::getDensidad() {
    return densidad;
}
std::vector<int> subLink::getPedestrianIdsInSubLink() {
    return pedestriansIdsInSubLink;
}

void subLink::calcularCantidadPedestrian() {
    cantidadPedestrian = pedestriansIdsInSubLink.size();
}
void subLink::calcularDensidad() {
    calcularCantidadPedestrian();
    densidad = static_cast<double>(cantidadPedestrian) / (parentLink->getLength()*parentLink->getWidth());
}
bool subLink::verificarPedestrianId(int idPedestrian) {
    for (int i = 0; i < pedestriansIdsInSubLink.size(); i++) {
        if (pedestriansIdsInSubLink.at(i) == idPedestrian) {
            return true;
            break;
        }
    }
    return false;
}
void subLink::agregarPedestrianId(int idPedestrian) {
    pedestriansIdsInSubLink.push_back(idPedestrian);
}
void subLink::quitarPedestrianId(int idPedestrian) {
    for (auto it = pedestriansIdsInSubLink.begin(); it != pedestriansIdsInSubLink.end(); ++it) {
        if (*it == idPedestrian) {
            pedestriansIdsInSubLink.erase(it);
            break;
        }
    }
}
void subLink::mostrarSubLink() {
    calcularCantidadPedestrian();
    std::cout << cantidadPedestrian << " ";
}
