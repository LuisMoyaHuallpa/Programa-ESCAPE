#include "nodes.h"

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

    int n, x, y, e, r;
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
        dbnodes.push_back(node(n, x, y, e, r));
        }
    file.close(); 
}

node* nodes::extracionNode(int index) {
    node* nodeExtraido = &dbnodes.at(index);
    return nodeExtraido;
}
void nodes::imprimirNodes() {
    for (int i = 0; i < dbnodes.size(); i++) {
        dbnodes.at(i).imprimirNode();
    }
}
