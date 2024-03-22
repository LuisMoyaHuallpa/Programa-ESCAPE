#include "subLink.h"
#include "dictionary.h"
#include "link.h"
// #include "pedestrian.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int subLink::numberDivisiones = std::stoi(dictionary::get()->lookup("numberDivisiones"));

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
subLink::subLink() {
}
subLink::subLink(const link* calle)
    : calle(calle) {
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void subLink::setIdSublink(int idSublink) {
    (*this).idSublink = idSublink;
}
void subLink::setPedestriansInSublink(std::vector<pedestrian*> pedestriansInSublink) {
    (*this).pedestriansInSublink = pedestriansInSublink;
}
void subLink::setDensidadSublink(double densidadSublink) {
    (*this).densidadSublink = densidadSublink;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int subLink::getIdSublink() const {
    return idSublink;  
}
std::vector<pedestrian*>& subLink::getPedestriansInSublink() {
    return pedestriansInSublink;
}
double subLink::getDensidadSublink() const {
    return densidadSublink;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void subLink::calcularDensidadSubdivision() {
    /* calcula la densidad de la subdivision*/
    densidadSublink = pedestriansInSublink.size() / (calle->getAnchoSubdivisiones() * calle->getWidth()); 
}
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
void subLink::mostrarPedestriansInSublink() const {
    std::cout << pedestriansInSublink.size() << " ";
}
