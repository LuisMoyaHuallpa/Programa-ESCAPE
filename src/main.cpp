#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "tiempo.h"
#include <sys/stat.h> 
#include "nodes.h"
#include "links.h"
#include "stateMatrixs.h"
#include "pedestrians.h"


void createFolder(const std::string& folderName) {
    // Crear la carpeta
    if (mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
        std::cout << "Carpeta creada exitosamente." << std::endl;
    } else {
        // std::cerr << "Error al crear la carpeta." << std::endl;
    }
}

int main() {
    // Creacion de data de interseccion.
    nodes dbNode1;
    // Creacion de data de calles.
    links dbLink1;
    // Lectura de simulaciones pasadas.
    stateMatrixs dbStateMatrixs1;
    // Lectura de data de peatones.
    pedestrians dbPedestrian1;
    // dbPedestrian1.mostrarPedestrians();
    // creacionde del tiempo de simulacion.
    tiempo tiempoSimulado;

    while (tiempoSimulado.running()) {
        tiempoSimulado++;
        tiempoSimulado.mostrarTiempo();
        dbPedestrian1.caminarPedestrians(tiempoSimulado.getValorTiempo());
        // dbPedestrian1.caminarPedestrians(tiempoSimulado.getValorTiempo());
        dbPedestrian1.mostrarPedestrians();
    //     if (tiempoSimulado.getWriteNow()) {
    //         std::string folderName = std::to_string(tiempoSimulado.getValorTiempo());
    //         createFolder(folderName);
    //         dbPedestrian1.imprimirPedestrians(folderName);
    //         dbNode1.imprimirCantPedestrianEvacuted(folderName);
    //     }
    }
    // dbNode1.mostrarNodes();
     // dbNode1.imprimirNodes();
    // dbStateMatrixs1.imprimirDbStateMatrixs();
}

