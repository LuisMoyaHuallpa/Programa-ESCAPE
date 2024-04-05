#include "sarsa.h"
#include "iostream"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const double sarsa::alpha = 0.05;
/* gamma es el discount un factor*/
const double sarsa::gamma = 0.9;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
sarsa::sarsa() : QPrevious(nullptr), QCurrent(nullptr), r(nullptr) {
}
// sarsa::sarsa(double QCurrent, double QPrevious, double r){
//     setQCurrent(QCurrent);
//     setQPrevious(QPrevious);
//     setR(r);
// }

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
double* sarsa::getQCurrent() {
    return QCurrent;
}
double* sarsa::getQPrevious() {
    return QPrevious;
}
int* sarsa::getR() {
    return r;  
}

void sarsa::sarsaActualizarQ() {
    *QPrevious += alpha * (*r + gamma * *QCurrent - *QPrevious); 
}
