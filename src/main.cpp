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
#include "chrono"
#include "dictionary.h"

int main() {
    // tiempo de performace
    auto start_time = std::chrono::high_resolution_clock::now();
    // leer controlDict
    dictionary controDict("controlDict");
    // Creacion de data de interseccion.
    nodes dbNode1;
    // Creacion de data de calles.
    links dbLink1;
    // imprimi malla de calles.
    dbLink1.imprimirMeshLinks();
    // Lectura de simulaciones pasadas.
    stateMatrixs dbStateMatrixs;
    // si la opcion de lectura de datos anteriores de stateMatrixs esta activa
    if (dictionary::controlDict["computationContinued"] == "yes") {
        dbStateMatrixs.leerDbStateMatrixs(stateMatrixs::simulationFile + dictionary::controlDict["previousComputationFile"]);
        dbStateMatrixs.extracionINumeroSimulacion();
    }
    pedestrian::dbNodeTotal = std::move(nodes::dbNodeTotal);
    pedestrian::dbLinkTotal = links::dbLinkTotal;

    // creacion de data de personas
    pedestrian::leerPedestrians(dictionary::controlDict["populationsFile"]);
    // tiempo de inicio segun la distribucion rayleigh
    pedestrian::tiempoInicioDistribution();
    // segun el número de simulaciones
    for (int i = 1; i <= std::stoi(dictionary::controlDict["numberSimulation"]); i++) {
        // creacionde del tiempo de simulacion.
        tiempo tiempoSimulado;
        // cantidad de simulaciones
        while (tiempoSimulado.running()) {
            tiempoSimulado++;
            tiempoSimulado.mostrarTiempo();
            // modelamiento de pedestrian.
            pedestrian::modelamientoPedestrians(tiempoSimulado.getValorTiempo());
            if (tiempoSimulado.verificarGraphicPrintout()) {
                // crea carpetas del tiempoSimulado.
                tiempoSimulado.crearCarpetaTiempo();
                // imprimir datos para postprocesamiento.
                pedestrian::imprimirPedestrians(tiempoSimulado.getValorTiempo());
            }
        }
        // Imprimir estados al terminar la simulación
        dbStateMatrixs.imprimirDbStateMatrixs();
    }

    // Imprime la duración en milisegundos
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;
}

