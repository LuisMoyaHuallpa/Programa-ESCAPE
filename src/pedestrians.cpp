#include "pedestrians.h"
#include "nodes.h"

pedestrians::pedestrians() {
    (*this).filename = "population.csv";
    leerPedestrians(filename);
}
pedestrians::pedestrians(nodes* dbNode) {
    (*this).filename = "population.csv";
    (*this).dbNode=dbNode;
    leerPedestrians(filename);
}
pedestrians::pedestrians(std::string filename) {
    leerPedestrians(filename);  
}

void pedestrians::leerPedestrians(std::string filename){
    std::fstream file;
    file.open(filename, std::ios::in);
    
    if (file.fail()) {
        std::cout << "Error opening the file " <<filename << std::endl;
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
        node* nearNode = dbNode->extracionNode(a5);
        dbPedestrians.push_back(pedestrian(a1, a2, a3, a4, nearNode));
        }
    file.close(); 
}
void pedestrians::mostrarPedestrians(){
    for (int i=0; i < dbPedestrians.size(); i++) {
        dbPedestrians.at(i).mostrarPedestrian();
    }
}
void pedestrians::calcularNumberPedestrian(){
    numberPedestrian =dbPedestrians.size();
}
void pedestrians::caminarPedestrians() {
    for (int i = 0; i < dbPedestrians.size(); i++) {
        dbPedestrians.at(i).caminar();
        dbPedestrians.at(i).updateLinkParameter();
        // dbPedestrians.at(i).verificarEndLink();
    }
}
