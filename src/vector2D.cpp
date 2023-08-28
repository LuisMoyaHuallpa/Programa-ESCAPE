#include "vector2D.h"

vector2D::vector2D() {
    (*this).X = 0;
    (*this).Y = 0;
}
vector2D::vector2D(double X, double Y) {
    setX(X);
    setY(Y);
}

void vector2D::setX(double X){
    (*this).X = X;
}
void vector2D::setY(double Y){
    (*this).Y = Y;
}

double vector2D::getX() {
    return X;
}
double vector2D::getY(){
    return Y;
}

vector2D vector2D::operator+(vector2D vector2) {
    double x = this->getX() + vector2.getX();
    double y = this->getY() + vector2.getY();
    return vector2D(x, y);
}
vector2D vector2D::operator*(double scalar) {
    double x = this->getX() * scalar;
    double y = this->getY() * scalar;
    return vector2D(x,y);
}
vector2D vector2D::operator+=(vector2D vector2) {
    X += vector2.getX();
    Y += vector2.getY();
    return *this;
}
