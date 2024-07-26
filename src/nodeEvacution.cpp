#include "nodeEvacution.h"
#include "io.h"
#include "tiempo.h"
#include "vector2D.h"
#include "nodes.h"

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
void nodeEvacuation::imprimirNodeEvacuation(fileIO* file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        // impresion de id de nodos, solo en tiempo 1 al inicio
        if (tiempo::get()->getValorTiempo() == 1) {
            // id 1 2 3 4
            file->getFileFstream() << "id,";
            for (int i = 0; i < nodes::get()->getDbNodeEvacuation().size(); i++) {
                file->getFileFstream() << nodes::get()->getDbNodeEvacuation().at(i)->getIdNode();
                // imprime , hasta antes de la ultima
                if (i < nodes::get()->getDbNodeEvacuation().size() - 1) {
                    file->getFileFstream() << ",";
                }
            }
            // salto de linea
            file->getFileFstream() << std::endl;
        }
        // impresion de personas evacuadas por nodo de evacuacion
        // imprime el tiempo
        file->getFileFstream() << tiempo::get()->getValorTiempo() << ",";
        for (int i = 0; i < nodes::get()->getDbNodeEvacuation().size(); i++) {
            // imprime la cantidad de personas evacuadas por nodo
            file->getFileFstream() << nodes::get()->getDbNodeEvacuation().at(i)->getPersonasEvacuadas();
            // imprime , hasta antes de la ultima
            if (i < nodes::get()->getDbNodeEvacuation().size() - 1) {
                file->getFileFstream() << ",";
            }
        }
        // salto de linea
        file->getFileFstream() << std::endl;
    }
}
void nodeEvacuation::imprimirTotalPersonasEvacuadas(fileIO* file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        // impresion de tiempo y personas evacuadas
        file->getFileFstream() << tiempo::get()->getValorTiempo() << ",";
        file->getFileFstream() << totalPersonasEvacuadas;
        file->getFileFstream() << std::endl;
    }
}
void nodeEvacuation::imprimirVariableTotalPersonasEvacuadas(fileIO* file) {
    // impresion de tiempo y personas evacuadas
    file->getFileFstream() << totalPersonasEvacuadas;
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
const bool nodeEvacuation::getLleno() const{
    return lleno;
}
const int nodeEvacuation::getMaxPersonasEvacuadas() const{
    return maxPersonasEvacuadas;    
}
const int nodeEvacuation::getPersonasEvacuadas() const{
    return personasEvacuadas;    
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
void nodeEvacuation::imprimirPersonasEvacuadas(std::fstream* file) {
    *file << personasEvacuadas;
}
