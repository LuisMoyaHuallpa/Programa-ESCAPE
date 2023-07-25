#include "dbLink.h"
#include "dbNode.h"

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

using std::endl;
dbNode dbLink::listaNode;

dbLink::dbLink(){
    (*this).filename = "links.csv";
    leerDbLink(filename);

}
dbLink::dbLink(std::string filename){
    leerDbLink(filename);
}

void dbLink::setListaNode(const dbNode& dbnode) {
    listaNode = dbnode;
}
void dbLink::leerDbLink(std::string filename){

    std::fstream fileLink;
    fileLink.open(filename, std::ios::in);

   if (fileLink.fail()) {
        std::cout << "Error opening the file links.csv" << std::endl;
        exit(1);
    }

   int id, n1, n2, l, w;
    std::string line;

    while (std::getline(fileLink, line)) {
        
        std::istringstream iss(line);
        std::string id_str, n1_str, n2_str, l_str, w_str;

        std::getline(iss, id_str, ',');
        std::getline(iss, n1_str, ',');
        std::getline(iss, n2_str, ',');
        std::getline(iss, l_str, ',');
        std::getline(iss, w_str, '\n');

        id = std::stoi(id_str);
        n1= std::stoi(n1_str);
        n2 = std::stoi(n2_str);
        l = std::stoi(l_str);
        w = std::stoi(w_str);
        links.push_back(link(id, n1, n2, l, w));
        }
    
    fileLink.close(); 


}

void dbLink::mostrarLinks(){

    for (int i=0; i <links.size(); i++) {

        std::cout << links.at(i).getId() << ' ';
        std::cout << links.at(i).getNode1().getId() << ' ';
        std::cout << links.at(i).getNode2().getId() << ' ';
        std::cout << endl;
    }
}
