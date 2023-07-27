#include "dbPedestrian.h"
#include <iostream>
#include <ostream>

dbPedestrian::dbPedestrian() {
    std::cout << "hola";
    (*this).filename = "population.csv";
    leerDbPedestrian(filename);
}
dbPedestrian::dbPedestrian(std::string filename) {
    leerDbPedestrian(filename);  
}
void dbPedestrian::leerDbPedestrian(std::string filename){
    std::fstream file;
    file.open(filename, std::ios::in);
    
    std::cout << "hola";
    if (file.fail()) {
        std::cout << "Error opening the file " <<filename << std::endl;
        exit(1);
    }
    
    std::string line;
    while (std::getline(file, line)) {
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
        pedestrians.push_back(pedestrian(a1, a2, a3, a4, a5));
        }
    
    file.close(); 
}

void dbPedestrian::mostrarDbPedestrian(){

    for (int i=0; i <pedestrians.size(); i++) {

        std::cout << pedestrians.at(i).getId() << ' ';
        std::cout << pedestrians.at(i).getEdad() << ' ';
        std::cout << pedestrians.at(i).getNearNode().getId() << ' ';
        std::cout << pedestrians.at(i).getNearNode().getCoordX() << ' ';
        std::cout << pedestrians.at(i).getNearNode().getCoordY() << ' ';
        std::cout << std::endl;
    }
}

void dbPedestrian::calcularNumberPedestrian(){
    numberPedestrian =pedestrians.size();
}
