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

