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

int main() {
    // Creacion de data de interseccion.
    nodes dbNode1;
    // Creacion de data de calles.
    links dbLink1;
    // imprimi malla de calles.
    dbLink1.imprimirMeshLinks();
    // Lectura de simulaciones pasadas.
    // stateMatrixs dbStateMatrixs1;
    pedestrian::dbNodeTotal = std::move(nodes::dbNodeTotal);
    pedestrian::dbLinkTotal = links::dbLinkTotal;

    pedestrian::leerPedestrians("population.csv");
    // tiempo de inicio segun la distribucion rayleigh
    pedestrian::tiempoInicioDistribution();

    // creacionde del tiempo de simulacion.
    tiempo tiempoSimulado;

    while (tiempoSimulado.running()) {
        tiempoSimulado++;
        tiempoSimulado.mostrarTiempo();
        // modelamiento de pedestrian.
        pedestrian::modelamientoPedestrians(tiempoSimulado.getValorTiempo());
        // crea carpetas del tiempoSimulado.
        tiempoSimulado.crearCarpetaTiempo();
        // imprimir datos para postprocesamiento.
        pedestrian::imprimirPedestrians(tiempoSimulado.getValorTiempo());
    }
}

