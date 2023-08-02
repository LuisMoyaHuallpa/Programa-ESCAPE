#include "velocity.h"
const int velocity::velocidad =1;


velocity::velocity() {
  
}
velocity::velocity(double componentX, double componentY) {
  
}

void velocity::setComponentX(double componentX){
    (*this).componentX = componentX;
}
void velocity::setComponentY(double componentY){
    (*this).componentY = componentY;
}

double velocity::getComponentX() {
    return componentX;
}
double velocity::getComponentY(){
    return componentY;
}
