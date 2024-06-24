#include "io.h"
#include "nodeEvacution.h"
#include "nodes.h"
#include "pedestrians.h"
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
    if (dictionary::get()->lookup("totalEvacuatedCount") == "yes") {
        fileTotalPersonasEvacuadas.open(filenameData + "totalEvacuatedCount.csv", std::ios::out);
    }
    if (dictionary::get()->lookup("evacuatedCount") == "yes") {
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

