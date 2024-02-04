#ifndef subLink_h
#define subLink_h
/*---------------------------------------------------------------------------*\
    Es la division de una calle o link.
\*---------------------------------------------------------------------------*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header generales
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <vector>
#include <iostream>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "vector2D.h"


class subLink  {

private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // idSubLink                 |-->| 
    // puntoFinal                |-->|
    // cantidadPedestrian        |-->| 
    // densidad                  |-->| 
    // pedestrianIdsInSubLink    |-->| 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int idSubLink;
    vector2D puntoFinal;
    int cantidadPedestrian;
    double densidad;
    std::vector<int> pedestriansIdsInSubLink;
    
public:
    static int numberDivisiones;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    subLink();
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void setIdSubLink(int idSubLink);
    void setPuntoFinal(vector2D puntoFinal);
    void setCantidadPedestrian(int cantidadPedestrian);
    void setDensidad(double densidad);
    void setPedestriansIdsInSubLink(std::vector<int> pedestrianIdsInSubLink);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int getIdSubLink();
    vector2D getPuntoFinal();
    int getCantidadPedestrian();
    double getDensidad();
    std::vector<int> getPedestrianIdsInSubLink();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void calcularCantidadPedestrian();
    void calcularDensidad(int length, int width);
    double calcularAnchoDivisiones();
    bool verificarPedestrianId(int idPedestrian);
    void agregarPedestrianId(int idPedestrian);
    void quitarPedestrianId(int idPedestrian);
    void mostrarSubLink();
    
};
#endif
