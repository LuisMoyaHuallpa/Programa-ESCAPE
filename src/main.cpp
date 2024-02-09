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
#include "chrono"
#include "dictionary.h"

int main() {
    // tiempo de performace
    auto start_time = std::chrono::high_resolution_clock::now();
    // leer controlDict
    dictionary controDict("controlDict");
    // imprimi malla de calles.
    links::get()->imprimirMeshLinks();
    // Lectura de simulaciones pasadas.
    stateMatrixs dbStateMatrixs;
    // si la opcion de lectura de datos anteriores de stateMatrixs esta activa
    dbStateMatrixs.leerDbStateMatrixs(stateMatrixs::simulationFile + dictionary::controlDict["previousComputationFile"]);

    // segun el número de simulaciones
    while (tiempo::get()->getINumberSimulation() < tiempo::get()->getEndNumberSimulation()) {
        // aumentar el numero de simulacion
        tiempo::get()->aumentarINumberSimulation();
        // loop para una evacuacion
        while (tiempo::get()->running()) {
            tiempo::get()->aumentarTiempo();
            tiempo::get()->mostrarTiempo();
            // // modelamiento de pedestrian.
            pedestrians::get()->modelamientoPedestrians(tiempo::get()->getValorTiempo());
            // imprimir datos para postprocesamiento.
            pedestrians::get()->imprimirPedestrians();
            
            links::get()->mostrarSublink();
            
            links::get()->resetSublinks();
            // pedestrians::get()->reset();
        }
        // Imprimir estados al terminar la simulación
        dbStateMatrixs.imprimirDbStateMatrixs();
        // reiniciar el tiempo
        tiempo::get()->setValorTiempo(0);
    }

    // Imprime la duración en milisegundos
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;
}

