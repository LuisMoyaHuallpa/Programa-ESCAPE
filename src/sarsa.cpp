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
    std::cout << "actualiza" << std::endl;
    std::cout << "r:" << *r << std::endl;
    std::cout << "qp:" << *QPrevious << std::endl;
    std::cout << "qc:" << *QCurrent << std::endl;
    double q1 = alpha * (*r + gamma * *QCurrent - *QPrevious); 
    *QPrevious = q1 + *QPrevious;
    *QPrevious += alpha * (*r + gamma * *QCurrent - *QPrevious); 
    std::cout << "q1:" << q1 << std::endl;
    std::cout << "qp:" << *QPrevious << std::endl;
}
