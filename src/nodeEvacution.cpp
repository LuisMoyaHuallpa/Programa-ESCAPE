#include "nodeEvacution.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeEvacuation::personasEvacuadas=0;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodeEvacuation::nodeEvacuation(int id, int coordX, int coordY)
    : node(id, coordX, coordY) {
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeEvacuation::getPersonasEvacudas() {
    return personasEvacuadas;
}    
void nodeEvacuation::sumarPersonaEvacuda() {
    personasEvacuadas++;
}
void nodeEvacuation::imprimirNodeEvacuation(std::fstream& file) {
    file << getPersonasEvacudas();
    file << std::endl;
}

