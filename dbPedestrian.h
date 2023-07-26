#ifndef dbPedestrian_h
#define dbPedestrian_h

#include "pedestrian.h"
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

class dbPedestrian {

private:
    std::string filename;
    std::vector<pedestrian> pedestrians;

public:
    dbPedestrian();
    dbPedestrian(std::string filename);

    void leerDbPedestrian(std::string filename);
    void mostrarDbPedestrian();
};



#endif
