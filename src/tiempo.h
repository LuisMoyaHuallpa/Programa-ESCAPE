#ifndef tiempo_h
#define tiempo_h

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
    
};

#endif
