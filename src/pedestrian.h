#ifndef pedestrian_h
#define pedestrian_h

#include "node.h"
#include "link.h"
#include "links.h"
#include "tiempo.h"
#include "vector2D.h"
#include "vector2DVelocidad.h"
#include <fstream>
#include <iostream>



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
    link* linkActual;
    vector2D orientacion;
    vector2DVelocidad velocidad;

    int retorno;
    bool evacuado;

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
    void setPosition(vector2D position);
    void setLinkActual(link* linkActual);
    void setOrientacion(vector2D orientacion);
    void setVelocidad(vector2DVelocidad velocidad);
    void setRetorno(int retorno);

    int getIdPedestrian() const;
    int getEdad() const;
    int getGender();
    int getHHType() const;
    int getHHId() const;
    node* getNodeInicio() const;
    node* getNodeFinal();
    vector2D getPosition();
    vector2D getOrientacion();
    link* getLinkActual();
    vector2DVelocidad getVelocidad();
    int getRetorno();

    void mostrarPedestrian();
    void imprimirPedestrian(std::fstream& file);
    void caminar();
    void eleccionRandomLinkActual();
    void calcularVelocidadLink();
    bool verificarEndLink();
    void calcularNodeFinal();
    void updateLinkParameter();
    void calcularOrientacion();
    void calcularRetorno();
    bool verificarEvacuationNode();
};

#endif
