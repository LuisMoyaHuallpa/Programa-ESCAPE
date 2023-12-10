#ifndef sarsa_h
#define sarsa_h
#include "action.h"
#include "stateActionQ.h"
class sarsa{

private:
    double QCurrent;
    double QPrevious;
    int r;
    
public: 
    static const double alpha;
    // gamma <- discount
    static const int gamma;

    sarsa();
    sarsa(double QCurrent, double QPrevious, double r);

    void setQCurrent(double QCurrent);
    void setQPrevious(double QPrevious);
    void setR(int r);

    double sarsaActualizarQ();
    
};

#endif 
