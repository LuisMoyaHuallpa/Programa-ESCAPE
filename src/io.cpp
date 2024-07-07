#include "io.h"
#include "nodeEvacution.h"
#include "nodes.h"
#include "pedestrians.h"
#include "tiempo.h"
#include <fstream>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
io* io::ioInstance = nullptr;

std::fstream io::fileTotalPersonasEvacuadas;
std::fstream io::filePersonasEvacuadasNodeEvacuation;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
io::io() {
    filenameData = "data/";
    // crea directorios
    crearCarpetasOutput();
    if (dictionary::get()->lookupDefault("totalEvacuatedCount") == "yes") {
        fileTotalPersonasEvacuadas.open(filenameData + "totalEvacuatedCount.csv", std::ios::out);
    }
    if (dictionary::get()->lookupDefault("evacuatedCount") == "yes") {
        filePersonasEvacuadasNodeEvacuation.open(filenameData + "evacuatedCount.csv", std::ios::out);
    }
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
io* io::get() {
    /* si aun no existe crea la unica instancia de nodes*/
    if (!ioInstance) {
        ioInstance =  new io();
    }
    return ioInstance;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::fstream& io::getFileEvacuatedCount() {
    return fileTotalPersonasEvacuadas;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void io::crearCarpetasOutput() {
    // crear carpeta data
    mkdir(filenameData.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

}
void io::imprimirOutput() {
    if (dictionary::get()->lookup("sarsaProcesses") == "trained") {
        if (tiempo::get()->verificarGraphicPrintout()) {
            // imprimir datos de personas: posicion y velocidad
            if (dictionary::get()->lookupDefault("graphicPrintout") == "yes") {
                pedestrians::get()->imprimirPedestrians();
            }
            // imprime personas totales evacuadas
            if (dictionary::get()->lookupDefault("totalEvacuatedCount") == "yes") {
                nodeEvacuation::imprimirTotalPersonasEvacuadas(fileTotalPersonasEvacuadas);
            }
            // imprime personas evacuadas por node evacuacion
            if (dictionary::get()->lookupDefault("evacuatedCount") == "yes") {
                // impresion de id de nodos
                if (tiempo::get()->getValorTiempo() == 1) {
                    filePersonasEvacuadasNodeEvacuation << "id,";
                    for (int i = 0; i < nodes::get()->getDbNodeEvacuation().size(); i++) {
                        filePersonasEvacuadasNodeEvacuation << nodes::get()->getDbNodeEvacuation().at(i)->getIdNode();
                        if (i < nodes::get()->getDbNodeEvacuation().size() - 1) {
                            filePersonasEvacuadasNodeEvacuation << ",";
                        }
                }
                filePersonasEvacuadasNodeEvacuation << std::endl;
   
                }
                // impresion de personas evacuadas por nodo de evacuacion
                filePersonasEvacuadasNodeEvacuation << tiempo::get()->getValorTiempo() << ",";
                for (int i = 0; i < nodes::get()->getDbNodeEvacuation().size(); i++) {
                    nodes::get()->getDbNodeEvacuation().at(i)->imprimirPersonasEvacuadas(filePersonasEvacuadasNodeEvacuation);
                    if (i < nodes::get()->getDbNodeEvacuation().size() - 1) {
                        filePersonasEvacuadasNodeEvacuation << ",";
                    }
                }
                filePersonasEvacuadasNodeEvacuation << std::endl;
            }
        }
    }
}

