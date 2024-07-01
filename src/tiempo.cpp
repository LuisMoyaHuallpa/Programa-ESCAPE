#include "tiempo.h"
#include "dictionary.h"
#include "nodeEvacution.h"
#include "nodes.h"
#include "pedestrians.h"
#include <chrono>
#include <cstdlib>
#include <string>
#include <filesystem>

int tiempo::deltaTiempo = 1;
std::string tiempo::filenameData = "data/";


tiempo* tiempo::tiempoInstance = nullptr;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tiempo::tiempo()
    : deltaT(1), endTime(std::stoi(dictionary::get()->lookup("endTime"))),
      graphicPrintoutPeriod(std::stoi(dictionary::get()->lookupDefault("graphicPrintoutPeriod"))),
      pedestrianCountPeriod(std::stoi(dictionary::get()->lookupDefault("pedestrianCountPeriod"))){
    (*this).valorTiempo = 0;
    inicializarNumberSimulation();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void tiempo::setValorTiempo(int valorTiempo) {
    (*this).valorTiempo = valorTiempo;
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
int tiempo::getValorTiempo() const {
    return valorTiempo;
}
const int tiempo::getEndTime() const {
    return endTime;
}
const int tiempo::getDeltaT() const {
    return deltaT;  
}
const int tiempo::getGraphicPrintoutPeriod() const {
    return graphicPrintoutPeriod;
}
int tiempo::getStartNumberSimulation() const {
    return startNumberSimulation;
}
int tiempo::getINumberSimulation() const {
    return iNumberSimulation;
}
int tiempo::getEndNumberSimulation() const {
    return endNumberSimulation;
}
const int tiempo::getPedestrianCountPeriod() const {
    return pedestrianCountPeriod;
}
double tiempo::getRandomChoiceRate() const {
    return randomChoiceRate;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tiempo* tiempo::get() {
    if (!tiempoInstance) {
        tiempoInstance =  new tiempo();
    }
    return tiempoInstance;
}

std::string tiempo::getFilenameData() {
    return filenameData;
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
    // reiniciar el tiempo
    tiempo::get()->setValorTiempo(0);
    // reiniciar el conteo de personas Evacuadas
    nodeEvacuation::totalPersonasEvacuadas = 0;
    // regresar a las personas al nodo de arranque
    pedestrians::get()->reiniciarPedestriansNodeArranque();
    nodes::get()->reiniciarNodesEvacuations();
    // reinicia la lista de personas en calles
    links::get()->resetPedestriansLink();
    // reinicar el timer de una simulacion 
    startTimeSimulation = std::chrono::high_resolution_clock::now();
}
void tiempo::inicializarNumberSimulation() {
    /* Inicializar las variables de NumberSimulation*/
    // Para proceso de calibracion
    if(dictionary::get()->lookupDefault("sarsaProcesses")=="calibration"){
        // si lee archivos de estados pasados, si
        if (dictionary::get()->lookupDefault("computationContinued") == "yes") {
            if (dictionary::get()->lookup("stopSimulationAt") == "endNumberSimulation") {
                extractINumberSimulation();
                endNumberSimulation = std::stoi(dictionary::get()->lookup("endNumberSimulation"));
                startNumberSimulation = startNumberSimulation + 1;
                iNumberSimulation = startNumberSimulation;
            }
            else if (dictionary::get()->lookup("stopSimulationAt") == "addNumberSimulation") {
                extractINumberSimulation();
                endNumberSimulation = startNumberSimulation  + std::stoi(dictionary::get()->lookup("addNumberSimulation"));
                startNumberSimulation = startNumberSimulation + 1;
                iNumberSimulation = startNumberSimulation;
            }
        }
        // si no lee estados pasados
        else {
            // inicia el la simulacion 1
            startNumberSimulation = 1;
            iNumberSimulation = 1;
            if (dictionary::get()->lookupDefault("stopSimulationAt") == "endNumberSimulation") {
                endNumberSimulation = std::stoi(dictionary::get()->lookup("endNumberSimulation"));
            }
            else{
                endNumberSimulation = std::stoi(dictionary::get()->lookup("addNumberSimulation"));
            }
        }
        // iniciar el timer tiempo real de simulacion
        startTimeSimulation = std::chrono::high_resolution_clock::now();
    }
    // Para proceso ya entrenado
    else if (dictionary::get()->lookupDefault("sarsaProcesses")=="trained"){
        // iniciar el timer tiempo real de simulacion
        startTimeSimulation = std::chrono::high_resolution_clock::now();
        startNumberSimulation = 1;
        iNumberSimulation = 1;
        // solo 1 simulacion
        endNumberSimulation = 1;
    }
}
void tiempo::extractINumberSimulation() {
    /* Extrar el numero de simulacion actual segun el archivo sim de estados
        anteriores del control de la variable previousComputation*/
    if (dictionary::get()->getControlDict().find("previousComputationFile") != dictionary::get()->getControlDict().end()) {
        std::string lastFile_str = dictionary::get()->lookup("previousComputationFile");   
        // busca el primer numero del 1-9 del nombre del archivo de estados
        size_t posicion = lastFile_str.find_first_of("123456789");
        int iLastFile = std::stoi(lastFile_str.substr(posicion));
        startNumberSimulation = iLastFile ;
    }
}
void tiempo::calcularRandomChoiceRate() {
    int k = iNumberSimulation;
    int N = endNumberSimulation;
    if (dictionary::get()->lookup("sarsaProcesses") == "calibration") {
        // formula para random choice
        double gleeFactor = 4.0 / double(N);
        // el -1 es para empezar el numero de simulaciones en 0
        randomChoiceRate = 1.0 / (gleeFactor * double(k - 1) + 1.0);
    }
    else if(dictionary::get()->lookup("sarsaProcesses") == "trained") {
        randomChoiceRate = 0;
    }
}
bool tiempo::running() {
    // verificar que tiempo sea el menor a tiempo total de la evacuacion
    if (valorTiempo < (endTime - 0.5*deltaT)) {
        // verifica que todas las personas hayan sido evacuadas
        if (nodeEvacuation::totalPersonasEvacuadas == pedestrians::get()->getDbPedestrianTotal().size()) {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}
void tiempo::mostrarIResultadosSimulacion() {
    // mostrar 
    std::cout << "***** Simu: " << iNumberSimulation << " *****" << std::endl;
    std::cout << "epsilon greedy - exploration: " << randomChoiceRate << std::endl;
    std::cout << "survived pedestrian: " << nodeEvacuation::getTotalPersonasEvacuadas() << std::endl;
    // termino de la simulacion
    endTimeSimulation = std::chrono::high_resolution_clock::now();
    auto duration = endTimeSimulation - startTimeSimulation;
    // Calcula la duración en milisegundos
    // auto durationMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    // std::cout << "Duración en milisegundos: " << durationMilliseconds.count() << " ms" << std::endl;
    // Calcula la duración en segundos
    auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    auto durationMinutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    std::cout << "Duración: " << durationMinutes.count() << " min";
    std::cout << " / " << durationSeconds.count() << " s" << std::endl;
    std::cout << std::endl;
}
void tiempo::mostrarTiempo() const {
    // Mostrar en terminal tiempo actual.
    std::cout << "Time = " << valorTiempo << std::endl;
}
void tiempo::crearCarpetaTiempo() {
    std::string folderData = "data/";
    std::string folderName = std::to_string(getValorTiempo());
    std::string path = folderData + folderName;
    // crear carpeta de los tiempos en segundos para almacenar informacion
    mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}
bool tiempo::verificarGraphicPrintout() {
    if (getValorTiempo() % getGraphicPrintoutPeriod() == 0) {
        return true;
    }
    else {
        return false;
    }
}
bool tiempo::verificarPedestrianCountPeriod() {
    if (getValorTiempo() % getPedestrianCountPeriod() == 0) {
        return true;
    }
    else {
        return false;
    }
}

