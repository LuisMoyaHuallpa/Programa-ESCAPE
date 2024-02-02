#include "tiempo.h"

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
    (*this).iNumberSimulation = 1;
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
void tiempo::setINumberSimulation(int iNumberSimulation) {
    (*this).iNumberSimulation = iNumberSimulation;
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
int tiempo::getINumberSimulation() {
    return iNumberSimulation;
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
