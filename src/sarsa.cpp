#include "sarsa.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const double sarsa::alpha = 0.05;
/* gamma es el discount un factor*/
const double sarsa::gamma = 0.9;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sarsa::sarsa() : QCurrent(nullptr), QPrevious(nullptr), r(nullptr){
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void sarsa::setQCurrent(double* QCurrent) {
    (*this).QCurrent = QCurrent;
}
void sarsa::setQPrevious(double* QPrevious) {
    (*this).QPrevious = QPrevious;
}
void sarsa::setR(int* r) {
    (*this).r = r;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double* &sarsa::getQCurrent() {
    return QCurrent;
}
double* &sarsa::getQPrevious() {
    return QPrevious;
}
int* sarsa::getR() {
    return r;  
}

void sarsa::sarsaActualizarQ() {
    *QPrevious += alpha * (*r + gamma * *QCurrent - *QPrevious); 
}
