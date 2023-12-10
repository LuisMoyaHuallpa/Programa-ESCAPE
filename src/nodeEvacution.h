#ifndef nodeEvacuation_h
#define nodeEvacuation_h

#include "node.h"

class nodeEvacuation: public node {
private:

public:
    static int personasEvacuadas;
    int static getPersonasEvacudas();
    void static sumarPersonaEvacuda();
    
    nodeEvacuation();
    nodeEvacuation(int id, int coordX, int coordY);

    

};

#endif
