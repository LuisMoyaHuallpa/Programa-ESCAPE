#ifndef pedestrian_h
#define pedestrian_h

#include "node.h"
#include "link.h"
#include "vector2D.h"


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
    link* linkActual;
    vector2D velocidad;

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

    int getIdPedestrian() const;
    int getEdad() const;
    int getGender();
    int getHHType() const;
    int getHHId() const;
    node* getNodeInicio() const;

    void mostrarPedestrian();
    void posibleCaminos();
    void caminar();
    
};

#endif
