#include "Q.h"
#include "stateMatrix.h"
#include "link.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Q::Q()
    :
    valor(0),
    callePtr(nullptr)
{
}
Q::Q(const link* const callePtr) :
    valor(0),
    callePtr(callePtr)
{
}
Q::Q(const double valor, const link *const callePtr)
    : valor(valor), callePtr(callePtr) {
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

