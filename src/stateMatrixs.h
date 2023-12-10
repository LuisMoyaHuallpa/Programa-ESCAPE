#ifndef stateMatrixs_h
#define stateMatrixs_h

#include "stateMatrix.h"
#include <vector>
#include <sstream>  
#include "nodes.h"
#include <iomanip>

class stateMatrixs {
private:
    std::vector<stateMatrix> dbStateMatrixs;
    nodes* dbNode;

public:
    static const std::string stateMatrixFile;
    stateMatrixs();
    stateMatrixs(nodes* dbNode);

    // void enviarDataNode(stateMatrix stateMatrixElement);
    std::string encontrarUltimoFile();
    std::string crearFileExport();
    void leerDbStateMatrixs(std::string filename);
    void imprimirDbStateMatrixs();
    
    
};

#endif
