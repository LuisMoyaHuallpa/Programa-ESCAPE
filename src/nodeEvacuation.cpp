#include "nodeEvacuation.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// extra 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "nodes.h"
#include "pedestrians.h"
#include "subLink.h"
#include "pedestrian.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeEvacuation::totalPersonasEvacuadas=0;
int nodeEvacuation::maxPersonasEvacuadasGlobal=1000;
bool nodeEvacuation::evacuacionTotal=false;

std::string nodeEvacuation::getNodeType() {
    return "nodeEvacuation";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodeEvacuation::nodeEvacuation(const int id, const vector2D coordenada)
    : node(id, coordenada),
      maxPersonasEvacuadas(-1),
      lleno(false)
{
}
nodeEvacuation::nodeEvacuation(const int id, const vector2D coordenada, const int maxPersonasEvacuadas)
    : node(id, coordenada),
      maxPersonasEvacuadas(maxPersonasEvacuadas),
      lleno(false)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int nodeEvacuation::getMaxPersonasEvacuadas() const{
    return maxPersonasEvacuadas;    
}
std::vector<pedestrian*> nodeEvacuation::getPersonasEvacuadasPtr() const{
    return personasEvacuadasPtr;    
}
bool nodeEvacuation::getLleno() const{
    return lleno;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool nodeEvacuation::verificarEvacuacionTotal() {
    /* verifica si todas las personas fueron evacuadas */
    const int totalPersonas = pedestrians::get()->getDbPedestrianTotal().size();
    return totalPersonasEvacuadas == totalPersonas;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void nodeEvacuation::reiniciar() {
    personasEvacuadasPtr.clear();
    lleno = false;
}
bool nodeEvacuation::verificarLLeno() const {
    /* verifica si el nodo de evacuacion esta lleno*/
    // compara el tamaño de la lista de personas evacuadas con la cantidad
    // maxima de personas evacuadas en el nodo de evacuacion
    return personasEvacuadasPtr.size() == maxPersonasEvacuadas;

}
estado nodeEvacuation::verificarNodoEvacuation() const {
    /* verifica si el nodo es un node de evacuacion */
    return evacuado;
}
std::vector<int> nodeEvacuation::stateObservado() const {
    return {0};
}
void nodeEvacuation::contabilizarPersona(pedestrian* const persona) {
    personasEvacuadasPtr.push_back(persona);
    totalPersonasEvacuadas++;
}
void nodeEvacuation::imprimirPersonasEvacuadas(std::fstream* file) {
    *file << personasEvacuadasPtr.size();
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
void nodeEvacuation::imprimirNodeEvacuation(fileIO* const file) {
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
            file->getFileFstream() << nodes::get()->getDbNodeEvacuation().at(i)->getPersonasEvacuadasPtr().size();
            // imprime , hasta antes de la ultima
            if (i < nodes::get()->getDbNodeEvacuation().size() - 1) {
                file->getFileFstream() << ",";
            }
        }
        // salto de linea
        file->getFileFstream() << std::endl;
    }
}
void nodeEvacuation::imprimirTotalPersonasEvacuadas(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        // impresion de tiempo y personas evacuadas
        file->getFileFstream() << tiempo::get()->getValorTiempo() << ",";
        file->getFileFstream() << totalPersonasEvacuadas;
        file->getFileFstream() << std::endl;
    }
}
void nodeEvacuation::imprimirVariableTotalPersonasEvacuadas(fileIO* const file) {
    // impresion de tiempo y personas evacuadas
    file->getFileFstream() << totalPersonasEvacuadas;
}
