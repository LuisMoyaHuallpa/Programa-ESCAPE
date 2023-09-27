#include "tiempo.h"

int tiempo::deltaTiempo = 1;

tiempo::tiempo() {
    (*this).valorTiempo = 0;
    (*this).deltaT = 1;
    (*this).writeNow = true;
    (*this).endTime = 200;
}

void tiempo::setValorTiempo(int valorTiempo) {
    (*this).valorTiempo = valorTiempo;
}
void tiempo::setDeltaT(int deltaT) {
    (*this).deltaT = deltaT;  
}
void tiempo::setWriteNow(bool writeNow) {
    (*this).writeNow = writeNow;
}

int tiempo::getValorTiempo() {
    return valorTiempo;
}
int tiempo::getDeltaT() {
    return deltaT;  
}
bool tiempo::getWriteNow() {
    return writeNow;  
}


tiempo& tiempo::operator++(int) {
    setValorTiempo(valorTiempo + deltaT); 
    return *this;
}
bool tiempo::running() {
    return valorTiempo < (endTime - 0.5*deltaT);
}
