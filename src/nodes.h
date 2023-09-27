#ifndef nodes_h
#define nodes_h

#include "node.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>



class nodes{

private:
    std::string filename;
    std::vector<node*> dbnodes;
public:
    // constructor
    nodes();
    nodes(std::string filename);


    // metodos
    void leerNodes(std::string filename);
    void usarlink();
    node* extracionNode(int index);
    void imprimirNodes();
    
};
#endif
