#ifndef stateActionQ_h
#define stateActionQ_h
// Cambiar de nombre qStateAction
#include "state.h"
#include "action.h"
#include <fstream>
#include <iostream>

class stateActionQ {

private:
    state s;
    action a;
    double Q;
public: 

    static bool compararId(stateActionQ& a, stateActionQ& b);
    stateActionQ();
    stateActionQ(state s, action a);
    stateActionQ(state s, action a, double Q);

    void setS(state s);
    void setA(action a);
    void setQ(double Q);

    state getS();
    action getA();
    double getQ();

    bool operator==(stateActionQ qObject);
    void mostrarQ();
    void imprimirQ(std::fstream& file);
    void imprimirState(std::fstream& file);
};

#endif
