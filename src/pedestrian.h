// MIT License
// Copyright (c) 2025 
// Luis Angel Moya Huallpa, Julio Cesar Ramirez Paredes, Erick Mas, Shunichi Koshimura
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
#include "io.h"
#include "sarsa.h"
// #include "subLink.h"
#include "stateMatrix.h"
#include "subLink.h"
#include "vector2D.h"
#include "velocidad.h"
#include "tiempo.h"

class node;
class link;
enum estado { pasivo, evacuando, evacuado, muerto };

class pedestrian {
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idPedestrian        |-->| ID DE LA INTERSECCION
    // edad                |-->| COORDENADA X DEL NODO 
    // gender              |-->| COORDENADA Y DEL NODO
    // hhType              |-->| 
    // hhId                |-->| 
    // position            |-->| POSICION DE LA PERSONA
    // nodeArranque        |-->| INTERSECCION DE INICIO AL INICIAR SIMULACION  
    // tiempoInicial       |-->| TIEMPO DE INICIO PARA QUE LA PERSONA EMPIEZE A CAMINAR 
    // position            |-->| POSICION DE LA PERSONA 
    // nodeInicio          |-->| INTERSECCION DE UNA CALLE 
    // nodeFinal           |-->| OTRA INTERSECCION DE LA MISMA CALLE
    // nodeInicioAnterior  |-->| INTERSECCION INICIAL DE LA CALLE ANTERIOR
    // linkActual          |-->| CALLE POR DONDE ESTA ACTUALMENTE LA PERSONA 
    // linkPasado          |-->| CALLE ANTERIOR POR DONDE PASO
    // direccionPedestrian |-->| DIRECCION DE LA PERSONA
    // velocidad           |-->| VELOCIDAD DE LA PERSONA
    // evacuado            |-->| LA PERSONA QUE LLEGO A UN PUNTO DE EVACUACION
    // retorno             |-->| PODRIA COMO LA GANANCIA TOTAL 
    // tiempoProximaInterseccion |-->| TIEMPO DE PROXIMA LLEGADA A UN NODO

    // stateMatrixCurrent  |-->| PUNTERO A STATEMATRIX EXPERIMENTANDO 
    // stateMatrixPrevious |-->| PUNTERO A STATEMATRIX EXPERIMENTANDO ANTERIORMENTE
    // QCurrent            |-->| PUNTERO A QCURRENTE 
    // QPrevious           |-->| PUNTERO A QPREVIOUS 
    // linkCurrent         |-->| PUNTERO A CALLE ACTUAL
    // linkPrevious         |-->| PUNTERO A CALLE PASADA 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
    const int idPedestrian;
    const int edad;
    const int gender;
    const int hhType;
    const int hhId;
    const node* nodeArranque;
    const int tiempoInicial;
    vector2D position;
    node* nodeInicioPtr;
    node* nodeFinalPtr;
    vector2D direccionPedestrian;
    velocidad velocidadPedestrian;
    estado estadoPedestrian;
    int reward;
    int tiempoAnteriorInterseccion;
    bool interseccion;
    stateMatrix* stateMatrixCurrentPtr;
    Q* QCurrentPtr;
    Q* QPreviousPtr;
    link* linkCurrentPtr;
    int idEndSublink;

public:

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static int contador;
    static const int meanRayleigh;
    const static int surviveReward;
    const static int deadReward;
    const static int stepReward;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    pedestrian(const int edad, const int gender, const int hhType, const int hhId, node* nodeArranque);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setPosition(vector2D position);
    void setNodeInicio(node* nodeInicio);
    void setNodeFinal(node* nodeFinal);
    void setNodeInicioAnterior(node* nodeInicioAnterior);
    void setLinkActual(link* linkActual);
    void setDireccionPedestrian(vector2D direccionPedestrian);
    void setVelocidadPedestrian(double velocidadPedestrian);
    void setEstadoPedestrian(estado estadoPedestrian);
    void setReward(int reward);
    void setInterseccion(bool interseccion);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const int getIdPedestrian() const;
    const int getEdad() const;
    const int getGender() const;
    const int getHHType() const;
    const int getHHId() const;
    const node* getNodeArranque() const;
    const int getTiempoInicial() const;
    vector2D getPosition() const;
    node* getNodeInicio() const;
    node* getNodeFinal() const;
    vector2D getDireccionPedestrian() const;
    velocidad &getVelocidadPedestrian();
    estado& getEstadoPedestrian();
    int getReward() const;
    int getTiempoAnteriorInterseccion() const;
    bool getInterseccion() const;
    stateMatrix* getStateMatrixCurrent() const;
    double* getQCurrent() const;
    double* getQPrevious() const;
    link* getLinkCurrent() const;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    bool operator==(const pedestrian& pedestrian2) const;
    void modelamientoPedestrian();
    void caminar();
    link* eleccionGeneralLink() const;
    link* eleccionRandomLink() const;
    link* eleccionSarsaLink() const;
    bool verificarNodoLLeno() const;
    bool verificarEndLink() const;
    int calcularIdEndSublink() const;
    double calcularIdSublink();
    int calcularReward() const;
    int calcularTiempoDesplazamiento() const;
    void contarPedestrianInSublink();
    void calcularDensityInSublink();
    void eleccionDosCallesContinuas();
    void calcularDireccionPedestrian();
    vector2D calcularSignoDireccion();
    int calcularSignoNumero(double numero);
    void reiniciar();
    void mostrarMovimientoPedestrian() const;
    void mostrarPedestrian() const;
    void imprimirPedestrianPosition(fileIO* file) const;
    void imprimirPedestrianVelocity(fileIO* file) const;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static metods
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static const double calcularScaleRayleigh();
    static double calcularRayleighDistribution(const double sigma);
    static void plotearPedestrians(fileIO* const file);
    
    // static double calcularOptimalChoiceRate();
};
#endif
