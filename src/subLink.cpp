#include "subLink.h"
#include "dictionary.h"
#include "link.h"
// #include "pedestrian.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
subLink::subLink() : calle(nullptr){
}
subLink::subLink(const link*  calle)
    : calle(calle) {
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
void subLink::calcularDensidadSubdivision() {
    /* calcula la densidad de la subdivision*/
    densidadSublink = pedestriansInSublink.size() / (calle->getAnchoSubdivisiones() * calle->getWidth()); 
}
void subLink::agregarPedestrian(pedestrian* const persona) {
    /* agregar persona en el sublink*/
    pedestriansInSublink.push_back(persona);
}
void subLink::quitarPedestrian(pedestrian *const persona) {
    /* quitar persona en el sublink porque se cambia a otro sublink*/
    pedestriansInSublink.erase(std::remove(pedestriansInSublink.begin(), pedestriansInSublink.end(), persona), pedestriansInSublink.end());
}
void subLink::mostrarPedestriansInSublink() const {
    std::cout << pedestriansInSublink.size() << " ";
}
