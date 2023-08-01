#ifndef links_h
#define links_h

#include "link.h"
#include "nodes.h"
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>


class links {

private:
    std::string filename;
    std::vector<link> dbLink;
    nodes *dbNode;
    
public:
    // static nodes listaNode;
    // static void setListaNode(const nodes& dbnode);

    /* constructor */
    // links();
    // links(std::string filename);
    links(nodes* dbNode);
    
    
    
    /* metodos */
    void leerLinks(std::string filename);
    void mostrarLinks();
    link extraccionLink(int index);
    // void buscarNode(int id);

};
#endif
