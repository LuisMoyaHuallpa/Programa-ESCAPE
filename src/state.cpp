#include "state.h"
#include "stateMatrix.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
state::state() {
}
state::state(std::vector<int> densityLinks)
    : densityLinks(densityLinks){
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const std::vector<int>& state::getDensityLinks() const {
    return densityLinks;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool state::operator==(const state state2) const {
    /* Compara si dos estados son iguales*/
    if (densityLinks.size() != state2.densityLinks.size()) {
        return false;
    }
    // Compara si los elementos de densityLinks son idénticos
    for (int i = 0; i < densityLinks.size(); i++) {
        if (densityLinks[i] != state2.getDensityLinks()[i]) {
            return false;
        }
    }
    // Si llegamos aquí, todos los elementos de densityLinks son iguales
    return true;
}
void state::mostrarState() const {
    for (int i = 0; i < densityLinks.size(); i++) {
        std::cout << densityLinks.at(i) << ',';
    }
}
void state::imprimirState(std::fstream& file) const {
    for (int i = 0; i < stateMatrix::tamanoVectorIO; i++) {
        if (i < densityLinks.size()) {
            file << densityLinks.at(i) << ',';
        } else {
            file << "0,";
        }
    }
}
