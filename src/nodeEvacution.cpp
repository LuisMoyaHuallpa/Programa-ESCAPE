#include "nodeEvacution.h"
#include "tiempo.h"
#include "vector2D.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeEvacuation::totalPersonasEvacuadas=0;
int nodeEvacuation::maxPersonasEvacuadasGlobal=1000;

std::string nodeEvacuation::getNodeType() {
    return "nodeEvacuation";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodeEvacuation::nodeEvacuation(int id, vector2D coordenada)
    : node(id, coordenada) {
    personasEvacuadas = 0;
    maxPersonasEvacuadas = -1;
    lleno = false;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeEvacuation::getTotalPersonasEvacuadas() {
    return totalPersonasEvacuadas;
}    
void nodeEvacuation::sumarTotalPersonasEvacuadas() {
    totalPersonasEvacuadas++;
}
void nodeEvacuation::imprimirNodeEvacuation(std::fstream& file) {
    file << totalPersonasEvacuadas;
    file << std::endl;
}
void nodeEvacuation::imprimirTotalPersonasEvacuadas(std::fstream& file) {
    file << tiempo::get()->getValorTiempo() << ",";
    file << totalPersonasEvacuadas;
    file << std::endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void nodeEvacuation::setMaxPersonasEvacuadas(int maxPersonasEvacuadas) {
    (*this).maxPersonasEvacuadas = maxPersonasEvacuadas;
}
 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool nodeEvacuation::getLleno() {
    return lleno;
}
int nodeEvacuation::getMaxPersonasEvacuadas() {
    return maxPersonasEvacuadas;    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void nodeEvacuation::sumarPersonasEvacuadas() {
    personasEvacuadas++;
    verificarLLeno();
}
void nodeEvacuation::reiniciar() {
    personasEvacuadas =0;
    lleno = false;
}
void nodeEvacuation::verificarLLeno() {
    if (personasEvacuadas==maxPersonasEvacuadas) {
        lleno = true;
    }
}
void nodeEvacuation::imprimirPersonasEvacuadas(std::fstream& file) {
    file << personasEvacuadas;
}
