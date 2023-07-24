#include <fstream>
#include <cstdlib>
#include <ostream>
#include <vector>
#include "node.H"
#include <iostream>
#include <fstream>
#include <sstream>


using std::endl; 



int main() {
    std::fstream nodesDbFile;
    nodesDbFile.open("nodes.csv", std::ios::in);

   if (nodesDbFile.fail()) {
        std::cout << "Error opening the file." << std::endl;
        exit(1);
    }

   std::vector<node> nodes;
    int n, x, y, e, r;

    std::string line;

    while (std::getline(nodesDbFile, line)) {
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
    
    nodesDbFile.close(); 

    // for (const auto& nodu : nodes) {
    //     std::cout <<  nodu.getNumber();
    //     std::cout << nodu.getCoordX();
    //     std::cout << nodu.getCoordY();

    //     std::cout << nodu.getEvacuationCode() << endl;
    // }
   
    
}
