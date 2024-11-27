#include "tiempo.h"
#include "dictionary.h"
#include "nodes.h"
#include "links.h"
#include "pedestrians.h"
#include <chrono>

int tiempo::deltaTiempo = 1;
std::string tiempo::filenameData = "data/";


tiempo* tiempo::tiempoInstance = nullptr;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
tiempo::tiempo()
    : deltaT(1),
      valorTiempo(0),
      endTime(std::get<int>(dictionary::get()->lookup("endTime"))),
      graphicPrintoutPeriod(std::get<int>(dictionary::get()->lookupDefault("graphicPrintoutPeriod"))),
      pedestrianCountPeriod(std::get<int>(dictionary::get()->lookupDefault("pedestrianCountPeriod")))
{
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
    // aumenta el tiempo de evacuacion
    valorTiempo += deltaT;
}
void tiempo::aumentarINumberSimulation() {
    // aumentar el numero de simulacion
    // setINumberSimulation(getINumberSimulation()+1);
    iNumberSimulation += 1;
    // reiniciar el tiempo
    valorTiempo = 0;
    // reiniciar el conteo de personas Evacuadas
    nodeDestino::totalPersonasEvacuadas = 0;
    // regresar a las personas al nodo de arranque
    pedestrians::get()->reiniciarPedestrians();
    nodes::get()->reiniciarNodesEvacuations();
    // reinicia la lista de personas en calles
    links::get()->resetLinks();
    // reinicar el timer de una simulacion 
    startTimeSimulation = std::chrono::high_resolution_clock::now();
}
void tiempo::inicializarNumberSimulation() {
    /* Inicializar las variables de NumberSimulation*/
    // Para proceso de calibracion
    if(std::get<std::string>(dictionary::get()->lookupDefault("process")) == "calibration"){
        // si lee statematrix
        if (std::get<bool>(dictionary::get()->lookupDefault("computationContinued")) == true) {
            startNumberSimulation = 0;
            endNumberSimulation = std::get<int>(dictionary::get()->lookup("endNumberSimulation"));
            startNumberSimulation = startNumberSimulation + 1;
            iNumberSimulation = startNumberSimulation;
        }
        // si no lee statematrix
        else {
            // inicia el la simulacion 1
            startNumberSimulation = 1;
            iNumberSimulation = 1;
            endNumberSimulation = std::get<int>(dictionary::get()->lookup("endNumberSimulation"));
        }
        // iniciar el timer tiempo real de simulacion
        startTimeSimulation = std::chrono::high_resolution_clock::now();
    }
    // Para proceso ya entrenado
    else if (std::get<std::string>(dictionary::get()->lookupDefault("process")) == "trained"){
        // iniciar el timer tiempo real de simulacion
        startTimeSimulation = std::chrono::high_resolution_clock::now();
        startNumberSimulation = 1;
        iNumberSimulation = 1;
        // solo 1 simulacion
        endNumberSimulation = 1;
    }
}
int tiempo::extractINumberSimulation() const {
    /* Extrar el numero de simulacion actual segun el archivo sim de estados
        anteriores del control de la variable previousComputation*/
    const std::string lastFile_str = std::get<std::string>(dictionary::get()->lookup("previousComputationFile"));
    // busca el primer numero del 1-9 del nombre del archivo de estados
    const size_t posicion = lastFile_str.find_first_of("123456789");
    return std::stoi(lastFile_str.substr(posicion));
}
void tiempo::calcularRandomChoiceRate() {
    const int k = iNumberSimulation;
    const int N = endNumberSimulation;
    // valor por default, puede ser 4 o 9 
    double temp = 4.0;
    // buscar nombre correcto
    // en proceso de calibracion
    if (std::get<std::string>(dictionary::get()->lookupDefault("process")) == "calibration") {
        // en busca el keyword exploration
        auto it = dictionary::get()->getControlDict().find("exploration");
        if (it != dictionary::get()->getControlDict().end()) {
            // Clave encontrada, proceder con la operación
            temp = calcularTemp(std::get<double>(it->second));
        }
        // formula para random choice
        const double gleeFactor = temp / double(N);
        // el -1 es para empezar el numero de simulaciones en 0
        randomChoiceRate = 1.0 / (gleeFactor * double(k - 1) + 1.0);
    }
    // en proceso de trained
    else if(std::get<std::string>(dictionary::get()->lookupDefault("process")) == "trained") {
        // para que solo eliga sarsa nada de aletorio
        randomChoiceRate = 0;
    }
}
const double tiempo::calcularTemp(const double r) const {
    const int N = endNumberSimulation;
    const double factor = N - 1;
    return (N - r * factor) / (r * factor);
}
bool tiempo::running() {
    /* contrala el tiempo de evacuacion*/
    // Verificar si todas las personas han sido evacuadas
    if (!nodeDestino::verificarEvacuacionTotal()) {
        endTime = valorTiempo;
        return false;    
    }
    // Verificar si el tiempo actual es menor al tiempo total de la evacuación ajustado
    else if (valorTiempo >= (endTime - 0.5 * deltaT)) {
        return false;
    }
    return true;
}
void tiempo::mostrarIResultadosSimulacion() {
    // mostrar 
    std::cout << "***** Simu: " << iNumberSimulation << " *****" << std::endl;
    std::cout << "epsilon greedy - exploration: " << randomChoiceRate << std::endl;
    std::cout << "survived pedestrian: " << nodeDestino::getTotalPersonasEvacuadas() << std::endl;
    // termino de la simulacion
    endTimeSimulation = std::chrono::high_resolution_clock::now();
    // tiempo de simulacion
    const auto duration = endTimeSimulation - startTimeSimulation;
    const auto miliSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    const auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    const auto durationMinutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    std::cout << "Duración: " << durationMinutes.count() << " min";
    std::cout << " / " << durationSeconds.count() << " s";
    std::cout << " / " << miliSeconds.count() << " ms" << std::endl;
    std::cout << std::endl;
}
void tiempo::mostrarTiempo() const {
    // Mostrar en terminal tiempo actual.
    std::cout << "Time = " << valorTiempo << std::endl;
}
bool tiempo::verificarGraphicPrintoutPeriod() const {
    /* cada cuando imprimir variables*/
    return (getValorTiempo() % graphicPrintoutPeriod == 0);
}
bool tiempo::verificarPedestrianCountPeriod() const {
    /* cada cuando debe contar las personas*/
    return getValorTiempo() % pedestrianCountPeriod == 0;
}
