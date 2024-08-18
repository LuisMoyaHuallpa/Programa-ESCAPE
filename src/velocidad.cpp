#include "velocidad.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
velocidad::velocidad()
    :
    magnitud(1.19)
{
}    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void velocidad::setMagnitud(double magnitud){
    (*this).magnitud = magnitud;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double velocidad::getMagnitud() const{
    return magnitud;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void velocidad::calcularAjusteRandom() {
    magnitud = magnitud + (0.02 * (static_cast<double>(std::rand()) / RAND_MAX)) - 0.01;
}
double velocidad::calcularVelocidadDensidad(const double &densidad) {
    return 1.388 - 0.396 * densidad; 
}
double velocidad::calcularAjusteLimites(double& velocidad) {
    const double vel_min = 0.2;
    const double vel_max = 1.19;
    return std::max(vel_min, std::min(velocidad, vel_max));
}
double velocidad::actualizarVelocidad(const double &densidad) {
    double vel = calcularVelocidadDensidad(densidad); 
    return calcularAjusteLimites(vel);
}
void velocidad::mostrarVelocidad() {
}
