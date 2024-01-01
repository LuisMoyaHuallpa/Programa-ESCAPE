#include "links.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<link> links::dbLinkTotal;
// #include "pedestrian.h"

// nodes links::listaNode;
// void links::setListaNode(const nodes& dbnode) {
//     listaNode = dbnode;
// }

// links::links(std::string filename) : dbNode(){
//     leerLinks(filename);
// }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
links::links(){
    (*this).fileName = "links.csv";
    leerLinks(fileName);
}

// links::links(nodes* dbNode) {
//     (*this).dbNode = dbNode;
//     (*this).fileName = "links.csv";
//     leerLinks(fileName);
//     creacionLinkConnections();
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string links::getFileName() {
    return fileName;  
}
std::vector<link> links::getDbLink() {
    return dbLink;
}
// nodes* links::getDbNode() {
//     return dbNode;  
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void links::leerLinks(std::string fileName){
    // Lectura de archivo de links
    std::fstream file;
    file.open(fileName, std::ios::in);
    
    if (file.fail()) {
        std::cout << "Error opening the file " << fileName << std::endl;
        exit(1);
    }
    // Variables de una fila del archivo nodos, que seria un solo node
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idLink                |-->| IDLINK
    // idNode1               |-->| POSICION X
    // idNode2               |-->| POSICION Y
    // lengthLink            |-->| NODE DE EVACUACION, SI ES 1
    // withLink              |-->| 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string a1_str, a2_str, a3_str, a4_str, a5_str;
    std::string idLink_str, idNode1_str, idNode2_str, lengthLink_str, widthLink_str;
    std::string line;
    link linkObj1;
    // Lectura de archivo de nodos
    while (std::getline(file, line)) {
        // Si el archivo tiene comentarios con #, no leerlos.
        if (line[0] == '#') {
            continue;
        }
        std::istringstream iss(line);

        std::getline(iss, idLink_str, ',');
        std::getline(iss, idNode1_str, ',');
        std::getline(iss, idNode2_str, ',');
        std::getline(iss, lengthLink_str, ',');
        std::getline(iss, widthLink_str, '\n');

        int idLink= std::stoi(idLink_str);
        int idNode1= std::stoi(idNode1_str);
        int idNode2 = std::stoi(idNode2_str);
        int lengthLink = std::stoi(lengthLink_str);
        int widthLink = std::stoi(widthLink_str);
        linkObj1.setIdLink(idLink);
        linkObj1 = link(idLink, idNode1, idNode2, lengthLink, widthLink);
        // dbLink.push_back(linkObj1);
        links::dbLinkTotal.push_back(linkObj1);
        nodes::dbNodeTotal.at(idNode1).addIdLinkConnection(idLink);
        nodes::dbNodeTotal.at(idNode2).addIdLinkConnection(idLink);
        // dbNode->getDbNode().at(idNode1).addIdLinkConnection(idLink);
        // dbNode->getDbNode().at(idNode2).addIdLinkConnection(idLink);

        // pedestrian::dbNode->getDbNode().at(idNode1).addIdLinkConnection(idLink);

        // pedestrian::dbNode.getDbNode().at(idNode2).addIdLinkConnection(idLink);
        // linkObj1.mostrarLink();
    }
    file.close(); 
}

void links::mostrarLinks(){
    for (int i=0; i <dbLinkTotal.size(); i++) {
        // dbLink.at(i).mostrarLink();
        dbLinkTotal.at(i).mostrarSubLinks();
    }
}
void links::imprimirLinks() {
    std::fstream file;
    std::string folderName = "meshLink";
    file.open(folderName + "/poliLinks",std::ios::out);
    for (int i=0; i < dbLink.size(); i++) {
        // dbLink.at(i).imprimirLink(file);

    }
}

void links::creacionLinkConnections() {
    for (int i = 0; i < dbLink.size(); i++) {
        dbLink.at(i).creacionLinkConnection();
    }
}
