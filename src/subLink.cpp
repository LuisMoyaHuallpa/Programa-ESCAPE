#include "subLink.h"
#include "link.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int subLink::numberDivisiones = 10;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
subLink::subLink() {
    (*this).cantidadPedestrian = 0;
    (*this).densidad = 0;
    // calcularDensidad();
}
// subLink::subLink(link* parenLink) {
//     (*this).parentLink = parenLink; 
//     (*this).cantidadPedestrian = 0;
//     (*this).densidad = 0;
//     // calcularDensidad();
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
void subLink::setPedestriansInSubLink(std::vector<int> pedestriansInSubLink) {
    (*this).pedestriansInSubLink = pedestriansInSubLink;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
std::vector<int> subLink::getPedestriansInSubLink() {
    return pedestriansInSubLink;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void subLink::calcularCantidadPedestrian() {
//     cantidadPedestrian = pedestriansIdsInSubLink.size();
// }
// void subLink::calcularDensidad(int length, int width) {
//     calcularCantidadPedestrian();
//     if (cantidadPedestrian != 0) {
//         densidad = static_cast<double>(cantidadPedestrian) / (link::getUnitWidthPartion() * width);
//     }
//     else {
//         densidad = 0;
//     }
// }
// double subLink::calcularAnchoDivisiones(int idNode1, int idNode2) {
//     double ancho_x =   links::;
//     int ancho_y = link::getIdNode1() ;  
//     return 0;
// }
// void subLink::calcular() {
//  //     // int idContador;
//     double index_x = (position.getX() - linkActual->getNode1()->getCoordX()) / static_cast<double>(linkActual->getUnitWidthPartion());
//     double index_y = (position.getY() - linkActual->getNode1()->getCoordY()) / static_cast<double>(linkActual->getUnitWidthPartion());
//     int index_hipo = std::trunc(std::sqrt(std::pow(index_x,2) + pow(index_y, 2)));
 
// }
// bool subLink::verificarPedestrianId(int idPedestrian) {
//     for (int i = 0; i < pedestriansIdsInSubLink.size(); i++) {
//         if (pedestriansIdsInSubLink.at(i) == idPedestrian) {
//             return true;
//             break;
//         }
//     }
//     return false;
// }
// void subLink::agregarPedestrianId(int idPedestrian) {
//     pedestriansIdsInSubLink.push_back(idPedestrian);
// }
// void subLink::quitarPedestrianId(int idPedestrian) {
//     for (auto it = pedestriansIdsInSubLink.begin(); it != pedestriansIdsInSubLink.end(); ++it) {
//         if (*it == idPedestrian) {
//             pedestriansIdsInSubLink.erase(it);
//             break;
//         }
//     }
// }
// void subLink::mostrarSubLink() {
//     calcularCantidadPedestrian();
//     std::cout << cantidadPedestrian << " ";
//     // std::cout << densidad << " ";
// }
