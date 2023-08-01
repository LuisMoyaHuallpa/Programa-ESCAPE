#include <fstream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "nodes.h"
#include "links.h"

// using std::endl;



int main() {
    nodes dbNode1;
    // dbLink::setListaNode(dbNode1);
    links dbLink1(&dbNode1);
    // dbLink1.mostrarLinks();
    dbNode1.imprimirNodes();


    // transLinks::setListaLink(dbLink1);
    // transLinks dbTransLink1;
    // dbTransLink1.mostrarTransLinks();
    // dbLink1.mostrarLinks();
    // dbPedestrian dbPedestrian1;
    // dbPedestrian1.mostrarDbPedestrian();
};
