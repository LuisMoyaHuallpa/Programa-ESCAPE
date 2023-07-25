#ifndef dbNode_h
#define dbNode_h

#include "node.h"
#include <string>
#include <vector>

class dbNode{

private:
    std::string filename;
    std::vector<node> nodes;
public:
    // constructor
    dbNode();
    dbNode(std::string filename);


    // metodos
    void leerDbNode(std::string filename);
    void usarlink();
    node extracionNode(int index);
    
};
#endif
