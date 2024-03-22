#ifndef pedestrian_h
#define pedestrian_h

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header generales
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <math.h>
                                                \
#include <memory>
#include <random>
#include <iomanip>
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "sarsa.h"
// #include "subLink.h"
#include "stateMatrix.h"
#include "subLink.h"
#include "vector2D.h"
#include "vector2DVelocidad.h"
#include "node.h"
#include "links.h"
#include "tiempo.h"
#include "nodeEvacution.h"

class pedestrian {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idPedestrian        |-->| ID DE LA INTERSECCION
    // edad                |-->| COORDENADA X DEL NODO 
    // gender              |-->| COORDENADA Y DEL NODO
    // hhType              |-->| 
    // hhId                |-->| 
    // position            |-->| POSICION DE LA PERSONA
    // nodeArranque        |-->| INTERSECCION DE INICIO AL INICIAR SIMULACION  
    // nodeInicio          |-->| INTERSECCION DE UNA CALLE 
    // nodeFinal           |-->| OTRA INTERSECCION DE LA MISMA CALLE
    // nodeInicioAnterior  |-->| INTERSECCION INICIAL DE LA CALLE ANTERIOR
    // linkActual          |-->| CALLE POR DONDE ESTA ACTUALMENTE LA PERSONA 
    // linkPasado          |-->| CALLE ANTERIOR POR DONDE PASO
    // direccionPedestrian |-->| CALLE ANTERIOR POR DONDE PASO
    // velocidad           |-->| VELOCIDAD DE LA PERSONA
    // tiempoInicial       |-->| TIEMPO DE INICIO PARA QUE LA PERSONA EMPIEZE A CAMINAR 
    // stateMatrixActual   |-->| ESTADO Y ACCION ACTUAL QUE EXPERIMENTO LA PERSONA 
    // stateMatrixPasado   |-->| ESTADO Y ACCION PASADO QUE EXPERIMENTO LA PERSONA 
    // evacuado            |-->| LA PERSONA QUE LLEGO A UN PUNTO DE EVACUACION
    // retorno             |-->| PODRIA COMO LA GANANCIA TOTAL 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int idPedestrian;
    const int edad;
    const int gender;
    const int hhType;
    const int hhId;
    vector2D position;
    const node* nodeArranque;
    node* nodeInicio;
    node* nodeFinal;
    node* nodeInicioAnterior;
    link* linkActual;
    link* linkPasado;
    vector2D direccionPedestrian;
    vector2DVelocidad velocidad;
    const int tiempoInicial;
    stateMatrix* stateMatrixActual;
    stateMatrix* stateMatrixPasado;
    bool evacuado;
    int reward;
    sarsa sarsaAlgorithm;

public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static int contador;
    const static int surviveReward;
    const static int deadReward;
    const static int stepReward;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // pedestrian();
    pedestrian(int edad, int gender, int hhType, int hhId, node* nodeArranque);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setPosition(vector2D position);
    void setNodeInicio(node* nodeInicio);
    void setNodeFinal(node* nodeFinal);
    void setNodeInicioAnterior(node* nodeInicioAnterior);
    void setLinkActual(link* linkActual);
    void setLinkPasado(link* linkPasado);
    void setDireccionPedestrian(vector2D direccionPedestrian);
    void setVelocidad(vector2DVelocidad velocidad);
    void setTiempoInicial(int tiempoInicial);
    // void setOrientacionLinkPasado(vector2D orientacionLinkPasado);
    // void setTiempoFinal(int tiempoFinal);
    // void setEmpezoCaminar(bool empezoCaminar);
    // void setPrimerTiempo(bool primerTiempo);
    // void setSaltoLink(bool saltoLink);
    void setEvacuado(bool evacuado);
    void setReward(int reward);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getIdPedestrian() const;
    const int getEdad() const;
    const int getGender();
    const int getHHType() const;
    const int getHHId() const;
    vector2D getPosition();
    const node* getNodeArranque();
    node* getNodeInicio() const;
    node* getNodeFinal();
    node* getNodeInicioAnterior();
    // vector2D getOrientacionLinkPasado();
    link* getLinkActual();
    link* getLinkPasado();
    vector2D getDireccionPedestrian();
    vector2DVelocidad& getVelocidad();
    int getTiempoInicial() const;
    // stateActionQ* getqStateAction();
    // int getTiempoFinal();
    // bool getEmpezoCaminar();
    // bool getPrimerTiempo();
    // bool getSaltoLink();
    bool getEvacuado();
    int getReward();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    bool operator==(pedestrian pedestrian2);
    void caminar();
    double calcularIDoubleSublink();
    void contarPedestrianInSublink();
    void calcularDensityInSublink();
    void cambioCalle();
    void eleccionGeneralLinkActual();
    void eleccionRandomLinkActual();
    void eleccionSarsa();
    void eleccionDosCallesContinuas();
    // int iEleccionRandomLinkActual();
    // void updateLinkActual(int iLinkConnection);
    // void updateStateAction(int iLinkConnection);
    // void updateParametrosPeaton();
    // void eleccionProbalistica();
    bool verificarEndLink();
    // bool verificarEndLink1();
    void calcularNodeFinal();
    void calcularDireccionPedestrian();
    vector2D calcularSignoDireccion();
    int calcularSignoNumero(double numero);
    void calcularReward();
    void verificarPedestrianEvacuation();
    void algoritmoSarsa();
    // std::vector<stateActionQ>::iterator agregarObtenerqLista(node* nodeDeBusqueda,stateActionQ qBuscando);
    // voidbuscarQ(bool verificarQExistente, stateActionQ* qElemento);
    void calcularLevelDensityAtNode();
    // void stateMatrixtoTableAtNode();
    // void crearqState(node* nodeActual);
    void modelamientoPedestrian();
    void mostrarMovimientoPedestrian();
    void imprimirPedestrianPosition(std::fstream& file) const;
    void imprimirPedestrianVelocity(std::fstream& file) const;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static metods
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static double calcularOptimalChoiceRate();
    
};
#endif
