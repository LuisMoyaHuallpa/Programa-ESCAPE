#ifndef state_h
#define state_h

#include <fstream>
#include <vector>
#include <iostream>

class state {

private:
    std::vector<int> densityLinks;

public:
    state();
    state(std::vector<int> densityLinks);

    void setDensityLinks(std::vector<int> densityLinks);

    std::vector<int> getDensityLinks();

    bool operator==(state stateObject);
    void agregarElementoState(int agregarElementoState);
    void mostrarState();
    void imprimirState(std::fstream& file);

};

#endif
