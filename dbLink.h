#ifndef dbLink_h
#define dbLink_h


#include "link.h"
#include "dbNode.h"
#include <string>
#include <vector>


class dbLink {

private:
    std::string filename;
    std::vector<link> links;
    
public:
    static dbNode listaNode;
    static void setListaNode(const dbNode& dbnode);

    /* constructor */
    dbLink();
    dbLink(std::string filename);
    
    
    /* metodos */
    void leerDbLink(std::string filename);
    void mostrarLinks();
    link extraccionLink(int index);
    // void buscarNode(int id);

};
#endif
