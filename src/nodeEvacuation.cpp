#include "nodeEvacuation.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// extra 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "nodes.h"
#include "pedestrians.h"
#include "subLink.h"
#include "pedestrian.h"
#include "tiempo.h"
#include <iostream>
#include <vector>

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
estado nodeEvacuation::estadoPedestrianEnNodo() const {
    /* devuelve el estado de la persona segun el tipo de nodo donde se encuentra */
    return evacuado;
}
bool nodeEvacuation::verificarNodoEvacuation() const {
    /* verifica si el nodo es un node de evacuacion */
    return true;
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
void nodeEvacuation::plotearTotalPersonasEvacuadasXSimulacion() {
    class totalPersonasEvacuadasXSimulacion{
    public:
        std::vector<int> tiempo;
        std::vector<int> totalEvacuados;
    }; 
    // elementos de simulaciones a imprimir
    const std::vector<int> tiempoSimulacion = {1, 2, 3};
    static std::vector<totalPersonasEvacuadasXSimulacion> data(tiempoSimulacion.size());
    auto it = std::find(tiempoSimulacion.begin(), tiempoSimulacion.end(), tiempo::get()->getINumberSimulation());
    // solo entra en el numero de simulacion que pide tiempoSimulacion
    if (it != tiempoSimulacion.end()) {
        // Determinar el índice en el vector `data` basado en la posición en `tiempoSimulacion`
        int index = std::distance(tiempoSimulacion.begin(), it);
        // Agregar el valor del tiempo actual al vector `tiempo` correspondiente
        data.at(index).tiempo.push_back(tiempo::get()->getValorTiempo());
        data.at(index).totalEvacuados.push_back(totalPersonasEvacuadas);
    }
    if (tiempo::get()->getINumberSimulation() ==  tiempo::get()->getEndNumberSimulation() and tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime()) {
        FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
        if (gnuplotPipe) {
            // Configurar Gnuplot
            fprintf(gnuplotPipe, "set terminal png size 800,600\n");
            fprintf(gnuplotPipe, "set output 'personas_evacuadas.png'\n");
            fprintf(gnuplotPipe, "set xlabel 'Tiempo (s)'\n");
            fprintf(gnuplotPipe, "set ylabel 'Total de personas evacuadas'\n");
            fprintf(gnuplotPipe, "set title 'Personas Evacuadas en el Tiempo'\n");
            fprintf(gnuplotPipe, "set grid\n");
            // Posicionar los títulos a la izquierda
            fprintf(gnuplotPipe, "set key left\n");
            // cracion de plot
            fprintf(gnuplotPipe, "plot ");
            // creando titulo de linea
            for (size_t i = 0; i < data.size(); ++i) {
                fprintf(gnuplotPipe, "'-' using 1:2 with lines title 'Simulacion %d'", tiempoSimulacion.at(i));
                if (i < data.size() - 1) {
                    fprintf(gnuplotPipe, ", ");
                }
            }
            fprintf(gnuplotPipe, "\n");
            // ploteando lineas 
            for (size_t i = 0; i < data.size(); ++i) {
                 for (size_t j = 0; j < data.at(i).tiempo.size(); ++j) {
                    fprintf(gnuplotPipe, "%d %d\n", data.at(i).tiempo.at(j), data.at(i).totalEvacuados.at(j));
                 }
                 fprintf(gnuplotPipe, "e\n");
            }
            fflush(gnuplotPipe);
            pclose(gnuplotPipe);
        }
    }
}
void nodeEvacuation::imprimirVariableTotalPersonasEvacuadas(fileIO* const file) {
    // impresion de tiempo y personas evacuadas
    file->getFileFstream() << totalPersonasEvacuadas;
}
