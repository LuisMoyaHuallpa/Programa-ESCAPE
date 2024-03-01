#include "link.h"
#include "vector2D.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int link::numberDivisiones = 10;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// link::link() : orientacionLink() {
//     (*this).idLink = 0;
//     (*this).idNode1 = 0;
//     (*this).idNode2 = 0;
//     (*this).length = 0;
//     (*this).width = 0;
//     (*this).densityLevel = 0;
// }
link::link(int idLink, node *node1, node *node2, int length, int width)
    : idLink(idLink), node1(node1), node2(node2), length(length), width(width),
      orientacionLink(calcularOrientacionLink()){
    // calcula la orientacion de la calle segun el node 1 y 2.
    // calcularOrientacionLink();
    setDensityLevel(0);
    calcularAnchoDivisiones();
    pedestriansInSublink.resize(link::numberDivisiones, 0);
    densityInSublink.resize(link::numberDivisiones, 0);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void link::setOrientacionLink(vector2D orientacionLink) {
//     (*this).orientacionLink = orientacionLink;
// }
void link::setPedestriansInSublink(std::vector<int> pedestriansInSublink) {
    (*this).pedestriansInSublink = pedestriansInSublink;
}
void link::setDensityInSublink(std::vector<double> densityInSublink) {
    (*this).densityInSublink = densityInSublink;
}
void link::setDensityLevel(int densityLevel) {
    (*this).densityLevel = densityLevel;
}
void link::setAnchoDivisiones(double anchoDivisiones) {
    (*this).anchoDivisiones = anchoDivisiones;
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
std::vector<int>& link::getPedestriansInSublink() {
    return pedestriansInSublink;
}
std::vector<double>& link::getDensityInSublink() {
    return densityInSublink;
}
int link::getDensityLevel() {
    return densityLevel;
}
double link::getAnchoDivisiones() {
    return anchoDivisiones;
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
void link::calcularAnchoDivisiones() {
    /* Calcula el ancho de divisiones de la calle segun el numero de divisiones preestablecidas*/
    double ancho_x = node1->getCoordenada().getX() - node2->getCoordenada().getX();
    double ancho_y = node1->getCoordenada().getY() - node2->getCoordenada().getY();
    double ancho = std::sqrt(pow(ancho_x, 2) + pow(ancho_y, 2)) / static_cast<double>(link::numberDivisiones);
    anchoDivisiones = ancho;
}
void link::calcularDensity() {
    /* calculo de la densidad en cada sublink de la calle*/
    for (int i = 0; i < pedestriansInSublink.size(); i++) {
        densityInSublink.at(i) = pedestriansInSublink.at(i) / (anchoDivisiones * width);
    }
}
void link::calcularDensityLevel() {
    /* calcula el nivel de densidad de la calle */
    double densidadMayorSubLink = 0.0;
    // Encontrar el sublink con mayor densidad de la calle
    for (int i = 0; i < densityInSublink.size(); i++) {
        if (densityInSublink.at(i) > densidadMayorSubLink) {
            densidadMayorSubLink = densityInSublink.at(i);
        }
    }
    // elecion del nivel de densidad segun rangos preestablecidos
    if(densidadMayorSubLink <= 0.5){
        densityLevel = 0;
    }  
    else if (densidadMayorSubLink <= 3.0) {
        densityLevel = 1;
    }
    else {
        densityLevel = 2;
    }
}

void link::mostrarLink(){
    std::cout << "link: ";
    std::cout << getIdLink() << " ";
    std::cout << "nodes: ";
    std::cout << node1->getIdNode() << " ";
    std::cout << node2->getIdNode() << " ";
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
void link::mostrarSubLink() {
    std::cout << getIdLink() << "  ";
    for (int i = 0; i < pedestriansInSublink.size(); i++) {
        std::cout << pedestriansInSublink.at(i) << " ";
    }
    std::cout << std::endl;
}
