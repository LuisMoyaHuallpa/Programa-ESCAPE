// MIT License
// Copyright (c) 2025 
// Luis Angel Moya Huallpa, Julio Cesar Ramirez Paredes, Erick Mas, Shunichi Koshimura
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "vector2D.h"
#include <iomanip>

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
double vector2D::getX() const {
    return X;
}
double vector2D::getY() const{
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
vector2D vector2D::operator*(vector2D& vector2) {
    /* operacion multiplicacion de vectores*/
    double x = this->getX() * vector2.getX();
    double y = this->getY() * vector2.getY();
    return vector2D(x, y);
}
vector2D vector2D::operator*(const vector2D& vector2) const {
    /* operacion multiplicacion de vectores*/
    double x = this->getX() * vector2.getX();
    double y = this->getY() * vector2.getY();
    return vector2D(x, y);
}
vector2D vector2D::operator*(const double scalar) const {
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
double vector2D::distanciaA(const vector2D &coordenada2) const {
    /* distancia entre dos coordenadas*/
    double dx = X - coordenada2.getX();
    double dy = Y - coordenada2.getY();
    return std::sqrt(dx * dx + dy * dy);
}
void vector2D::mostrarVector() const {
    /* Muestra en el terminal en formato vector*/
    std::cout << "(" << std::setprecision(3) << X << ",";
    std::cout << std::setprecision(3) << Y << ")" << std::endl;
}
