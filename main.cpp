#include <fstream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "dbNode.h"
#include "dbLink.h"
#include "dbPedestrian.h"

// using std::endl;



int main() {

    dbNode dbNode1;
    dbLink::setListaNode(dbNode1);
    dbLink dbLink1;
    // dbLink1.mostrarLinks();
    dbPedestrian dbPedestrian1;
    dbPedestrian1.mostrarDbPedestrian();

};
