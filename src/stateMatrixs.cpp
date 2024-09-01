#include "stateMatrixs.h"
#include "Q.h"
#include "io.h"
#include "stateMatrix.h"
#include <vector>

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
    // const std::string typeFile = ".csv";
    std::ostringstream filenameStream;
    // Crea el archivo inicial con el siguiente formato sim_000000001.csv
    filenameStream << std::setw(9) << std::setfill('0') << tiempo::get()->getINumberSimulation() ;
    // Nombre final de exportacion 
    return preName + filenameStream.str();
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
void stateMatrixs::leerDbStateMatrixs() {
    // si la opcion de lectura de datos anteriores de stateMatrixs esta activa
    // if (dictionary::controlDict["computationContinued"] == "yes") {
    if (std::get<std::string>(dictionary::get()->lookupDefault("sarsaProcesses")) == "trained") {
        dictionary::get()->getControlDict()["computationContinued"] = "yes";
    }
    if (std::get<bool>(dictionary::get()->lookupDefault("computationContinued")) == true) {
        // /* Empieza el timing*/
        // auto start = std::chrono::high_resolution_clock::now();
        /* Lectura de datos de una simulación pasada.*/
        std::fstream file;
        file.open(simulationFile + std::get<std::string>(dictionary::get()->lookup("previousComputationFile")), std::ios::in);
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
        std::string line;
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
        int idNode;
        int s;
        double Qa;
        int O;
        int o1, o2, o3, o4, o5, o6, o7, o8, o9, o10;
        std::string p0;
        std::string idNode_str;
        std::string s_str;
        std::string Q_str;
        std::string O_str;
        std::string o1_str, o2_str, o3_str, o4_str, o5_str, o6_str, o7_str, o8_str, o9_str, o10_str; 
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
            node* nodeLeido = nodes::get()->getDbNodeTotal().at(idNode).get();
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
            QsLeido.clear();
            for (int i = 0; i < io::tamanoElementosIO; ++i) {
                if (i < nodeLeido->getLinkConnectionsPtr().size()) {
                    std::getline(iss, Q_str, ',');
                    Qa = std::stod(Q_str);
                    QsLeido.push_back(Q(Qa, nodeLeido->getLinkConnectionsPtr().at(i)));
                } 
                else {
                    std::getline(iss, p0, ',');
                }
            }
            // !-----------------------------------------------------------------------
            // Elementos de observacion
            for (int i = 0; i < io::tamanoElementosIO; ++i) {
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
            // creaciones del stateMatrix
            stateMatrix* nuevoStateMatrix = new stateMatrix(nodeLeido, stateLeido, QsLeido);
            dbStateMatrixs.emplace_back(nuevoStateMatrix);
            nodeLeido->addStateMatrixExperimentadosPtr(nuevoStateMatrix);


            // std::getline(iss, o1_str, ',');
            // std::getline(iss, o2_str, ',');
            // std::getline(iss, o3_str, ',');
            // std::getline(iss, o4_str, ',');
            // std::getline(iss, o5_str, ',');
            // std::getline(iss, o6_str, ',');
            // std::getline(iss, o7_str, ',');
            // std::getline(iss, o8_str, ',');
            // std::getline(iss, o9_str, ',');
            // std::getline(iss, o10_str, '\n');
            // // Elementos de o
            // if (std::get<bool>(dictionary::get()->lookupDefault("observationStatePedestrian")) == true) {
            //     o1 = std::stoi(o1_str);
            //     o2 = std::stoi(o2_str);
            //     o3 = std::stoi(o3_str);
            //     o4 = std::stoi(o4_str);
            //     o5 = std::stoi(o5_str);
            //     o6 = std::stoi(o6_str);
            //     o7 = std::stoi(o7_str);
            //     o8 = std::stoi(o8_str);
            //     o9 = std::stoi(o9_str);
            //     o10 = std::stoi(o10_str);
            // }
            // !-----------------------------------------------------------------------
            // Grabar datos de la fila del stateMatrix en en Qtable del nodo numero id.
            // falta
            // nodes::get()->getDbNodeTotal().at(idNode)->getStateMatrixTable().push_back(stateMatrixLeido);

            // std::cout << std::endl;
            // nodes::get()->getDbNodeTotal().at(idNode)->getStateMatrixTableMap().emplace(stateMatrixLeido->getStateValue().getDensityLinks(),stateMatrixLeido);
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
