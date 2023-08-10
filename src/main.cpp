#include <fstream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "nodes.h"
#include "links.h"
#include "pedestrians.h"
#include "tiempo.h"
// using std::endl;



int main() {
    nodes dbNode1;
    nodes dbNode2("nodes.csv");
    links dbLink1(&dbNode1);
    // dbLink1.mostrarLinks();
    // dbNode1.imprimirNodes();
    pedestrians dbPedestrian1(&dbNode1);
    // dbPedestrian1.mostrarPedestrians();

    tiempo tiempoSimulado;

    while (tiempoSimulado.running())
    {
        tiempoSimulado++;
        std::cout << "Time = " << tiempoSimulado.getValorTiempo() << std::endl;

        dbPedestrian1.caminarPedestrians();
        dbPedestrian1.mostrarPedestrians();

    }

}
