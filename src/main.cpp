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
    stateMatrixs dbStateMatrixs1;
    pedestrian::dbNodeTotal = std::move(nodes::dbNodeTotal);
    pedestrian::dbLinkTotal = links::dbLinkTotal;

    pedestrian::leerPedestrians(dictionary::controDict["populationFile"]);
    // tiempo de inicio segun la distribucion rayleigh
    pedestrian::tiempoInicioDistribution();

    // creacionde del tiempo de simulacion.
    tiempo tiempoSimulado;

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

    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time);
    // Imprime la duración en milisegundos
    std::cout << "Tiempo de ejecución: " << duration.count() << " segundos" << std::endl;
}

