#ifndef tiempo_h
#define tiempo_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header generales
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <sys/stat.h> 
#include <iostream>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "dictionary.h"
#include "chrono"

class tiempo {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // valorTiempo           |-->| TIEMPO DE SIMULACION 
    // deltaT                |-->| TIEMPO DE PASO DE SIMULACION  
    // endTime               |-->| TIEMPO DE TERMINO DE LA SIMULACION
    // graphicPrintoutPeriod |-->| PERIODO DE TIEMPO PARA IMPRIMIR DATOS
    // startNumberSimulation |-->| INICIO DEL NUMERO DE SIMULACION
    // iNumberSimulation     |-->| NUMERO DE SIMULACION ACTUAL
    // endNumberSimulation   |-->| FIN DEL NUMERO DE SIMULACION
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int valorTiempo;
    int deltaT;
    int endTime;
    int graphicPrintoutPeriod;
    int startNumberSimulation;
    int iNumberSimulation;
    int endNumberSimulation;
    std::chrono::high_resolution_clock::time_point startTimeSimulation;
    std::chrono::high_resolution_clock::time_point endTimeSimulation;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    tiempo();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static tiempo* tiempoInstance;

public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static int deltaTiempo;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setValorTiempo(int valorTiempo);
    void setDeltaT(int deltaT);
    void setGraphicPrintoutPeriod(int graphicPrintoutPeriod);
    void setStartNumberSimulation(int startNumberSimulation);
    void setINumberSimulation(int iNumberSimulation);
    void setEndNumberSimulation(int endNumberSimulation);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getValorTiempo();
    int getDeltaT();
    int getGraphicPrintoutPeriod();
    int getStartNumberSimulation();
    int getINumberSimulation();
    int getEndNumberSimulation();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static tiempo* get();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    tiempo& operator++(int);
    void aumentarTiempo();
    void aumentarINumberSimulation();
    void inicializarNumberSimulation();
    void extractINumberSimulation();
    bool running();
    void mostrarTiempo();
    void mostrarIResultadosSimulacion();
    void crearCarpetaTiempo();
    bool verificarGraphicPrintout(); 
    
};

#endif

