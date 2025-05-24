// MIT License
// Copyright (c) 2025 
// Luis Angel Moya Huallpa, Julio Cesar Ramirez Paredes, Erick Mas, Shunichi Koshimura
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "stateMatrixs.h"
#include "Q.h"
#include "dictionary.h"
#include "io.h"
#include "stateMatrix.h"
#include <vector>
#include "links.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrixs* stateMatrixs::stateMatrixsInstance = nullptr;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrixs::stateMatrixs() {
    // setINumeroSimulacion(1);
    // leerDbStateMatrixs();
    // Lectura de la ultima simulacion.
    // leerDbStateMatrixs(simulationFile + dictionary::controlDict["previousComputationFile"]); 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Nombre del la carpeta donde estan las simulaciones.
const std::string stateMatrixs::simulationFile = "stateMatrices/";

// stateMatrixs::stateMatrixs(nodes* dbNode) {
//     // dbNode contiene todos los nodos de la simulacion
//     (*this).dbNode = dbNode;
//     // Lectura de la ultima simulacion.
//     leerDbStateMatrixs(encontrarUltimoFile()); 
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<stateMatrix*> &stateMatrixs::getDbStateMatrixs() {
    return dbStateMatrixs;    
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrixs* stateMatrixs::get() {
    /* si aun no existe crea la unica instancia de nodes*/
    if (!stateMatrixsInstance) {
        stateMatrixsInstance =  new stateMatrixs();
    }
    return stateMatrixsInstance;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string stateMatrixs::creacionFileStateMatrix() const {
    /* Crear el nombre del archivo de exportacion.*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // iFileInicio     |-->| ID DEL ARCHIVO DE inicio, 1
    // preName         |-->| EXTENSION DE EXPORTACION
    // typeFile        |-->| EXTENSION DE EXPORTACION
    // filenameStream  |-->| ARCHIVO FALSO, PERMITE CONTROLAR LOS CARACTERES
    // DE UNA VARIABLE PARA LUEGO GUARDARLO EN UN STRING
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // aumento del numero de simulacion
    const std::string preName = "sim_";
    const std::string typeFile = ".csv";
    std::ostringstream filenameStream;
    // Crea el archivo inicial con el siguiente formato sim_000000001.csv
    filenameStream << std::setw(9) << std::setfill('0') << tiempo::get()->getINumberSimulation() ;
    // Nombre final de exportacion 
    return preName + filenameStream.str() + typeFile;
}
std::string stateMatrixs::encontrarUltimoFile() {
    // Encontrar la ultima simulacion para leerla
    std::string ultimoFile;
    ultimoFile = "stateMatrices/sim_000000006.csv";
    return ultimoFile;
}
std::string stateMatrixs::crearFilenameSalida(int numeroSimulacion) {
    /* Crear el nombre del archivo de exportacion.*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // iFileInicio     |-->| ID DEL ARCHIVO DE inicio, 1
    // preName         |-->| EXTENSION DE EXPORTACION
    // typeFile        |-->| EXTENSION DE EXPORTACION
    // filenameStream  |-->| ARCHIVO FALSO, PERMITE CONTROLAR LOS CARACTERES
    // DE UNA VARIABLE PARA LUEGO GUARDARLO EN UN STRING
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Si lee un archivo de estados
    // if (dictionary::controlDict["computationContinued"] == "yes" ) {
        
    // }
    // else {
        
    // }
    int iFileInicio = 1;
    std::string preName = "sim_";
    std::string typeFile = ".csv";
    std::ostringstream filenameStream;
    // Crea el archivo inicial con el siguiente formato sim_000000001.csv
    filenameStream << std::setw(9) << std::setfill('0') << iFileInicio ;
    // Nombre final de exportacion 
    return simulationFile +preName + filenameStream.str() + typeFile;
}
std::string stateMatrixs::fileNameSalida() {
    std::string lastFile_str = std::get<std::string>(dictionary::get()->lookup("previousComputationFile"));
    size_t posicion = lastFile_str.find_first_of("123456789");
    int iLastFile = std::stoi(lastFile_str.substr(posicion));
    std::string preName = "sim_";
    std::string typeFile = ".csv";
    std::ostringstream filenameStream;
    // Crea el archivo inicial con el siguiente formato sim_000000001.csv
    filenameStream << std::setw(9) << std::setfill('0') << iLastFile ;
    return simulationFile + preName + filenameStream.str() + typeFile;
}
// void stateMatrixs::agregarStateMatrix(stateMatrix stateMatrixElement) {
//     dbStateMatrixs.push_back(stateMatrixElement);
// }
void stateMatrixs::leerActionsDb(std::fstream& file) {
    /* Permite leer archivos de python, con este archivo actiondb puedo saber
        el orden las calles en cada nodo*/
    std::string line;
    char comma;
    int idNode, cantidadLinks;
    int idLink;
    actiondb.resize(nodes::get()->getDbNodeTotal().size()); 
    // si no existe el arhivo
    if (file.fail()) {
        std::cout << "Error opening the file " << std::endl;
        exit(1);
    }
    // lectura de cada line
    while (std::getline(file, line)) {
        // Si el archivo tiene comentarios con #, no leerlos.
        if (line[0] == '#') {
            continue;
        }
        // lectura de linea
        std::istringstream iss(line);
        if (!(iss >> idNode >> comma >> cantidadLinks >> comma)) {
            std::cerr << "Error al leer ID o count." << std::endl;
        }
        // verifica que no sea un nodo de evacuacion
        // porque no tiene conecciones
        if (nodes::get()->getDbNodeTotal().at(idNode).get()->verificarNodoEvacuation() == false) {
            // crea el tamaño del vector
            actiondb.at(idNode).resize(cantidadLinks);
            for (int i = 0; i < cantidadLinks; ++i) {
                if (!(iss >> idLink)) {
                    std::cerr << "Error al leer valor para conectionCalles en la posición " << i << std::endl;
                    return; // Sale de la función si hay un error
                }
                // agrega en action cada coneccion de calle segun el nodo 
                actiondb.at(idNode).at(i) = links::get()->getDbLinkTotal().at(idLink).get();
                // std::cout << actiondb.at(idNode).at(i)->getIdLink() << " ";
                // Ignora la coma entre valores, si no es el último valor
                if (i < cantidadLinks - 1) {
                    iss >> comma;  // Lee y descarta la coma
                    if (iss.fail()) {
                        std::cerr << "Error al leer la coma después del valor en la posición " << i << std::endl;
                        return; // Sale de la función si hay un error
                    }
                }
            }
        }
    } 
}
void stateMatrixs::leerDbStateMatrixs() {
  if (std::get<std::string>(dictionary::get()->lookupDefault("process")) == "trained") {
    dictionary::get()->getControlDict()["computationContinued"] = true;
  }
  // si la opcion de lectura de datos anteriores de stateMatrixs esta activa
  if (std::get<bool>(dictionary::get()->lookupDefault("computationContinued")) == true) {
    // lectura de datos de stateMatrixs de la version en python,
    // se debe leer de acuerdo a al orden a las conecciones de calles
    
    /* Lectura de datos de una simulación pasada.*/
    std::fstream file;
    if (std::get<bool>(dictionary::get()->lookupDefault("pythonVersion")) == true
	and std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")) == "in") {
      leerActionsDb(io::fileActionsDb.getFileFstream());
      file.open(std::get<std::string>(dictionary::get()->lookup("previousComputationFile")), std::ios::in);
    }
    else {
      file.open(simulationFile + std::get<std::string>(dictionary::get()->lookup("previousComputationFile")), std::ios::in);
    }
        // Si no existe el archivo
    if (file.fail()) {
      std::cout << "Error al abrir el archivo: "<< std::get<std::string>(dictionary::get()->lookup("previousComputationFile")) << std::endl;
      exit(1);
    }
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // iLinkConnection          |-->| POSICION EN EL ARREGLO linkConection
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // Actualizar la calle o linkActual, que es la calle por donde ira la persona. 

        // Guardar cada linea del archivo filname en la variable line.
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // id     |-->| ID DEL NODO O DE LA INTERSECCION
        // s      |-->| ESTADO DE UNA DE LAS CALLES EN linksConnection DE UN NODO
        // Q      |-->| Q DE LA CALLE 1 DE LOS linksConnection DEL NODO
        // o      |-->| OTRAS VARIABLES POR DEFINIR
        // p0     |-->| PALABRA EN 0, LEIDAS PERO GUARDADAS 
        // stateMatrixLeido |-->| CLASS SE CREA Y LUEGO SE DESTRUYE DENTRO DE ESTE
        // AMBITO
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // id podria pasar unsigned short int
        std::string line;
        int idNode;
        int s;
        double Qa;
        int O;
        std::string p0;
        std::string idNode_str;
        std::string s_str;
        std::string Q_str;
        std::string O_str;
        std::vector<int> stateLeido;
        std::vector<Q> QsLeido;
        // Recorre todas las line del archivo.
        while (std::getline(file, line)) {
            // Si el archivo tiene comentarios con #, no leerlos.
            if (line[0] == '#') {
                continue;
            }
            // !-----------------------------------------------------------------------
            // Guardar cada line en la variable line  
            std::istringstream iss(line);
            // Guarda la variable idNode
            std::getline(iss, idNode_str, ',');
            idNode = std::stoi(idNode_str);
            node* const nodeLeido = nodes::get()->getDbNodeTotal().at(idNode).get();
            // !-----------------------------------------------------------------------
            // Guarda los elementos de state
            stateLeido.clear();
            for (int i = 0; i < io::tamanoElementosIO; ++i) {
                if (i < nodeLeido->getLinkConnectionsPtr().size()) {
                    std::getline(iss, s_str, ',');
                    s = std::stoi(s_str);
                    stateLeido.push_back(s);
                } 
                else {
                    std::getline(iss, p0, ',');
                }
            }
            // !-----------------------------------------------------------------------
            // Elementos de Q
            // cuando se lee archivos stateMatrix de python
            if (std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")) == "in" and
            std::get<bool>(dictionary::get()->lookupDefault("pythonVersion")) == true) {
                QsLeido.clear();
                QsLeido.resize(nodeLeido->getLinkConnectionsPtr().size());
                for (int i = 0; i < io::tamanoElementosIO; ++i) {
                    // verificar si es nodo de evacuacion
                    if(nodeLeido->verificarNodoEvacuation()){
                        if (i == 0) {
                            std::getline(iss, Q_str, ',');
                            Qa = std::stod(Q_str);
                            QsLeido[i] = Q(Qa);
                        }
                        else {
                            std::getline(iss, p0, ',');
                        }
                    }
                    // cuando no es un nodo de evacuacion
                    else {
                        if (i < nodeLeido->getLinkConnectionsPtr().size()) {
                            std::getline(iss, Q_str, ',');
                            Qa = std::stod(Q_str);
                            QsLeido[i] = Q(Qa, actiondb.at(idNode).at(i));
                        } 
                        else {
                            std::getline(iss, p0, ',');
                        }
                    }

                }
            }
            // cuando se lee un archivo stateMatrix del mismo programa
            else {
                QsLeido.clear();
                // recorre el tamaño de elementos, por general es 10
                for (int i = 0; i < io::tamanoElementosIO; ++i) {
                    // verificar si es nodo de evacuacion
                    if(nodeLeido->verificarNodoEvacuation()){
                        if (i == 0) {
                            std::getline(iss, Q_str, ',');
                            Qa = std::stod(Q_str);
                            QsLeido.push_back(Q(Qa));
                        }
                        else {
                            std::getline(iss, p0, ',');
                        }
                    }
                    // cuando no es un nodo de evacuacion
                    else {
                        if (i < nodeLeido->getLinkConnectionsPtr().size()) {
                            std::getline(iss, Q_str, ',');
                            Qa = std::stod(Q_str);
                            QsLeido.push_back(Q(Qa, nodeLeido->getLinkConnectionsPtr().at(i)));
                        } 
                        else {
                            std::getline(iss, p0, ',');
                        }
                    }
                }
            }
            // !-----------------------------------------------------------------------
            // Elementos de observacion
            for (int i = 0; i < io::tamanoElementosIO; ++i) {
                // verificar si es nodo de evacuacion
                if(nodeLeido->verificarNodoEvacuation()){
                    if (i == 0) {
                        // siempre paso las observacines
                        std::getline(iss, O_str, ',');
                        // si quiero leer observaciones pasadas
                        if (std::get<bool>(dictionary::get()->lookupDefault("observationStatePedestrian")) == true) {
                            O = std::stod(O_str);
                            QsLeido.at(i).setObservaciones(O);
                        }
                    } 
                    else {
                        std::getline(iss, p0, ',');
                    }
                }
                // si no es nodo de evacuacion
                else {
                    if (i < nodeLeido->getLinkConnectionsPtr().size()) {
                        // siempre paso las observacines
                        std::getline(iss, O_str, ',');
                        // si quiero leer observaciones pasadas
                        if (std::get<bool>(dictionary::get()->lookupDefault("observationStatePedestrian")) == true) {
                            O = std::stod(O_str);
                            QsLeido.at(i).setObservaciones(O);
                        }
                    } 
                    else {
                        std::getline(iss, p0, ',');
                    }
                 
                }
            }
            // creaciones del stateMatrix
            stateMatrix* nuevoStateMatrix = new stateMatrix(nodeLeido, stateLeido, QsLeido);
            dbStateMatrixs.emplace_back(nuevoStateMatrix);
            nodeLeido->addStateMatrixExperimentadosPtr(nuevoStateMatrix);
        }
        file.close(); 
        // // Termina el timing
        // auto stop = std::chrono::high_resolution_clock::now();
        // auto duration = stop - start;
        // auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        // auto durationMinutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        // std::cout << "Duración Lectura: " << durationMinutes.count() << " min";
        // std::cout << " / " << durationSeconds.count() << " s" << std::endl;
    }

}
void stateMatrixs::mostrarDbStateMatrixs() const {
    // Mostrar todos los stateMatrix dentro de dbStateMatrixs.
   for (int i = 0; i < dbStateMatrixs.size(); i++) {
        dbStateMatrixs[i]->mostrarStateMatrix();
    }
}
void stateMatrixs::imprimirDbStateMatrixs(fileIO* const file) const {
    // Crear el nombre del archivo de exportacion.
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // file    |-->| ARCHIVO DE SALIDA, EL NOMBRE SE CREA CON crearFilenameSalida()
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // std::fstream file;
    // file.open(creacionArchivoSalida(), std::ios::out);
    // Recorre todos los nodos
    for (const auto& it : dbStateMatrixs) {
        // imprimir los statesMatrix de las tablas de cada nodo 
        it->imprimirStateMatrix(file);
    }
}
