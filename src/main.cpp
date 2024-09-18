#include <cstdlib>
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>
#include "dictionary.h"
#include "pedestrian.h"
#include "tiempo.h"
#include "nodes.h"
#include "links.h"
#include "stateMatrixs.h"
#include "pedestrians.h"

int main() {
    // imprimi malla de calles.
    links::get()->imprimirMeshLinks();
    // Lectura de simulaciones pasadas.
    stateMatrixs::get()->leerDbStateMatrixs();
    // segun el número de simulaciones
    while (tiempo::get()->getINumberSimulation() <= tiempo::get()->getEndNumberSimulation()) {
        // calcula el valor el valor del randomChoiceRate
        tiempo::get()->calcularRandomChoiceRate();
        // loop para una evacuacion
        while (tiempo::get()->running()) {
            tiempo::get()->aumentarTiempo();
           // modelamiento de pedestrian.
            pedestrians::get()->modelamientoPedestrians();
            // contador de personas un tiempo atras de la funcion modelamiento
            links::get()->contarPedestrians();
            io::get()->imprimirOutput();
            // pone en 0 los elementos valores sublink            
            links::get()->resetSublinks();
        }
        // mostrar resultados simulation
        tiempo::get()->mostrarIResultadosSimulacion();
        // aumentar el numero de simulacion y reiniciar valores
        tiempo::get()->aumentarINumberSimulation();
    }
}
