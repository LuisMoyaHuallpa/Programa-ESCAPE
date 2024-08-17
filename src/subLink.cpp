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
