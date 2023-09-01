#ifndef vector2DVelocidad_h
#define vector2DVelocidad_h

#include "vector2D.h"
#include <iostream>

class vector2DVelocidad : public vector2D {

private:
    vector2D orientacion;
    double magnitud;


public:
    static double velocidadConstante;

    vector2DVelocidad();
    // vector2DVelocidad(vector2D* orientacion, double densidad);
    
    void setOrientacion(vector2D orientacion);
    void setMagnitud(int magnitud);

    vector2D getOrientacion();
    double getMagnitud();

    void calcularMagnitudVelocidad(double densidad);
    void ajusteVelocidad();
    void calcularVectorVelocidad();
    void actualizarVelocidad(double densidad);
};
#endif
