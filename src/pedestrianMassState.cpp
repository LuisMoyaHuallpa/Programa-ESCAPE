#include "pedestrianMassState.h"
// #include "stateMatrix.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrianMassState::pedestrianMassState(){}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrianMassState::setPedestrianMassState(
    std::vector<int> pedestrianMassStateVector) {
    (*this).pedestrianMassStateVector = pedestrianMassStateVector;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getter
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<int>& pedestrianMassState::getPedestrianMassStateVector() {
    return pedestrianMassStateVector;  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrianMassState::mostrarPedestrianMassStateVector() const {
    for (int i = 0; i < pedestrianMassStateVector.size(); i++) {
        std::cout << pedestrianMassStateVector.at(i) << ",";
    }
}

void pedestrianMassState::imprimirPedestrianMassStateVector(std::fstream &file) const {
    for (int i = 0; i < 10; i++) {
        if (i < pedestrianMassStateVector.size()) {
            file << pedestrianMassStateVector.at(i) << ',';
        }
        // el ultimo valor debe ser sin coma
        else if (i == 9) {
            file << "0";
        }
        else {
            file << "0,";
        }
    }  
}
