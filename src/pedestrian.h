#ifndef pedestrian_h
#define pedestrian_h

#include "node.h"
#include "links.h"
#include "tiempo.h"
#include "vector2D.h"
#include "vector2DVelocidad.h"
#include <fstream>
#include <iostream>
#include "subLink.h"
#include <algorithm>
#include <cmath>
#include <math.h>
#include <random>
#include <iomanip>
#include <vector>
#include "sarsa.h"

class pedestrian {
private:
    int idPedestrian;
    int gender;
    int edad;
    int hhType;
    int hhId;

    int coordX;
    int coordY;
    vector2D position;
    node* nodeInicio;
    node* nodeFinal;
    // node* nodeAnterior;
    link* linkActual;
    link* linkPasado;
    stateActionQ* qStateAction;
    vector2D orientacion;
    vector2D orientacionLinkPasado;
    vector2DVelocidad velocidad;
    int tiempoInicial;
    int tiempoFinal;
    bool empezoCaminar;
    bool primerTiempo;
    bool saltoLink;
    int retorno;
    bool evacuado;
    sarsa sarsaAlgorithm;

public:
    static int contador;
    static const int surviveReward;
    static const int deadReward;
    static const int stepReward;
   
    pedestrian();
    pedestrian(int edad, int gender, int hhType, int hhId, node* nodeInicio);

    /* setters */
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
    void setqStateAction(stateActionQ* qStateAction);
    void setOrientacion(vector2D orientacion);
    void setOrientacionLinkPasado(vector2D orientacionLinkPasado);
    void setVelocidad(vector2DVelocidad velocidad);
    void setTiempoInicial(int tiempoInicial);
    void setTiempoFinal(int tiempoFinal);
    void setEmpezoCaminar(bool empezoCaminar);
    void setPrimerTiempo(bool primerTiempo);
    void setSaltoLink(bool saltoLink);
    void setRetorno(int retorno);
    void setEvacuado(bool evacuado);

    int getIdPedestrian() const;
    int getEdad() const;
    int getGender();
    int getHHType() const;
    int getHHId() const;
    node* getNodeInicio() const;
    node* getNodeFinal();
    // node* getNodeAnterior();
    vector2D getPosition();
    vector2D getOrientacion();
    vector2D getOrientacionLinkPasado();
    link* getLinkActual();
    link* getLinkPasado();
    stateActionQ* getqStateAction();
    vector2DVelocidad getVelocidad();
    int getTiempoInicial();
    int getTiempoFinal();
    bool getEmpezoCaminar();
    bool getPrimerTiempo();
    bool getSaltoLink();
    int getRetorno();
    bool getEvacuado();

    void mostrarPedestrian();
    void imprimirPedestrianPosition(std::fstream& file);
    void imprimirPedestrianVelocity(std::fstream& file);
    void caminar();
    void eleccionRandomLinkActual();
    int iEleccionRandomLinkActual();
    void updateLinkActual(int iLinkConnection);
    void updateStateAction(int iLinkConnection);
    void updateParametrosPeaton();
    void eleccionProbalistica();
    bool verificarEndLink();
    bool verificarEndLink1();
    void calcularNodeFinal();
    void updateLinkParameter();
    // void updateLinkParameter(sarsa* sarsaAlgorithm);
    void updateCalle();
    void calcularOrientacion();
    void calcularRetorno();
    void verificarPedestrianEvacuation();
    void contarPedestrainSubdivision();
    bool verificarDirectionLink();
    void encontrarPrimerTiempo();
    bool verificarSaltoLink();
    void correctionPosition();
    void algoritmoSarsa();
    std::vector<stateActionQ>::iterator agregarObtenerqLista(node* nodeDeBusqueda,stateActionQ qBuscando);
    void buscarQ(bool verificarQExistente, stateActionQ* qElemento);
    std::vector<int> calcularLevelDensityLinks();
    void inicializarq();
    void crearqState(node* nodeActual);
    
};

#endif
