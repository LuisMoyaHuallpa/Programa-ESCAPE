#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tiempo.h"
#include "nodes.h"
#include "links.h"
#include "stateMatrixs.h"
#include "pedestrian.h"
#include "pedestrians.h"
#include "dictionary.h"
#include "chrono"

int main() {
    // leer controlDict
    // dictionary controDict("controlDict");
    // imprimi malla de calles.

    
    links::get()->imprimirMeshLinks();

    auto start = std::chrono::high_resolution_clock::now();
    // Lectura de simulaciones pasadas.
    // stateMatrixs dbStateMatrixs;
    // si la opcion de lectura de datos anteriores de stateMatrixs esta activa
    stateMatrixs::get()->leerDbStateMatrixs();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << duration.count() << std::endl;
    std::cout << "Duración lectura: " << duration.count() << " s" << std::endl;

    // nodes::get()->mostrarNodes();
    // segun el número de simulaciones
    while (tiempo::get()->getINumberSimulation() <= tiempo::get()->getEndNumberSimulation()) {
        // loop para una evacuacion
        // calcula el valor el valor del randomChoiceRate
        tiempo::get()->calcularRandomChoiceRate();
        while (tiempo::get()->running()) {
            tiempo::get()->aumentarTiempo();
            // tiempo::get()->mostrarTiempo();
            // contador de personas un tiempo atras de la funcion modelamiento de caminar de personas
            pedestrians::get()->contarPedestriansInSublink();
            links::get()->calcularDensityLevelLinks();
            // // modelamiento de pedestrian.
            pedestrians::get()->modelamientoPedestrians();
            // imprimir datos para postprocesamiento.
            pedestrians::get()->imprimirPedestrians();
            
            // links::get()->mostrarSublink();
            
            links::get()->resetSublinks();
            // pedestrians::get()->reset();
        }
        // Imprimir estados al terminar la simulación
        stateMatrixs::get()->imprimirDbStateMatrixs();
        // mostrar resultados simulation
        tiempo::get()->mostrarIResultadosSimulacion();
        // aumentar el numero de simulacion y reinciar
        tiempo::get()->aumentarINumberSimulation();

    }
}

