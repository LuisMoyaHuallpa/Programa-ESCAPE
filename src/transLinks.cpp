#include "transLinks.h"
#include "links.h"
#include "transLink.h"
#include <iostream>
#include "iomanip"

links transLinks::listaLink;
void transLinks::setListaLink(const links &dblink) {
    listaLink = dblink;  
}
transLinks::transLinks() {
    (*this).filename = "transitionsdb.csv";
    leerTransLinks(filename);
}
transLinks::transLinks(std::string filename) {
    leerTransLinks(filename);
}

void transLinks::leerTransLinks(std::string filename) {
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
        std::string a1_str, a2_str, id_str;

        std::getline(iss, a1_str, ',');
        std::getline(iss, a2_str, ',');
        int a1 = std::stoi(a1_str);
        int a2 = std::stoi(a2_str);

        std::vector<int> ids;
        for (int i = 0; i < a2; i++) {
            std::getline(iss, id_str, ',');
            int id = std::stoi(id_str);
            ids.push_back(id);
        }
        
        dbTransLink.push_back(transLink(a1, a2, ids));
        }
    file.close(); 
}
void transLinks::mostrarTransLinks() {
    std::cout <<"hola";
    for (int i = 0; i < dbTransLink.size(); i++) {
        std::cout << std::setw(3) <<dbTransLink.at(i).getMainNode().getId() << ' ';
        std::cout << "link: ";
        for (int j = 0; j < dbTransLink.at(i).getLinkConnection().size(); j++) {
            std::cout << dbTransLink.at(i).getLinkConnection().at(j).getId() << ' ';
            std::cout << dbTransLink.at(i).getLinkConnection().at(j).getNode1().getCoordX() << ' ';

        }
        std::cout << std::endl;
    }
}
