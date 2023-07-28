#include "dbLink.h"
#include "dbNode.h"

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>


dbNode dbLink::listaNode;
void dbLink::setListaNode(const dbNode& dbnode) {
    listaNode = dbnode;
}

dbLink::dbLink(){
    (*this).filename = "links.csv";
    leerDbLink(filename);
}
dbLink::dbLink(std::string filename){
    leerDbLink(filename);
}

void dbLink::leerDbLink(std::string filename){
    std::fstream file;
    file.open(filename, std::ios::in);

   if (file.fail()) {
       std::cout << "Error opening the file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line[0] == '#') {
            continue;
        }
        
        std::istringstream iss(line);
        std::string a1_str, a2_str, a3_str, a4_str, a5_str;

        std::getline(iss, a1_str, ',');
        std::getline(iss, a2_str, ',');
        std::getline(iss, a3_str, ',');
        std::getline(iss, a4_str, ',');
        std::getline(iss, a5_str, '\n');

        int a1 = std::stoi(a1_str);
        int a2= std::stoi(a2_str);
        int a3 = std::stoi(a3_str);
        int a4 = std::stoi(a4_str);
        int a5 = std::stoi(a5_str);
        links.push_back(link(a1, a2, a3, a4, a5));
        }
    
    file.close(); 
}

void dbLink::mostrarLinks(){
    for (int i=0; i <links.size(); i++) {
        std::cout << links.at(i).getId() << ' ';
        std::cout << links.at(i).getNode1().getId() << ' ';
        std::cout << links.at(i).getNode2().getId() << ' ';
        std::cout << std::endl;
    }
}
link dbLink::extraccionLink(int index) {
    link linkExtraido = links.at(index);
    return linkExtraido;
}
