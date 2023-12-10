#include "sarsa.h"

const double sarsa::alpha = 0.05;
const int sarsa::gamma = 9;

sarsa::sarsa() {
    setQCurrent(0);
    setQPrevious(0);
    setR(0);
}
sarsa::sarsa(double QCurrent, double QPrevious, double r){
    setQCurrent(QCurrent);
    setQPrevious(QPrevious);
    setR(r);
}

void sarsa::setQCurrent(double QCurrent) {
    (*this).QCurrent = QCurrent;
}
void sarsa::setQPrevious(double QPrevious) {
    (*this).QPrevious = QPrevious;
}
void sarsa::setR(int r) {
    (*this).r = r;
}
double sarsa::sarsaActualizarQ() {
    QPrevious += alpha * (r + gamma * QCurrent - QPrevious); 
    // std::cout << "durante2: ";
    // std::cout << QPrevious << std::endl;
    return QPrevious;
}
