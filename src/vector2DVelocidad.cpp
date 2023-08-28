
#include "vector2DVelocidad.h"
#include "link.h"
#include "pedestrian.h"
#include "vector2D.h"
#include <iostream>


double vector2DVelocidad::velocidadConstante = 1.388;

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

void vector2DVelocidad::setOrientacion(vector2D orientacion) {
    (*this).orientacion = orientacion;
}

void vector2DVelocidad::setMagnitud(int magnitud){
    (*this).magnitud = magnitud;
}

vector2D vector2DVelocidad::getOrientacion() {
    return orientacion; 
}
double vector2DVelocidad::getMagnitud(){
    return magnitud;
}

void vector2DVelocidad::calcularMagnitudVelocidad(double densidad) {
    magnitud = 1.388 - 0.396 * densidad; 
}
void vector2DVelocidad::ajusteVelocidad() {
    const double vel_min = 0.2;
    const double vel_max = 1.19;
    magnitud = std::max(vel_min, std::min(magnitud, vel_max));
}
void vector2DVelocidad::calcularVectorVelocidad() {
    std::cout << "cal: ";
    std::cout << orientacion.getX() << " ";
    std::cout << orientacion.getY() << " ";
    std::cout << std::endl;
    vector2D a = orientacion * magnitud;
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
