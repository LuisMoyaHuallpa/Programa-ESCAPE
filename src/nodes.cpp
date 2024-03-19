#include "nodes.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodes* nodes::nodesInstance = nullptr;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodes::nodes() {
    (*this).fileName = dictionary::get()->lookupDefault("nodesFile");
    leerNodes(fileName);
}
nodes::nodes(std::string fileName) {
   leerNodes(fileName);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string nodes::getFileName() {
    return fileName;  
}
std::vector<std::shared_ptr<node>> nodes::getDbNodeTotal() {
    return dbNodeTotal;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodes* nodes::get() {
    /* si aun no existe crea la unica instancia de nodes*/
    if (!nodesInstance) {
        nodesInstance =  new nodes();
    }
    return nodesInstance;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void nodes::leerNodes(std::string fileName) {
    // Lectura de archivo de nodos
    std::fstream file;
    file.open(fileName, std::ios::in);

    if (file.fail()) {
        // std::cout << "Error opening the file nodes.csv" << std::endl;
        std::cout << "Error al abrir el archivo: " << getFileName() << std::endl;
        exit(1);
    }
    // Variables de una fila del archivo nodos, que seria un solo node
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idNode          |-->| IDNODE
    // x               |-->| POSICION X
    // y               |-->| POSICION Y
    // e               |-->| NODE DE EVACUACION, SI ES 1
    // r               |-->| 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int n, x, y, e, r;
    std::string n_str, y_str, x_str, e_str, r_str;
    // Guarda todo la informacion de una solo linea. 
    std::string line;
    // Recorre todas las lineas del archivo.
    while (std::getline(file, line)) {
        // Si el archivo tiene comentarios con #, no leerlos.
        if (line[0] == '#') {
            continue;
        }
        // Guardar cada line en la variable line  
        std::istringstream iss(line);
        // Guardar cada valor en las variables.
        std::getline(iss, n_str, ',');
        std::getline(iss, x_str, ',');
        std::getline(iss, y_str, ',');
        std::getline(iss, e_str, ',');
        std::getline(iss, r_str, '\n');
        // Cambiar de str a int
        n = std::stoi(n_str);
        x = std::stoi(x_str);
        y = std::stoi(y_str);
        e = std::stoi(e_str);
        r = std::stoi(r_str);
        // Creacion de cada persona en la data base.
        if (e == 0) {
            std::unique_ptr<node> nodoNuevo = std::make_unique<node>(n, vector2D(x, y));
            // node nodoNuevo1 = node(n, x, y);
            nodes::dbNodeTotal.push_back(std::move(nodoNuevo));
        }
        else {
            std::unique_ptr<nodeEvacuation> nodoEvacuationNuevo = std::make_unique<nodeEvacuation>(n, vector2D(x, y));
            // nodeEvacuation nodoEvacuationNuevo= nodeEvacuation(n, x, y);
            dbNodeTotal.push_back(std::move(nodoEvacuationNuevo));
        }
    }
    file.close(); 
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mostrar
void nodes::mostrarNodes() const {
    // Muestra en el terminal todos los nodos y sus datos.
    for (int i = 0; i < dbNodeTotal.size(); i++) {
        dbNodeTotal.at(i)->mostrarNode();
        dbNodeTotal.at(i)->mostrarQTable();
        // const node* baseNode = dbNode.at(i);
        // const nodeEvacuation* evacuationNode = dynamic_cast<const nodeEvacuation*>(baseNode);
        // if (evacuationNode) {
        //     std::cout << "nodeEvacuation: " << evacuationNode->getIdNode() << ", X: " << evacuationNode->getCoordX() << ", Y: " << evacuationNode->getCoordY() << std::endl;
        // }
    }
}
void nodes::mostrardbNodeTotal() const {
    for (int i = 0; i < dbNodeTotal.size(); i++) {
        dbNodeTotal.at(i)->mostrarNode();
        dbNodeTotal.at(i)->mostrarQTable();
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// imprimir
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// void nodes::imprimirCantPedestrianEvacuted(std::string folderName) {
//     std::fstream file3;
//     file3.open(folderName + "/cantPedestrianEvacuated",std::ios::out);
//     for (int i = 0; i < dbNode.size(); i++) {
//         // const node* baseNode = dbNode.at(i);
//         // const nodeEvacuation* evacuationNode = dynamic_cast<const nodeEvacuation*>(baseNode);
//         // if (evacuationNode) {
//         //     file3 << evacuationNode->getPersonasEvacudas();
//         // }
//     }

// }
