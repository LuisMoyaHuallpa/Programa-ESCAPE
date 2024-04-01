#include "link.h"
#include "pedestrian.h"
#include "subLink.h"
#include "vector2D.h"
#include <algorithm>
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int link::numberLinkDivision = std::stoi(dictionary::get()->lookup("numberLinkDivision"));


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
link::link(int idLink, node *node1, node *node2, int length, int width)
    : idLink(idLink), node1(node1), node2(node2), length(length), width(width),
      orientacionLink(calcularOrientacionLink()),
      anchoSubdivision(calcularAnchoDivisiones()),
      densityLevel(0) {
    subdivisiones.resize(link::numberLinkDivision, subLink(this));
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void link::setDensityLevel(int densityLevel) {
    (*this).densityLevel = densityLevel;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int link::getIdLink() const {
    return idLink;  
}
const node* link::getNode1() {
    return node1;
}
const node* link::getNode2() {
    return node2;
}
const int link::getLength() const{
    return length;
}
const int link::getWidth() const{
    return width;
}
const vector2D link::getOrientacionLink() const {
    return orientacionLink;
}
int* link::getDensityLevel() {
    return &densityLevel;
}
std::vector<pedestrian*>& link::getPedestriansLink() {
    return pedestriansLink;
}
std::vector<subLink>& link::getSublink() {
    return subdivisiones;  
}
const double link::getAnchoSubdivisiones() const {
    return anchoSubdivision;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
vector2D link::calcularOrientacionLink() {
    /* deberia esta calcular orientacion pero necesita acceder a dbLink
        por ello se calculara la direccione en pedestrian*/
    double x = node2->getCoordenada().getX() - node1->getCoordenada().getX();
    double y = node2->getCoordenada().getY() - node1->getCoordenada().getY();
    // Calcula la magnitud del vector de dirección
    double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    // Normaliza el vector de dirección (divide cada e por la magnitud)
    // orientacionLink.setX(std::abs(x / magnitud));
    // orientacionLink.setY(std::abs(y / magnitud));
    return {std::abs(x / magnitud), std::abs(y / magnitud)};
}
double link::calcularAnchoDivisiones() {
    /* Calcula el ancho de divisiones de la calle segun el numero de divisiones preestablecidas*/
    double ancho_x = node1->getCoordenada().getX() - node2->getCoordenada().getX();
    double ancho_y = node1->getCoordenada().getY() - node2->getCoordenada().getY();
    double ancho = std::sqrt(pow(ancho_x, 2) + pow(ancho_y, 2)) / static_cast<double>(link::numberLinkDivision);
    return ancho;
}
void link::calcularDensity() {
    /* calculo de la densidad en cada sublink de la calle*/
    for (auto it = subdivisiones.begin(); it != subdivisiones.end(); ++it) {
        // subdivion es it
        // calculo de densidad en subdivisiones
        it->calcularDensidadSubdivision();
        // recorre todas las personas en la subdivion
        // j es una persona
        for (auto j : it->getPedestriansInSublink()) {
            // actualizacion de velocidad
            j->getVelocidad().actualizarVelocidad(it->getDensidadSublink());
        }
    }
}
void link::calcularDensityLevel() {
    // Encontrar el sublink con mayor densidad de la calle
    auto max_iter = std::max_element(subdivisiones.begin(), subdivisiones.end(),
    [](const subLink& a, const subLink& b) {
        return a.getDensidadSublink() < b.getDensidadSublink();
    });
    // elecion del nivel de densidad segun rangos preestablecidos
    if(max_iter->getDensidadSublink() <= 0.5){
        densityLevel = 0;
    }  
    else if (max_iter->getDensidadSublink() <= 3.0) {
        densityLevel = 1;
    }
    else {
        densityLevel = 2;
    }
}
void link::mostrarPedestriansLink() const {
    std::cout << "pedestrianLink: ";
    for (int i = 0; i < pedestriansLink.size(); i++) {
        std::cout << pedestriansLink.at(i)->getIdPedestrian() << " ";
    }
}
void link::mostrarSubdivisiones() const {
    std::cout << "subdivisiones: ";
    for (int i = 0; i < subdivisiones.size(); i++) {
        subdivisiones.at(i).mostrarPedestriansInSublink();
    }
}
void link::mostrarLink(){
    std::cout << "link: ";
    std::cout << getIdLink() << " ";
    std::cout << "nodes: ";
    std::cout << node1->getIdNode() << " ";
    std::cout << node2->getIdNode() << " ";
    mostrarPedestriansLink();
    mostrarSubdivisiones();
    std::cout << std::endl;
}
void link::imprimirLink(std::fstream& file) {
    file << std::fixed << std::setprecision(2);
    file << node1->getCoordenada().getX() << " ";
    file << node1->getCoordenada().getY() << " ";
    file << node2->getCoordenada().getX() << " ";
    file << node2->getCoordenada().getY() << " ";
    file << std::endl;
}
