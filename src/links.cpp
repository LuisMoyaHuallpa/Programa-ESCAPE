#include "links.h"
#include "dictionary.h"
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
links* links::linksInstance = nullptr;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
links::links() {
    // (*this).fileName = dictionary::controlDict["linksFile"];
    (*this).fileName = dictionary::get()->lookupDefault("linksFile");
    leerLinks(fileName);
}

// nodes links::listaNode;
// void links::setListaNode(const nodes& dbnode) {
//     listaNode = dbnode;
// }

// links::links(std::string filename) : dbNode(){
//     leerLinks(filename);
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string links::getFileName() {
    return fileName;  
}
std::vector<std::shared_ptr<link>> links::getDbLinkTotal() {
    return dbLinkTotal;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
links* links::get() {
    /* si aun no existe crea la unica instancia de nodes*/
    if (!linksInstance) {
        linksInstance =  new links();
    }
    return linksInstance;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void links::leerLinks(std::string fileName){
    /* Lectura de archivo de links */
    std::fstream file;
    file.open(fileName, std::ios::in);
    // en caso no exista el archivo link.csv 
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
    // link linkObj1;
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
        // obtiendo los node1 y node2
        node* node1 =nodes::get()->getDbNodeTotal().at(idNode1).get();
        node* node2 =nodes::get()->getDbNodeTotal().at(idNode2).get();
        std::unique_ptr<link> linkNuevo = std::make_unique<link>(idLink, node1, node2, lengthLink, widthLink);
        dbLinkTotal.push_back(std::move(linkNuevo));
        // node1->getIdLinkConnection().push_back(idLink);
        // node2->getIdLinkConnection().push_back(idLink);
        // node1->getLinkConnection().push_back(dbLinkTotal.back().get());
        const_cast<std::vector<link*>&>(node1->getLinkConnection()).push_back(dbLinkTotal.back().get());
        const_cast<std::vector<link*>&>(node2->getLinkConnection()).push_back(dbLinkTotal.back().get());
    }
    file.close(); 
}
void links::calcularDensityLevelLinks() {
    for (int i = 0; i < dbLinkTotal.size(); i++) {
        dbLinkTotal.at(i)->calcularDensity();
        dbLinkTotal.at(i)->calcularDensityLevel();
    }
}
void links::resetSublinks() {
    /* reinicia valores de conteo de sublink*/
    // no hacerlo si estas en la ultima simulaciones, debido a que ya las personas se movieron y no
    // necesitaran esta información
    for (int i = 0; i < dbLinkTotal.size(); i++) {
        dbLinkTotal.at(i)->getPedestriansInSublink().assign(link::numberDivisiones, 0);
    }
}
void links::mostrarLinks(){
    for (int i = 0; i < dbLinkTotal.size(); i++) {
        dbLinkTotal.at(i)->mostrarLink();
        // dbLinkTotal.at(i).mostrarSubLinks();
    }
}
void links::mostrarSublink() {
    for (int i = 0; i < dbLinkTotal.size(); i++) {
        dbLinkTotal.at(i)->mostrarSubLink();
    }
}
void links::imprimirMeshLinks() {
    /* imprimi datos para la malla de calles, donde guardo informacion
        de calles y intersecciones.*/
    std::fstream file;
    // nombre de la carpeta
    const char* folderName = "mesh";
    // Crear la carpeta mesh
    mkdir(folderName, S_IRWXU | S_IRWXG | S_IRWXO);
    // abre el archivo en el objeto file
    file.open(std::string(folderName) + "/poliLinks",std::ios::out);
    // recorre todas la base de datos de calle.
    for (int i=0; i < links::dbLinkTotal.size(); i++) {
        dbLinkTotal.at(i)->imprimirLink(file);
    }
}

// void links::creacionLinkConnections() {
//     for (int i = 0; i < dbLink.size(); i++) {
//         dbLink.at(i).creacionLinkConnection();
//     }
// }
