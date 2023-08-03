#include "links.h"
#include "link.h"
#include <iostream>

// nodes links::listaNode;
// void links::setListaNode(const nodes& dbnode) {
//     listaNode = dbnode;
// }

// links::links(){
//     (*this).filename = "links.csv";
//     leerLinks(filename);
// }
// links::links(std::string filename) : dbNode(){
//     leerLinks(filename);
// }
links::links(nodes* dbNode) : dbNode(dbNode){
    (*this).filename = "links.csv";
    // (*this).dbNode = dbNode;
    leerLinks(filename);
}

void links::leerLinks(std::string filename){
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
        node* node1 = dbNode->extracionNode(a2);
        node* node2 = dbNode->extracionNode(a3);
        link linkObj = link(a1, node1, node2, a4, a5);
        dbLink.push_back(linkObj);
        node1->agregarLink(linkObj);
        node2->agregarLink(linkObj);
    }
    file.close(); 
}

void links::mostrarLinks(){
    for (int i=0; i <dbLink.size(); i++) {
        dbLink.at(i).mostrarLink();
    }
}
link links::extraccionLink(int index) {
    link linkExtraido = dbLink.at(index);
    return linkExtraido;
}
