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
    // randomChoiceRate      |-->| COEFICIENTE DE ELECCION ENTRE RANDOM O SARSA 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int valorTiempo;
    const int deltaT;
    const int endTime;
    const int graphicPrintoutPeriod;
    int startNumberSimulation;
    int iNumberSimulation;
    int endNumberSimulation;
    const int pedestrianCountPeriod;
    std::chrono::high_resolution_clock::time_point startTimeSimulation;
    std::chrono::high_resolution_clock::time_point endTimeSimulation;
    double randomChoiceRate;
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
    void setStartNumberSimulation(int startNumberSimulation);
    void setINumberSimulation(int iNumberSimulation);
    void setEndNumberSimulation(int endNumberSimulation);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getValorTiempo() const;
    const int getDeltaT() const;
    const int getGraphicPrintoutPeriod() const;
    int getStartNumberSimulation() const;
    int getINumberSimulation() const;
    int getEndNumberSimulation() const;
    const int getPedestrianCountPeriod() const;
    double getRandomChoiceRate() const;

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
    void calcularRandomChoiceRate();
    bool running();
    void mostrarTiempo() const;
    void mostrarIResultadosSimulacion();
    void crearCarpetaTiempo();
    bool verificarGraphicPrintout(); 
    bool verificarPedestrianCountPeriod(); 
    
};

#endif

