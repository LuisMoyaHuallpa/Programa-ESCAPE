#include "io.h"
#include "pedestrians.h"

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
    // crea directorios
    crearCarpetasOutput();
    if (std::get<bool>(dictionary::get()->lookupDefault("totalEvacuatedCount")) == true) {
        fileTotalPersonasEvacuadas.open(filenameData + filenameTotalEvacuatedCount, std::ios::out);
    }
    if (std::get<bool>(dictionary::get()->lookupDefault("evacuatedCount")) == true) {
        filePersonasEvacuadasNodeEvacuation.open(filenameData + filenameEvacuatedCount, std::ios::out);
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
    if (std::get<std::string>(dictionary::get()->lookup("sarsaProcesses")) == "trained") {
        if (tiempo::get()->verificarGraphicPrintout()) {
            // imprimir datos de personas: posicion y velocidad
            if (std::get<bool>(dictionary::get()->lookupDefault("graphicPrintout")) == true) {
                pedestrians::get()->imprimirPedestrians();
            }
            // imprime personas totales evacuadas
            if (std::get<bool>(dictionary::get()->lookupDefault("totalEvacuatedCount")) == true) {
                nodeEvacuation::imprimirTotalPersonasEvacuadas(fileTotalPersonasEvacuadas);
            }
            // imprime personas evacuadas por node evacuacion
            if (std::get<bool>(dictionary::get()->lookupDefault("evacuatedCount")) == true) {
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
