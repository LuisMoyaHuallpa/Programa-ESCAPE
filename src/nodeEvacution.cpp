#include "nodeEvacution.h"
#include "tiempo.h"
#include "vector2D.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeEvacuation::personasEvacuadas=0;
std::string nodeEvacuation::getNodeType() {
    return "nodeEvacuation";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodeEvacuation::nodeEvacuation(int id, vector2D coordenada)
    : node(id, coordenada) {
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeEvacuation::getPersonasEvacuadas() {
    return personasEvacuadas;
}    
void nodeEvacuation::sumarPersonaEvacuada() {
    personasEvacuadas++;
}
void nodeEvacuation::imprimirNodeEvacuation(std::fstream& file) {
    file << getPersonasEvacuadas();
    file << std::endl;
}
void nodeEvacuation::imprimirTrasientNumberEvacuated(std::fstream& file) {
    file << tiempo::get()->getValorTiempo() << " ";
    file << getPersonasEvacuadas();
    file << std::endl;
}

