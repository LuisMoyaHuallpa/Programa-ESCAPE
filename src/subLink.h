#ifndef subLink_h
#define subLink_h

#include "vector2D.h"
#include <vector>
#include <iostream>

// class link;
class subLink  {

private:
    int idSubLink;
    vector2D puntoFinal;
    int cantidadPedestrian;
    double densidad;
    std::vector<int> pedestriansIdsInSubLink;
    
public:
    subLink();
    
    void setIdSubLink(int idSubLink);
    void setPuntoFinal(vector2D puntoFinal);
    void setCantidadPedestrian(int cantidadPedestrian);
    void setDensidad(double densidad);
    void setPedestriansIdsInSubLink(std::vector<int> pedestrianIdsInSubLink);

    int getIdSubLink();
    vector2D getPuntoFinal();
    int getCantidadPedestrian();
    double getDensidad();
    std::vector<int> getPedestrianIdsInSubLink();

    void calcularCantidadPedestrian();
    void calcularDensidad(int length, int width);
    bool verificarPedestrianId(int idPedestrian);
    void agregarPedestrianId(int idPedestrian);
    void quitarPedestrianId(int idPedestrian);
    void mostrarSubLink();
    
};
#endif
