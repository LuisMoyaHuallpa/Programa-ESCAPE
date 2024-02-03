#include "tiempo.h"
#include "dictionary.h"
#include <cstdlib>
#include <string>

int tiempo::deltaTiempo = 1;

tiempo* tiempo::tiempoInstance = nullptr;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tiempo::tiempo() {
    (*this).valorTiempo = 0;
    (*this).deltaT = 1;
    (*this).graphicPrintoutPeriod = 1;
    (*this).writeNow = true;
    (*this).endTime = std::stoi(dictionary::controlDict["endTime"]);
    inicializarNumberSimulation();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void tiempo::setValorTiempo(int valorTiempo) {
    (*this).valorTiempo = valorTiempo;
}
void tiempo::setDeltaT(int deltaT) {
    (*this).deltaT = deltaT;  
}
void tiempo::setGraphicPrintoutPeriod(int graphicPrintoutPeriod) {
    (*this).graphicPrintoutPeriod = graphicPrintoutPeriod;
}  
void tiempo::setWriteNow(bool writeNow) {
    (*this).writeNow = writeNow;
}
void tiempo::setStartNumberSimulation(int startNumberSimulation) {
    (*this).startNumberSimulation = startNumberSimulation;
}
void tiempo::setINumberSimulation(int iNumberSimulation) {
    (*this).iNumberSimulation = iNumberSimulation;
}
void tiempo::setEndNumberSimulation(int endNumberSimulation) {
    (*this).endNumberSimulation = endNumberSimulation;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int tiempo::getValorTiempo() {
    return valorTiempo;
}
int tiempo::getDeltaT() {
    return deltaT;  
}
int tiempo::getGraphicPrintoutPeriod() {
    return graphicPrintoutPeriod;
}
bool tiempo::getWriteNow() {
    return writeNow;  
}
int tiempo::getStartNumberSimulation() {
    return startNumberSimulation;
}
int tiempo::getINumberSimulation() {
    return iNumberSimulation;
}
int tiempo::getEndNumberSimulation() {
    return endNumberSimulation;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tiempo *tiempo::get() {
    if (!tiempoInstance) {
        tiempoInstance =  new tiempo();
    }
    return tiempoInstance;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tiempo& tiempo::operator++(int) {
    setValorTiempo(valorTiempo + deltaT); 
    return *this;
}
void tiempo::aumentarTiempo() {
    setValorTiempo(valorTiempo + deltaT); 
}
void tiempo::aumentarINumberSimulation() {
    setINumberSimulation(getINumberSimulation()+1);
}
void tiempo::inicializarNumberSimulation() {
    /* Inicializar las variables de NumberSimulation*/
    // si lee archivos de estados pasados, si
    if (dictionary::controlDict["computationContinued"] == "yes") {
        if (dictionary::controlDict["stopSimulationAt"] == "endNumberSimulation") {
            extractINumberSimulation();
            endNumberSimulation = std::stoi(dictionary::controlDict["endNumberSimulation"]);
        }
        else if (dictionary::controlDict["stopSimulationAt"] == "addNumberSimulation") {
            extractINumberSimulation();
            endNumberSimulation = startNumberSimulation + std::stoi(dictionary::controlDict["addNumberSimulation"]);
        }
    }
    // si no lee estados pasados
    else {
        startNumberSimulation = 1;
        iNumberSimulation = 1;
        if (dictionary::controlDict["stopSimulationAt"] == "endNumberSimulation") {
            endNumberSimulation = std::stoi(dictionary::controlDict["endNumberSimulation"]);
        }
       }
}
void tiempo::extractINumberSimulation() {
    /* Extrar el numero de simulacion actual segun el archivo sim de estados
        anteriores del control de la variable previousComputation*/
    if (dictionary::controlDict.find("previousComputationFile") != dictionary::controlDict.end()) {
        std::string lastFile_str = dictionary::controlDict["previousComputationFile"];   
        // busca el primer numero del 1-9 del nombre del archivo de estados
        size_t posicion = lastFile_str.find_first_of("123456789");
        int iLastFile = std::stoi(lastFile_str.substr(posicion));
        startNumberSimulation = iLastFile;
        iNumberSimulation = iLastFile;
    }
    else {
        std::cout << "'previousComputationFile' no está presente en el controDict." << std::endl;
        exit(1);
    }
}
bool tiempo::running() {
    return valorTiempo < (endTime - 0.5*deltaT);
}
void tiempo::mostrarTiempo() {
    // Mostrar en terminal tiempo actual.
    std::cout << "Time = " << getValorTiempo() << std::endl;
}
void tiempo::crearCarpetaTiempo() {
    if (getWriteNow()) {
        std::string folderName = std::to_string(getValorTiempo());
        if (mkdir(folderName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0) {
            std::cout << "Carpeta creada exitosamente." << std::endl;
        } else {
            // std::cerr << "Error al crear la carpeta." << std::endl;
        }
    }
}
bool tiempo::verificarGraphicPrintout() {
    if (getValorTiempo() % getGraphicPrintoutPeriod() == 0) {
        return true;
    }
    else {
        return false;
    }
}
