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

#include "node.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// extras
#include "link.h"
#include "pedestrian.h"
#include "stateMatrix.h"
#include "vector2D.h"
#include <cstddef>
#include <vector>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
node::node(const int idNode, const vector2D coordenada) :
    idNode(idNode), coordenada(coordenada){
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// destrutor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// node::~node(){}

std::string node::getNodeType() {
    return "node";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void node::setLinkConnectionsPtr(std::vector<link *> linkConnectionsPtr) {
    (*this).linkConnectionsPtr =  linkConnectionsPtr;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int node::getIdNode() const{
    return idNode;
}
const vector2D node::getCoordenada() const{
    return coordenada;
}
const std::vector<link*> node::getLinkConnectionsPtr() const {
    return linkConnectionsPtr;  
}
std::vector<stateMatrix*>* node::getStateMatrixExperimentadosPtr() {
    return &stateMatrixsExperimentadosPtr;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const node* node::buscarNodoFinal(link *callePtr) const {
    /* busqueda del node final segun la calle que se encuentre
        cada calle tiene un nodo de inicio y final dependiendo
        si esta de ida o vuelta delvolvera el nodo final esto seria ida */
    // Si el nodo donde estoy es el nodo 1 de la calle entonce nodo final es el nodo 2
    if(callePtr->getNode1Ptr() == this){
        return callePtr->getNode2Ptr();
    }
    // Si el nodo donde estoy es el nodo 2 de la calle entonce nodo final es el nodo 1
    else {
        return callePtr->getNode1Ptr();    
    }
}
// void node::buscarStateMatrix(stateMatrix stateMatrixBuscando, bool& verificarStateMatrix, int& iStateMatrixTable) {
//     /* recorre la tabla de stateMatrix en busqueda del elemento stateMatrixBuscando  */
//     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     // stateMatrixBuscando   |-->| ELEMENTO stateMatrix a buscar 
//     // verificarStateMatrix  |-->| SI ENCUENTRA EL ELEMENTO, ES VERDADERO 
//     for (int i = 0; i < stateMatrixTable.size(); i++) {
//         if (stateMatrixTable.at(i) == stateMatrixBuscando) {
//             verificarStateMatrix = true;
//             iStateMatrixTable = i;
//             return;
//         }
//     } 
//     // Establecer verificarQ basado en qEncontrado
//     verificarStateMatrix = false;
// }
// void node::addqQTable(stateActionQ qElemento) {
//     qTable.push_back(qElemento); 
// }
// void node::ordenarQTable() {
//     std::sort(qTable.begin(), qTable.end(), stateActionQ::compararId);
// }
// void node::buscarQ(stateActionQ qBuscando, bool* verificarQ) {
//     std::cout << "buscando.." << std::endl;
//     verificarQ = false;
//     for (int i = 0; i < getQTable().size(); i++) {
//         if (getQTable().at(i) == qBuscando) {
//             std::cout << "hola";
//             // qEncontrado = &getQTable().at(i);
//             *verificarQ = true;
//             std::cout << *verificarQ << std::endl;
//             break;
//         }
//     } 
//     *verificarQ = false;
// }
// void node::crearStateMatrix() {
//     stateMatrix stateMatrixElement;
//     for (int i = 0; i < qTable.size(); i++) {
//         qTable[i].getQ();
//     }
// }
estado node::estadoPedestrianEnNodo() const {
    return evacuando;    
}
bool node::verificarNodoEvacuation() const {
    return false;    
}
std::vector<int> node::stateObservado() const {
    // vector de estado
    std::vector<int> stateObservado;
    // Reserva espacio en el vector
    stateObservado.reserve(linkConnectionsPtr.size());
    // asignacion de estados
    for (link* calle : linkConnectionsPtr) {
        stateObservado.push_back(calle->getDensityLevel());
    }
    return stateObservado;
}
double node::calcularDistanciaA(const node* nodo2) const {
    /* calcula la distancia entre dos nodos*/
    return coordenada.distanciaA(nodo2->getCoordenada());
}
double node::calcularDistanciaA(const vector2D &position) const {
    /* calcula la distancia entre dos nodos*/
    return coordenada.distanciaA(position);
}
void node::addLink(link *calle) {
    /* agrega una calle en el vector de linkConnections*/
    linkConnectionsPtr.push_back(calle);
}
void node::addStateMatrixExperimentadosPtr(stateMatrix *stateMatrixExperimentado){
    /* agrega un stateMatrixExperimentado en el vector stateMatrixsExperimentado*/
    stateMatrixsExperimentadosPtr.push_back(stateMatrixExperimentado);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mostrar
void node::mostrarNode() const {
    /* Muestra en el terminal datos del nodo:
    // IdNode
    // x y
    // idLinkConnections*/
    std::cout << "Node: " << idNode << std::endl;
    std::cout << "x: " << coordenada.getX() << " ";
    std::cout << "y: " << coordenada.getY() << std::endl;
    std::cout << "linkConnections: ";
    for (int i = 0; i < linkConnectionsPtr.size(); i++) {
        std::cout << linkConnectionsPtr.at(i)->getIdLink() << " "; 
        std::cout << "p: "<< linkConnectionsPtr.at(i)->calcularPedestriansLink() << " "; 
        std::cout << "d: " <<linkConnectionsPtr.at(i)->getDensityLevel() << "|"; 
    }
    std::cout << std::endl;
}
void node::mostrarStateMatrixTable() const {
    /* muestra la tabla de stateMatrix experimentado*/
    std::cout << "Qtable: " << std::endl;
    for (const stateMatrix* const elemento : stateMatrixsExperimentadosPtr) {
        elemento->mostrarStateMatrix();
    } 
}
void node::imprimirAction(std::fstream& file) const {
    /* impresion de una linea de actionDb*/ 
    // id, cantidadCalles, idCalle....
    file << idNode << ",";
    file << linkConnectionsPtr.size() << ",";
    // imprime el id de la calle
    for (auto it = linkConnectionsPtr.begin(); it != linkConnectionsPtr.end(); ++it) {
        file << (*it)->getIdLink();
        file << ",";
    }
    // recorre los elementos de impresion de una fila
    // por defecto esta 10
    size_t faltante = io::tamanoElementosIO - linkConnectionsPtr.size();
    for (size_t i = 0; i < faltante; i++) {
        // solo la ultima pornerle sin coma
        if (i == faltante - 1) {
            file << "0";
        }
        else {
            file << "0,";
        }
    }
        
    file << std::endl;
}
void node::imprimirTransition(std::fstream& file) const {
    /* impresion de una linea de transition*/ 
    // id, cantidadCalles, idNode...
    file << idNode << ",";
    file << linkConnectionsPtr.size() << ",";
    // imprime el id de la calle
    for (auto it = linkConnectionsPtr.begin(); it != linkConnectionsPtr.end(); ++it) {
        // da el otro nodo de la calle diferente al de idNode
        if ((*it)->getNode1Ptr() == this) {
            file << (*it)->getNode2Ptr()->idNode;
        }
        else {
            file << (*it)->getNode1Ptr()->idNode;
        }
        if (std::next(it) != linkConnectionsPtr.end()) {
            file << ",";
        }
    }
    // recorre los elementos de impresion de una fila
    // por defecto esta 10
    size_t faltante = io::tamanoElementosIO - linkConnectionsPtr.size();
    for (size_t i = 0; i < faltante; i++) {
        // solo la ultima pornerle sin coma
        if (i == faltante - 1) {
            file << "0";
        }
        else {
            file << "0,";
        }
    }
 
    file << std::endl;
}


