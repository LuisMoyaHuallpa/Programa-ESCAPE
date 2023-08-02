#ifndef velocity_h
#define velocity_h

class velocity{

private:
    double componentX;
    double componentY;
    
    
    
public:

    static const int velocidad;
    velocity();
    velocity(double componetX, double componentY);
    void setComponentX(double componentX);
    void setComponentY(double componentY);

    double getComponentX();
    double getComponentY();

    void velocityLink();
};
#endif
