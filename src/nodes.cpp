#include "nodes.h"
#include "link.h"
#include "nodeEvacution.h"

nodes::nodes() {
    (*this).filename = "nodes.csv";
    leerNodes(filename);
    
}
nodes::nodes(std::string filename) {
   leerNodes(filename);
}

void nodes::leerNodes(std::string filename) {
    std::fstream file;
    file.open(filename, std::ios::in);

    if (file.fail()) {
        std::cout << "Error opening the file nodes.csv" << std::endl;
        exit(1);
    }

    //- Variables de una fila del archivo node.csv, que seria un node
    int n, //<-id 
        x, //<-posicion x 
        y, //<-posicion y
        e, //<-node de evacucion, si es 1
        r;
    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == '#') {
            continue;
        }
        
        std::istringstream iss(line);
        std::string n_str, y_str, x_str, e_str, r_str;

        std::getline(iss, n_str, ',');
        std::getline(iss, x_str, ',');
        std::getline(iss, y_str, ',');
        std::getline(iss, e_str, ',');
        std::getline(iss, r_str, '\n');

        n = std::stoi(n_str);
        x = std::stoi(x_str);
        y = std::stoi(y_str);
        e = std::stoi(e_str);
        r = std::stoi(r_str);
        if (e == 0) {
            dbnodes.push_back(new node(n, x, y));
        }
        else {
            dbnodes.push_back(new nodeEvacuation(n, x, y));
        }
    }
    file.close(); 
}

node* nodes::extracionNode(int index) {
    node* nodeExtraido = dbnodes.at(index);
    return nodeExtraido;
}
void nodes::mostrarNodes() {
    for (int i = 0; i < dbnodes.size(); i++) {
        dbnodes.at(i)->mostrarNode();
        dbnodes.at(i)->mostrarQTable();
        const node* baseNode = dbnodes.at(i);
        const nodeEvacuation* evacuationNode = dynamic_cast<const nodeEvacuation*>(baseNode);
        if (evacuationNode) {
            std::cout << "nodeEvacuation: " << evacuationNode->getIdNode() << ", X: " << evacuationNode->getCoordX() << ", Y: " << evacuationNode->getCoordY() << std::endl;
        }
    }
}
void nodes::imprimirNodes() {
    std::string fileStatesMatriz = "stateMatrices/sim_0.csv";
    std::fstream file;
    file.open(fileStatesMatriz, std::ios::out);
    for (int i = 0; i < dbnodes.size(); i++) {
        dbnodes.at(i)->ordenarQTable();
        dbnodes.at(i)->imprimirQTable(file);
    }
}

void nodes::imprimirCantPedestrianEvacuted(std::string folderName) {
    std::fstream file3;
    file3.open(folderName + "/cantPedestrianEvacuated",std::ios::out);
    for (int i = 0; i < dbnodes.size(); i++) {
        const node* baseNode = dbnodes.at(i);
        const nodeEvacuation* evacuationNode = dynamic_cast<const nodeEvacuation*>(baseNode);
        if (evacuationNode) {
            file3 << evacuationNode->getPersonasEvacudas();
        }
    }

}
