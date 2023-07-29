#include "dbNode.h"


#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

dbNode::dbNode() {
    (*this).filename = "nodes.csv";
    leerDbNode(filename);
    
}
dbNode::dbNode(std::string filename) {
   leerDbNode(filename);
}

void dbNode::leerDbNode(std::string filename) {

    std::fstream nodeFile;
    nodeFile.open(filename, std::ios::in);

   if (nodeFile.fail()) {
        std::cout << "Error opening the file nodes.csv" << std::endl;
        exit(1);
    }

    int n, x, y, e, r;
    std::string line;

    while (std::getline(nodeFile, line)) {
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
        nodes.push_back(node(n, x, y, e, r));
        }
    
    nodeFile.close(); 

 
}

node dbNode::extracionNode(int index) {
    node nodeExtraido = nodes.at(index);
    return nodeExtraido;
}

// void dbNode::usarlink() {
//     link ob(*this); 
// }
