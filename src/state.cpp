#include "state.h"
#include <iostream>
#include <vector>

state::state() {
    
}
state::state(std::vector<int> densityLinks) {
    setDensityLinks(densityLinks); 
}

void state::setDensityLinks(std::vector<int> densityLinks) {
    (*this).densityLinks = densityLinks;
}

std::vector<int> state::getDensityLinks() {
    return densityLinks;
}

bool state::operator==(state stateObject) {
    if (densityLinks.size() != stateObject.densityLinks.size()) {
        return false;
    }
    // Compara si los elementos de densityLinks son idénticos
    for (int i = 0; i < densityLinks.size(); i++) {
        if (getDensityLinks()[i] != stateObject.getDensityLinks()[i]) {
            return false;
        }
    }
    // Si llegamos aquí, todos los elementos de densityLinks son iguales
    return true;
}
void state::agregarElementoState(int stateElemento) {
    densityLinks.push_back(stateElemento);
}
void state::mostrarState() {
    for (int i = 0; i < densityLinks.size(); i++) {
        std::cout << getDensityLinks().at(i) << ' ';
    }
}
void state::imprimirState(std::fstream& file) {
    int tamanoState = 10;
    for (int i = 0; i < tamanoState; i++) {
        if (i < densityLinks.size()) {
            file << getDensityLinks().at(i) << ' ';
        } else {
            file << "0 ";
        }
    }
}
