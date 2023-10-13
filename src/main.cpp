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
    nodes dbNode1;
    links dbLink1(&dbNode1);
    // dbLink1.imprimirLinks();
    // dbLink1.mostrarLinks();
    // dbNode1.imprimirNodes();
    pedestrians dbPedestrian1(&dbNode1);
    dbPedestrian1.mostrarPedestrians();
    tiempo tiempoSimulado;

    while (tiempoSimulado.running())
    {
        tiempoSimulado++;
        int tiempo = tiempoSimulado.getValorTiempo();
        std::cout << "Time = " << tiempoSimulado.getValorTiempo() << std::endl;
        dbPedestrian1.caminarPedestrians(tiempoSimulado.getValorTiempo());

        dbPedestrian1.mostrarPedestrians();
        if (tiempoSimulado.getWriteNow()) {
            std::string folderName = std::to_string(tiempoSimulado.getValorTiempo());
            createFolder(folderName);
            dbPedestrian1.imprimirPedestrians(folderName);
            dbNode1.imprimirCantPedestrianEvacuted(folderName);
        }
    }
}
