#ifndef tiempo_h
#define tiempo_h

#include <iostream>
class tiempo {

private:
    int valorTiempo;
    int deltaT;
    bool writeNow;
    int endTime;

public:

    static int deltaTiempo;
    tiempo();

    void setValorTiempo(int valorTiempo);
    void setDeltaT(int deltaT);
    void setWriteNow(bool writeNow);

    int getValorTiempo();
    int getDeltaT();
    bool getWriteNow();

    tiempo& operator++(int);
    bool running();
    void mostrarTiempo();
    
};

#endif
