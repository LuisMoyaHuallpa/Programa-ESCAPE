#ifndef pedestrians_h
#define pedestrians_h

#include "pedestrian.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include "nodes.h"

class pedestrians {

private:
    std::string filename;
    std::vector<pedestrian> dbPedestrians;
    int numberPedestrian;
    nodes* dbNode;

public:
    pedestrians();
    pedestrians(nodes* dbNode);
    pedestrians(std::string filename);

    void leerPedestrians(std::string filename);
    void mostrarPedestrians();
    void imprimirPedestrians(std::string foldeName);
    void calcularNumberPedestrian();
    void caminarPedestrians(int valorTiempo);
    void calcularDistribucionRayleigh();
    
};
#endif
