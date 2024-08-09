#include "velocidad.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
velocidad::velocidad()
    :
    magnitud(1)
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
double velocidad::calcularVelocidadDensidad(const double &densidad) {
    return 1.388 - 0.396 * densidad; 
}
double velocidad::calcularAjusteVelocidad(double& velocidad) {
    const double vel_min = 0.2;
    const double vel_max = 1.19;
    return std::max(vel_min, std::min(velocidad, vel_max));
}
double velocidad::actualizarVelocidad(const double &densidad) {
    double vel = calcularVelocidadDensidad(densidad); 
    return calcularAjusteVelocidad(vel);
}
void velocidad::mostrarVelocidad() {
}
