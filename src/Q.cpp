#include "Q.h"
#include "stateMatrix.h"
#include "link.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Q::Q()
    :
    valor(0),
    callePtr(nullptr),
    observaciones(0)
{
}
Q::Q(const double valor)
    :
    valor(valor),
    callePtr(nullptr),
    observaciones(0)
{
}
Q::Q(const link* const callePtr) :
    valor(0),
    callePtr(callePtr),
    observaciones(0)
{
}
Q::Q(const double valor, const link *const callePtr)
    : valor(valor), callePtr(callePtr), observaciones(0)
{
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Q::setObservaciones(int observaciones) {
    (*this).observaciones = observaciones;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double* Q::getValor() {
    return &valor;    
}
double Q::getValor() const {
    return valor;
}
const link* Q::getCallePtr() const {
    return callePtr;
}
int Q::getObservaciones() const {
    return observaciones;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Q::aumentar1Observacion() {
    observaciones += 1;
}
void Q::mostrarQs() const{
    if (callePtr == nullptr) {
        std::cout << valor << " ";
    }
    else {
        std::cout << valor << " ";
    }
}
// void Q::imprimirQs(std::fstream &file) const {
//     for (int i = 0; i < stateMatrix::tamanoVectorIO; i++) {
//         if (i < QsVector.size()) {
//             file << QsVector.at(i) << ',';
//         } else {
//             file << "0,";
//         }
//     }  
// }

