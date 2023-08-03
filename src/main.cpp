#include <fstream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "nodes.h"
#include "links.h"
#include "pedestrians.h"

// using std::endl;



int main() {
    nodes dbNode1;
    links dbLink1(&dbNode1);
    // dbLink1.mostrarLinks();
    dbNode1.imprimirNodes();
    pedestrians dbPedestrian1(&dbNode1);
    // dbPedestrian1.mostrarPedestrians();


};
