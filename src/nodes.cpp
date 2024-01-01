#include "nodes.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<node> nodes::dbNodeTotal;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodes::nodes() {
    (*this).fileName = "nodes.csv";
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
            node nodoNuevo = node(n, x, y);
            nodes::dbNodeTotal.push_back(nodoNuevo);
        }
        else {
            nodeEvacuation nodoEvacuationNuevo= nodeEvacuation(n, x, y);
            nodes::dbNodeTotal.push_back(nodoEvacuationNuevo);
        }
    }
    file.close(); 
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mostrar
void nodes::mostrarNodes() {
    // Muestra en el terminal todos los nodos y sus datos.
    for (int i = 0; i < nodes::dbNodeTotal.size(); i++) {
        nodes::dbNodeTotal.at(i).mostrarNode();
        nodes::dbNodeTotal.at(i).mostrarQTable();
        // const node* baseNode = dbNode.at(i);
        // const nodeEvacuation* evacuationNode = dynamic_cast<const nodeEvacuation*>(baseNode);
        // if (evacuationNode) {
        //     std::cout << "nodeEvacuation: " << evacuationNode->getIdNode() << ", X: " << evacuationNode->getCoordX() << ", Y: " << evacuationNode->getCoordY() << std::endl;
        // }
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// imprimir
// void nodes::imprimirNodes(std::fstream& file) {
//     for (int i = 0; i < dbNode.size(); i++) {
//         dbNode.at(i).ordenarQTable();
//         dbNode.at(i).imprimirQTable(file);
//     }
// }

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
