#include "stateMatrixs.h"
#include "dictionary.h"
#include "pedestrian.h"
#include "stateMatrix.h"
#include "tiempo.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Nombre del la carpeta donde estan las simulaciones.
const std::string stateMatrixs::simulationFile = "stateMatrices/";

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
stateMatrixs::stateMatrixs() {
    setINumeroSimulacion(1);
    // Lectura de la ultima simulacion.
    // leerDbStateMatrixs(simulationFile + dictionary::controlDict["previousComputationFile"]); 
}
// stateMatrixs::stateMatrixs(nodes* dbNode) {
//     // dbNode contiene todos los nodos de la simulacion
//     (*this).dbNode = dbNode;
//     // Lectura de la ultima simulacion.
//     leerDbStateMatrixs(encontrarUltimoFile()); 
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void stateMatrixs::setINumeroSimulacion(int iNumeroSimulacion) {
    (*this).iNumeroSimulacion = iNumeroSimulacion;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int stateMatrixs::getINumeroSimulacion() {
    return iNumeroSimulacion;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string stateMatrixs::creacionArchivoSalida() {
    /* Crear el nombre del archivo de exportacion.*/
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // iFileInicio     |-->| ID DEL ARCHIVO DE inicio, 1
    // preName         |-->| EXTENSION DE EXPORTACION
    // typeFile        |-->| EXTENSION DE EXPORTACION
    // filenameStream  |-->| ARCHIVO FALSO, PERMITE CONTROLAR LOS CARACTERES
    // DE UNA VARIABLE PARA LUEGO GUARDARLO EN UN STRING
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // aumento del numero de simulacion
    std::string preName = "sim_";
    std::string typeFile = ".csv";
    std::ostringstream filenameStream;
    // Crea el archivo inicial con el siguiente formato sim_000000001.csv
    filenameStream << std::setw(9) << std::setfill('0') << tiempo::get()->getINumberSimulation() ;
    // Nombre final de exportacion 
    return simulationFile +preName + filenameStream.str() + typeFile;
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
    if (dictionary::controlDict["computationContinued"] == "yes" ) {
        
    }
    else {
        
    }
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
    std::string lastFile_str = dictionary::controlDict["previousComputationFile"];   
    size_t posicion = lastFile_str.find_first_of("123456789");
    int iLastFile = std::stoi(lastFile_str.substr(posicion));
    std::string preName = "sim_";
    std::string typeFile = ".csv";
    std::ostringstream filenameStream;
    // Crea el archivo inicial con el siguiente formato sim_000000001.csv
    filenameStream << std::setw(9) << std::setfill('0') << iLastFile ;
    return simulationFile + preName + filenameStream.str() + typeFile;
}
void stateMatrixs::agregarStateMatrix(stateMatrix stateMatrixElement) {
    dbStateMatrixs.push_back(stateMatrixElement);
}
void stateMatrixs::leerDbStateMatrixs(std::string filename) {
    // si la opcion de lectura de datos anteriores de stateMatrixs esta activa
    if (dictionary::controlDict["computationContinued"] == "yes") {
        /* Lectura de datos de una simulación pasada.*/
        std::fstream file;
        file.open(filename, std::ios::in);
        if (file.fail()) {
            std::cout << "Error al abrir el archivo: " << filename << std::endl;
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
        const int cantidadColumnasCsv = 10;
        // id podria pasar unsigned short int
        int idNode;
        int s;
        double Q;
        int o1, o2, o3, o4, o5, o6, o7, o8, o9, o10;
        std::string p0;
        std::string idNode_str;
        std::string s_str;
        std::string Q_str;
        std::string o1_str, o2_str, o3_str, o4_str, o5_str, o6_str, o7_str, o8_str, o9_str, o10_str; 
        stateMatrix stateMatrixLeido;
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
            // !-----------------------------------------------------------------------
            // Guarda los elementos de state
            state stateLeido;
            for (int i = 0; i < cantidadColumnasCsv; ++i) {
                if (i < nodes::get()->getDbNodeTotal().at(idNode)->getIdLinkConnection().size()) {
                    std::getline(iss, s_str, ',');
                    s = std::stoi(s_str);
                    stateLeido.getDensityLinks().push_back(s);
                } 
                else {
                    std::getline(iss, p0, ',');
                }
            }
            stateMatrixLeido.setStateValue(stateLeido);
            // !-----------------------------------------------------------------------
            // Elementos de Q
            std::vector<double> Qvector;
            Qs QsLeido;
            for (int i = 0; i < stateMatrix::getTamanoVector(); ++i) {
                if (i < nodes::get()->getDbNodeTotal().at(idNode)->getIdLinkConnection().size()) {
                    std::getline(iss, Q_str, ',');
                    Q = std::stod(Q_str);
                    QsLeido.getQsVector().push_back(Q);
                } 
                else {
                    std::getline(iss, p0, ',');
                }
            }
            stateMatrixLeido.setQsValue(QsLeido);
            // !-----------------------------------------------------------------------
            // Falta definir
            // Elementos de o
            std::getline(iss, o1_str, ',');
            std::getline(iss, o2_str, ',');
            std::getline(iss, o3_str, ',');
            std::getline(iss, o4_str, ',');
            std::getline(iss, o5_str, ',');
            std::getline(iss, o6_str, ',');
            std::getline(iss, o7_str, ',');
            std::getline(iss, o8_str, ',');
            std::getline(iss, o9_str, ',');
            std::getline(iss, o10_str, '\n');
            // Elementos de o
            if (dictionary::controlDict["readPedestrianMassState"] == "yes") {
                o1 = std::stoi(o1_str);
                o2 = std::stoi(o2_str);
                o3 = std::stoi(o3_str);
                o4 = std::stoi(o4_str);
                o5 = std::stoi(o5_str);
                o6 = std::stoi(o6_str);
                o7 = std::stoi(o7_str);
                o8 = std::stoi(o8_str);
                o9 = std::stoi(o9_str);
                o10 = std::stoi(o10_str);
            }
            // !-----------------------------------------------------------------------
            // Grabar datos de la fila del stateMatrix en en Qtable del nodo numero id.
            nodes::get()->getDbNodeTotal().at(idNode)->getStateMatrixTable().push_back(stateMatrixLeido);
        }
        file.close(); 
    }
}
void stateMatrixs::mostrarDbStateMatrixs(){
    // Mostrar todos los stateMatrix dentro de dbStateMatrixs.
    for (int i = 0; i < dbStateMatrixs.size(); i++) {
        dbStateMatrixs[i].mostrarStateMatrix();
    }
}
void stateMatrixs::imprimirDbStateMatrixs(){
    // Crear el nombre del archivo de exportacion.
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // file    |-->| ARCHIVO DE SALIDA, EL NOMBRE SE CREA CON crearFilenameSalida()
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::fstream file;
    file.open(creacionArchivoSalida(), std::ios::out);
    // Recorre todos los nodos
    for (int i = 0; i < nodes::get()->getDbNodeTotal().size(); i++) {
        // imprimir los statesMatrix de las tablas de cada nodo 
        nodes::get()->getDbNodeTotal().at(i)->imprimirQTable(file);
    }
}
