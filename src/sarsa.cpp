#include "sarsa.h"
#include "iostream"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const double sarsa::alpha = 0.05;
/* gamma es el discount un factor*/
const double sarsa::gamma = 0.9;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sarsa::sarsaActualizarQ(double* const QPrevious, const double* const QCurrent, const int& r) {
    *QPrevious += alpha * (static_cast<double>(r) + gamma * *QCurrent - *QPrevious); 
}

