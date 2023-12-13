#include "stateActionQ.h"
#include "state.h"
#include <fstream>

bool stateActionQ::compararId(stateActionQ& a, stateActionQ& b) {
    return a.getA().getIdLink() < b.getA().getIdLink();
}

stateActionQ::stateActionQ() : a(), s() {
    setQ(0.5); 
}
stateActionQ::stateActionQ(state s, action a) {
    setS(s); 
    setA(a);
    setQ(0.5); 
}
stateActionQ::stateActionQ(state s, action a, double Q) {
    setS(s); 
    setA(a);
    setQ(Q); 
}

void stateActionQ::setS(state s) {
    (*this).s = s; 
}
void stateActionQ::setA(action a) {
    (*this).a = a;
}
void stateActionQ::setQ(double Q) {
    (*this).Q = Q;
    // std::cout << "set: "<<this->getQ() << std::endl;
}

state stateActionQ::getS() {
    return s;
}
action stateActionQ::getA() {
    return a;
}
double stateActionQ::getQ() {
    return Q;
}

bool stateActionQ::operator==(stateActionQ qObject) {
    if (getA() == qObject.getA() and getS() == qObject.getS()) {
        return true;
    }
    return false;
}
void stateActionQ::mostrarQ() {
    a.mostrarAction();
    std::cout << a.getILinkConnection()<< " ";
    s.mostrarState();
    std::cout << Q;
}
void stateActionQ::imprimirQ(std::fstream& file) {
    file << getQ();
}
void stateActionQ::imprimirState(std::fstream& file) {
    s.imprimirState(file);
}

