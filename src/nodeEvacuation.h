#ifndef nodeEvacuation_h
#define nodeEvacuation_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "pedestrian.h"
#include "vector2D.h"
#include "io.h"
#include <vector>
#include "node.h"

// forward declaration
class pedestrian;

class nodeEvacuation: public node {
    
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // maxPersonasEvacuadas   |-->| ID DE LA INTERSECCION
    // personasEvacuadasPtr   |-->| LISTA DE PUNTEROS DE PERSONAS EVACUADAS
    // lleno                  |-->| NODO EVACUACION AL MAXIMO DE SU CAPACIDAD 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int maxPersonasEvacuadas;
    std::vector<pedestrian*> personasEvacuadasPtr;
    bool lleno;

public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static int totalPersonasEvacuadas;
    static int maxPersonasEvacuadasGlobal;
    static bool evacuacionTotal;

    std::string getNodeType() override;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    nodeEvacuation();
    nodeEvacuation(const int id, const vector2D coordenada);
    nodeEvacuation(const int id, const vector2D coordenada, const int maxPersonasEvacuadas);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getMaxPersonasEvacuadas() const;
    std::vector<pedestrian*> getPersonasEvacuadasPtr() const;
    bool getLleno() const;
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int static getTotalPersonasEvacuadas();
    static bool verificarEvacuacionTotal();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void reiniciar();
    bool verificarLLeno() const;
    estado estadoPedestrianEnNodo() const override;
    bool verificarNodoEvacuation() const override;
    std::vector<int> stateObservado() const override;
    void contabilizarPersona(pedestrian* const persona);
    void imprimirPersonasEvacuadas(std::fstream* file);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static metods
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void static sumarTotalPersonasEvacuadas();
    void static imprimirNodeEvacuation(fileIO* const file);
    void static imprimirTotalPersonasEvacuadas(fileIO* const file);
    void static plotearTotalPersonasEvacuadasXSimulacion();
    void static imprimirVariableTotalPersonasEvacuadas(fileIO* const file);


};

#endif
