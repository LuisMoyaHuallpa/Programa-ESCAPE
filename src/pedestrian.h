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
#include <random>
#include <iomanip>
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "sarsa.h"
// #include "subLink.h"
#include "vector2D.h"
#include "vector2DVelocidad.h"
#include "node.h"
#include "link.h"
#include "tiempo.h"

class pedestrian {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idPedestrian     |-->| ID DE LA INTERSECCION
    // edad             |-->| COORDENADA X DEL NODO 
    // gender           |-->| COORDENADA Y DEL NODO
    // hhType           |-->| 
    // hhId             |-->| 
    // position         |-->| POSICION DE LA PERSONA
    // nodeInicio       |-->| INTERSECCION DE UNA CALLE 
    // nodeFinal        |-->| OTRA INTERSECCION DE LA MISMA CALLE
    // linkActual       |-->| CALLE POR DONDE ESTA ACTUALMENTE LA PERSONA 
    // linkPasado       |-->| CALLE ANTERIOR POR DONDE PASO
    // velocidad        |-->| VELOCIDAD DE LA PERSONA
    // tiempoInicial    |-->| TIEMPO DE INICIO PARA QUE LA PERSONA EMPIEZE A CAMINAR 
    // evacuado         |-->| LA PERSONA QUE LLEGO A UN PUNTO DE EVACUACION
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    int idPedestrian;
    int edad;
    int gender;
    int hhType;
    int hhId;
    vector2D position;
    node* nodeInicio;
    node* nodeFinal;
    // node* nodeAnterior;
    link* linkActual;
    link* linkPasado;

    vector2DVelocidad velocidad;
    int tiempoInicial;
    // stateActionQ* qStateAction;
    // vector2D orientacion;
    // vector2D orientacionLinkPasado;
    // int tiempoFinal;
    // bool empezoCaminar;
    // bool primerTiempo;
    // bool saltoLink;
    // int retorno;
    bool evacuado;
    // sarsa sarsaAlgorithm;

public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static int contador;
    const static int surviveReward;
    const static int deadReward;
    const static int stepReward;
    static std::vector<node> dbNodeTotal;
    static std::vector<link> dbLinkTotal;
    static std::vector<pedestrian> dbPedestrianTotal;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    pedestrian();
    pedestrian(int edad, int gender, int hhType, int hhId, node* nodeInicio);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setIdPedestrian(int idPedestrian);
    void setEdad(int edad);
    void setGender(int gender);
    void setHHType(int hhType);
    void setHHId(int hhId);
    void setNodeInicio(node* nodeInicio);
    void setNodeFinal(node* nodeFinal);
    // void setNodeAnterior(node* nodeAnterior);
    void setPosition(vector2D position);
    void setLinkActual(link* linkActual);
    void setLinkPasado(link* linkPasado);
    // void setqStateAction(stateActionQ* qStateAction);
    // void setOrientacion(vector2D orientacion);
    // void setOrientacionLinkPasado(vector2D orientacionLinkPasado);
    void setVelocidad(vector2DVelocidad velocidad);
    void setTiempoInicial(int tiempoInicial);
    // void setTiempoFinal(int tiempoFinal);
    // void setEmpezoCaminar(bool empezoCaminar);
    // void setPrimerTiempo(bool primerTiempo);
    // void setSaltoLink(bool saltoLink);
    // void setRetorno(int retorno);
    void setEvacuado(bool evacuado);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getIdPedestrian() const;
    int getEdad() const;
    int getGender();
    int getHHType() const;
    int getHHId() const;
    node* getNodeInicio() const;
    node* getNodeFinal();
    // node* getNodeAnterior();
    vector2D getPosition();
    // vector2D getOrientacion();
    // vector2D getOrientacionLinkPasado();
    link* getLinkActual();
    link* getLinkPasado();
    // stateActionQ* getqStateAction();
    vector2DVelocidad getVelocidad();
    int getTiempoInicial();
    // int getTiempoFinal();
    // bool getEmpezoCaminar();
    // bool getPrimerTiempo();
    // bool getSaltoLink();
    // int getRetorno();
    bool getEvacuado();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static getters
    static std::vector<node> getDbNodeTotal();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void imprimirPedestrianPosition(std::fstream& file);
    // void imprimirPedestrianVelocity(std::fstream& file);
    void caminar();
    void eleccionRandomLinkActual();
    // int iEleccionRandomLinkActual();
    // void updateLinkActual(int iLinkConnection);
    // void updateStateAction(int iLinkConnection);
    // void updateParametrosPeaton();
    // void eleccionProbalistica();
    // bool verificarEndLink();
    // bool verificarEndLink1();
   void calcularNodeFinal();
    // void updateLinkParameter();
    // // void updateLinkParameter(sarsa* sarsaAlgorithm);
    // void updateCalle();
    // void calcularOrientacion();
    // void calcularRetorno();
    // void verificarPedestrianEvacuation();
    // void contarPedestrainSubdivision();
    // bool verificarDirectionLink();
    // void encontrarPrimerTiempo();
    // bool verificarSaltoLink();
    void correctionPosition();
    // void algoritmoSarsa();
    // std::vector<stateActionQ>::iterator agregarObtenerqLista(node* nodeDeBusqueda,stateActionQ qBuscando);
    // voidbuscarQ(bool verificarQExistente, stateActionQ* qElemento);
    // std::vector<int> calcularLevelDensityLinks();
    // void inicializarq();
    // void crearqState(node* nodeActual);
    void mostrarMovimientoPedestrian();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static metods
    static void leerPedestrians(std::string fileName);
    static void tiempoInicioDistribution();
    static void modelamientoPedestrians(int valorTiempo);
    static void mostrarDbPedestrianTotal();
    
};
#endif
