#include "nodeEvacution.h"

int nodeEvacuation::personasEvacuadas=0;
int nodeEvacuation::getPersonasEvacudas() {
    return personasEvacuadas;
}    
void nodeEvacuation::sumarPersonaEvacuda() {
    personasEvacuadas++;
}
nodeEvacuation::nodeEvacuation(int id, int coordX, int coordY)
    : node(id, coordX, coordY) {
}


