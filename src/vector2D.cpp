#include "vector2D.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector2D::vector2D() {
    (*this).X = 0;
    (*this).Y = 0;
}
vector2D::vector2D(double X, double Y) {
    setX(X);
    setY(Y);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void vector2D::setX(double X){
    (*this).X = X;
}
void vector2D::setY(double Y){
    (*this).Y = Y;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double vector2D::getX() {
    return X;
}
double vector2D::getY(){
    return Y;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector2D vector2D::operator+(vector2D vector2) {
    /* operacion suma de vectores*/
    double x = this->getX() + vector2.getX();
    double y = this->getY() + vector2.getY();
    return vector2D(x, y);
}
vector2D vector2D::operator*(vector2D vector2) {
    /* operacion multiplicacion de vectores*/
    double x = this->getX() * vector2.getX();
    double y = this->getY() * vector2.getY();
    return vector2D(x, y);
}
vector2D vector2D::operator*(double scalar) {
    // operacion multipliacion de vector y scalar
    double x = this->getX() * scalar;
    double y = this->getY() * scalar;
    return vector2D(x,y);
}
vector2D vector2D::operator+=(vector2D vector2) {
    X += vector2.getX();
    Y += vector2.getY();
    return *this;
}
void vector2D::mostrarVector() {
    std::cout << "(" << getX() << ",";
    std::cout << getY() << ")" << std::endl;
    
}
