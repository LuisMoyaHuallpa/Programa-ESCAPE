// MIT License
// Copyright (c) 2025 
// Luis Angel Moya Huallpa, Julio Cesar Ramirez Paredes, Erick Mas, Shunichi Koshimura
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "links.h"
#include "dictionary.h"
#include "nodes.h"
#include "pedestrians.h"
#include "tiempo.h"
#include <vector>
#include "pedestrian.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
links* links::linksInstance = nullptr;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
links::links() {
    (*this).fileName = std::get<std::string>(dictionary::get()->lookupDefault("linksFile"));
    leerLinks(fileName);
}

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
        // añadir link en cada nodo
        node1->addLink(dbLinkTotal.back().get());
        node2->addLink(dbLinkTotal.back().get());
    }
    file.close(); 
}
void links::contarPedestrians() {
    /* calcula el nivel de densidad en las calles*/
    if(tiempo::get()->verificarPedestrianCountPeriod()){
        // recorre todas las calles
        for (auto it = dbLinkTotal.begin(); it != dbLinkTotal.end(); ++it) {
            // calcula el nivel de densidad de todas las calles con los datos anterios
            it->get()->calcularDensityGeneral();
        }
    }
}
void links::resetSublinks() {
    /* reinicia valores de conteo de sublink*/
    // verifica cada cuando esta contando
    if (tiempo::get()->getPedestrianCountPeriod()) {
        // recorre todos las calles
        for (auto it = dbLinkTotal.begin(); it != dbLinkTotal.end(); ++it) {
            // recorre cada sublink y lo reincia
            for (auto y = it->get()->getSubdiviones().begin(); y != it->get()->getSubdiviones().end(); ++y) {
                // solo borra si no esta vacia
                if (!y->getPedestriansInSublink().empty()) {
                    y->getPedestriansInSublink().clear();
                }
            }
        }    
    }
}
void links::resetLinks() {
    /* reinicia los valores de los pedestriansLink*/  
    for (auto it = dbLinkTotal.begin(); it != dbLinkTotal.end(); ++it) {
        it->get()->reiniciarSubdivisiones();
    }
}
void links::mostrarDbLinksTotal(){
    for (int i = 0; i < dbLinkTotal.size(); i++) {
        dbLinkTotal.at(i)->mostrarLink();
    }
}
void links::mostrarSublink() {
    for (int i = 0; i < dbLinkTotal.size(); i++) {
        dbLinkTotal.at(i)->mostrarSubdivisiones();
        std::cout << std::endl;
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
