#include "link.h"
#include "pedestrian.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int link::numberLinkDivision = std::get<int>(dictionary::get()->lookup("numberLinkDivision"));


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
link::link(int idLink, node *node1, node *node2, int length, int width)
    : idLink(idLink), node1Ptr(node1), node2Ptr(node2), length(length), width(width),
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
const node* link::getNode1Ptr() const {
    return node1Ptr;
}
const node* link::getNode2Ptr() const {
    return node2Ptr;
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
int& link::getDensityLevel() {
    return densityLevel;
}

std::vector<pedestrian*>& link::getPedestriansLinkPtr() {
    return pedestriansLinkPtr;
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
const vector2D link::calcularOrientacionLink() const{
    /* deberia esta calcular orientacion pero necesita acceder a dbLink
        por ello se calculara la direccione en pedestrian*/
    /* calcula la direccion de la calle con los nodos inicial y final*/
    const double x = node2Ptr->getCoordenada().getX() - node1Ptr->getCoordenada().getX();
    const double y = node2Ptr->getCoordenada().getY() - node1Ptr->getCoordenada().getY();
    // Calcula la magnitud del vector de dirección
    const double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    // Normaliza el vector de dirección (divide cada e por la magnitud)
    return {std::abs(x / magnitud), std::abs(y / magnitud)};
}
const double link::calcularAnchoDivisiones() const{
    /* Calcula el ancho de divisiones de la calle segun el numero de divisiones preestablecidas*/
    const double ancho_x = node1Ptr->getCoordenada().getX() - node2Ptr->getCoordenada().getX();
    const double ancho_y = node1Ptr->getCoordenada().getY() - node2Ptr->getCoordenada().getY();
    const double ancho = std::sqrt(ancho_x * ancho_x + ancho_y * ancho_y) / static_cast<double>(link::numberLinkDivision);
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
            j->getVelocidadPedestrian().actualizarVelocidad(it->getDensidadSublink());
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
    for (int i = 0; i < pedestriansLinkPtr.size(); i++) {
        std::cout << pedestriansLinkPtr.at(i)->getIdPedestrian() << " ";
    }
}
void link::mostrarSubdivisiones() const {
    std::cout << "subdivisiones: ";
    for (int i = 0; i < subdivisiones.size(); i++) {
        subdivisiones.at(i).mostrarPedestriansInSublink();
    }
}
void link::mostrarLink() const {
    std::cout << "link: ";
    std::cout << idLink << " ";
    std::cout << "nodes: ";
    std::cout << node1Ptr->getIdNode() << " ";
    std::cout << node2Ptr->getIdNode() << " ";
    mostrarPedestriansLink();
    mostrarSubdivisiones();
    std::cout << std::endl;
}
void link::imprimirLink(std::fstream& file) {
    file << std::fixed << std::setprecision(2);
    file << node1Ptr->getCoordenada().getX() << " ";
    file << node1Ptr->getCoordenada().getY() << " ";
    file << node2Ptr->getCoordenada().getX() << " ";
    file << node2Ptr->getCoordenada().getY() << " ";
    file << std::endl;
}
