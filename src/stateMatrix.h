#ifndef stateMatrix_h
#define stateMatrix_h
/*---------------------------------------------------------------------------*\
Una fila de archivo de entrada o salida.
\*---------------------------------------------------------------------------*/

#include "state.h"
#include "action.h"
#include <fstream>
#include <vector>
#include "node.h"

class stateMatrix {
private:
    int idNode;
    state stateValue;
    std::vector<double> QVector;
    std::vector<int> otrosVector;

public:
    stateMatrix();
    stateMatrix(int idNode, state stateValue, std::vector<double> QVector, std::vector<int> otrosValue);

    // void leerStateMatrix(std::string filename);
    // void imprimirStateMatrix();
    // Setters
    void setIdNode(int idNode);
    void setStateValue(state stateValue);
    void setQVector(std::vector<double> actionVector);
    void setOtrosVector(std::vector<int> otrosVector);

    int getIdNode();
    state getStateValue();
    std::vector<double> getQVector();
    std::vector<int> getotrosVector();

    void enviarDataNode(node* nodeAGuardar);
    void imprimirStateMatrix(std::fstream& file);

};
#endif
