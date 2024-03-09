#include "vector2DVelocidad.h"
#include <iostream>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double vector2DVelocidad::velocidadConstante = 1.0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector2DVelocidad::vector2DVelocidad() : vector2D() {
    magnitud = velocidadConstante;
}
// vector2DVelocidad::vector2DVelocidad(vector2D* orientacion, double densidad) : vector2D() {
//     // vector velocidad
//     calcularMagnitudVelocidad(densidad);
//     // setOrientacion(orientacion);
//     vector2D v = *orientacion * magnitud;
//     double x = v.getX();
//     double y = v.getY();
//     setX(x);
//     setY(y);
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void vector2DVelocidad::setDireccion(vector2D direccion) {
    (*this).direccion = direccion;
    calcularVectorVelocidad();
}

void vector2DVelocidad::setMagnitud(int magnitud){
    (*this).magnitud = magnitud;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector2D vector2DVelocidad::getDireccion() {
    return direccion; 
}
double vector2DVelocidad::getMagnitud() const{
    return magnitud;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void vector2DVelocidad::calcularMagnitudVelocidad(double densidad) {
    magnitud = 1.388 - 0.396 * densidad; 
}
void vector2DVelocidad::ajusteVelocidad() {
    const double vel_min = 0.2;
    const double vel_max = 1.19;
    magnitud = std::max(vel_min, std::min(magnitud, vel_max));
}
void vector2DVelocidad::calcularVectorVelocidad() {
    vector2D a = direccion * magnitud;
    double x = a.getX();
    double y = a.getY();
    setX(x);
    setY(y);
}
void vector2DVelocidad::actualizarVelocidad(double densidad) {
    calcularMagnitudVelocidad(densidad); 
    ajusteVelocidad();
    calcularVectorVelocidad();
}
void vector2DVelocidad::mostrarVelocidad() {
    std::cout << "u: " << getX() << " ";
    std::cout << "v: " << getY() << std::endl;
}
