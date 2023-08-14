#include "pedestrian.h"
#include "link.h"
#include "node.h"
#include "subLink.h"
#include "tiempo.h"
#include "vector2D.h"
#include "vector2DVelocidad.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <iomanip>

const int pedestrian::surviveReward = 100000;
const int pedestrian::deadReward = -1000; 
const int pedestrian::stepReward = -1;
int pedestrian::contador = 1;

pedestrian::pedestrian() : nodeInicio () {
    (*this).idPedestrian = 0;
    (*this).edad = 0;
    (*this).hhType = 0;
    (*this).hhId = 0;
}
pedestrian::pedestrian(int edad, int gender, int hhType, int hhId, node* nodeInicio) {
    setIdPedestrian(contador++);
    setEdad(edad);
    setGender(gender);
    setHHType(hhType);
    setHHId(hhId);
    setNodeInicio(nodeInicio);
    double x = nodeInicio->getCoordX();
    double y = nodeInicio->getCoordY();
    vector2D position(x, y);
    setPosition(position);
    eleccionRandomLinkActual();
    calcularNodeFinal();
    calcularOrientacion();
    calcularVelocidadLink();
}

void pedestrian::setIdPedestrian(int id){
    (*this).idPedestrian = id;
}
void pedestrian::setEdad(int edad){
    (*this).edad = edad;
}
void pedestrian::setGender(int gender) {
    (*this).gender = gender;  
}
void pedestrian::setHHType(int hhType){
    (*this).hhType = hhType;
}
void pedestrian::setHHId(int hhId){
    (*this).hhId = hhId;
}
void pedestrian::setNodeInicio(node* nodeInicio){
    (*this).nodeInicio = nodeInicio;
}
void pedestrian::setNodeFinal(node* nodeFinal) {
    (*this).nodeFinal = nodeFinal;
}
void pedestrian::setPosition(vector2D position) {
    (*this).position = position;
}
void pedestrian::setLinkActual(link *linkActual) {
    (*this).linkActual = linkActual;
}
void pedestrian::setOrientacion(vector2D orientacion) {
    (*this).orientacion = orientacion;
}
void pedestrian::setVelocidad(vector2DVelocidad velocidad) {
    (*this).velocidad = velocidad;
}
void pedestrian::setRetorno(int retorno) {
    (*this).retorno = retorno;
}

int pedestrian::getIdPedestrian() const {
    return idPedestrian;
}
int pedestrian::getEdad() const{
    return edad;
}
int pedestrian::getGender() {
    return gender;
}
int pedestrian::getHHType() const{
    return hhType;
}
int pedestrian::getHHId() const{
    return hhId;
}
node* pedestrian::getNodeInicio() const{
    return nodeInicio;
}
node* pedestrian::getNodeFinal() {
    return nodeFinal;  
}
vector2D pedestrian::getPosition() {
    return position;
}
link *pedestrian::getLinkActual() {
    return linkActual;
}
vector2D pedestrian::getOrientacion() {
    return orientacion;
}
vector2DVelocidad pedestrian::getVelocidad() {
    return velocidad;
}
int pedestrian::getRetorno() {
    return retorno;  
}

void pedestrian::mostrarPedestrian(){
    std::cout << getIdPedestrian() << ' ';
    std::cout << std::setw(6) << getNodeInicio()->getIdNode() << ' ';
    std::cout << "start: ";
    std::cout << std::fixed << std::setprecision(1);
    std::cout << std::setw(5) << getNodeInicio()->getCoordX() << ' ';
    std::cout << std::setw(5) << getNodeInicio()->getCoordY() << ' ';
    std::cout << "now: ";
    std::cout << std::setw(5) << getPosition().getX() << " ";
    std::cout << std::setw(5) << getPosition().getY() << " ";
    std::cout << "end: ";
    std::cout << std::setw(5) << getNodeFinal()->getCoordX() << ' ';
    std::cout << std::setw(5) << getNodeFinal()->getCoordY() << ' ';
    std::cout << std::endl;
}
void pedestrian::imprimirPedestrian(std::fstream& file){
    file << getPosition().getX() << " ";
    file << getPosition().getY() << " ";
    file << std::endl;
}
void pedestrian::caminar() {
    position += velocidad * tiempo::deltaTiempo;
    contarPedestrainSubdivision();
}
void pedestrian::eleccionRandomLinkActual() {
    // Obtener una semilla aleatoria del hardware
    std::random_device rd;

    // Algoritmo Motor Mersenne Twister
    std::mt19937 generador(rd());

    int limite_max = nodeInicio->getLinkConnection().size() - 1 ;

    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<int> distribucion(0, limite_max);

    int numero_aleatorio = distribucion(generador);

    // link* linkSeleccionado = nodeInicio->getLinkConnection().at(numero_aleatorio);
    link* linkSeleccionado = getNodeInicio()->getLinkConnection().at(numero_aleatorio);
    setLinkActual(linkSeleccionado);
}
//Calculo de velocidad decomponiendo en la orientacion de link 
void pedestrian::calcularVelocidadLink() {
    (*this).velocidad.setOrientacion(&orientacion);
}
bool pedestrian::verificarEndLink() {
    bool terminoLink = false;
    // if (position.getX() == nodeFinal->getCoordX() and
    // position.getY() == nodeFinal->getCoordY()){
    //     terminoLink = true;
    // }
    if (position.getX()*orientacion.getX() >= nodeFinal->getCoordX()*orientacion.getX() and
    position.getY()*orientacion.getY() >= nodeFinal->getCoordY()*orientacion.getY()){
        terminoLink = true;
    }

    return terminoLink;
}
void pedestrian::calcularNodeFinal() {
    // busqueda del node final
    if(nodeInicio == linkActual->getNode1()){
        setNodeFinal(linkActual->getNode2());
    }
    else {
        setNodeFinal(linkActual->getNode1());
    }
}
void pedestrian::updateLinkParameter() {
    if (verificarEndLink()) {
        setNodeInicio(nodeFinal);
        eleccionRandomLinkActual();
        calcularNodeFinal();
        calcularOrientacion();
        calcularVelocidadLink();
    }
}
void pedestrian::calcularOrientacion() {
    vector2D direction;
    double x = nodeFinal->getCoordX() - nodeInicio->getCoordX();
    double y = nodeFinal->getCoordY() - nodeInicio->getCoordY();

    // Calcula la magnitud del vector de dirección
    double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));

    // Normaliza el vector de dirección (divide cada e por la magnitud)
    orientacion.setX(x / magnitud);
    orientacion.setY(y / magnitud);
}
void pedestrian::calcularRetorno() {
    if (nodeInicio->getEvacuationCode() == 0) {
        retorno += stepReward;
    }
    else {
        retorno += surviveReward;
    }
}
bool pedestrian::verificarEvacuationNode(){
    if (nodeInicio->getEvacuationCode() == 1) {
        return true;
    }
    return false;
}
void pedestrian::contarPedestrainSubdivision() {
    int idContador;
    if (linkActual->getNode1()->getCoordX() < linkActual->getNode2()->getCoordX()) {
        int row = std::trunc((position.getX()-linkActual->getNode1()->getCoordX()) / static_cast<double>(linkActual->getUnitWidthPartion()));
        int col = std::trunc((position.getY()-linkActual->getNode1()->getCoordY()) / static_cast<double>(linkActual->getUnitWidthPartion()));
        if (row == col) {
            std::cout << "start" <<std::endl;
            idContador = row;
            for (int i = 0; i < linkActual->getSubLinks().size(); i++) {
                std::cout << linkActual->getSubLinks().at(i).getCantidadPedestrian()<< " ";
            }
            std::cout << std::endl;
            linkActual->getSubLinks().at(idContador).sumarPedestrian();
            for (int i = 0; i < linkActual->getSubLinks().size(); i++) {
                std::cout << linkActual->getSubLinks().at(i).getCantidadPedestrian()<< " ";
            }
            std::cout << std::endl;
            std::cout << "end" <<std::endl;
        }
        else {
            idContador = std::max(row, col);
            linkActual->getSubLinks().at(idContador).sumarPedestrian();
        }
    }
    else {
        int row = std::trunc((position.getX()-linkActual->getNode2()->getCoordX()) / static_cast<double>(linkActual->getUnitWidthPartion()));
        int col = std::trunc((position.getY()-linkActual->getNode1()->getCoordY()) / static_cast<double>(linkActual->getUnitWidthPartion()));
        if (row == col) {
            idContador = row;
            linkActual->getSubLinks().at(idContador).sumarPedestrian();
        }
        else {
            idContador = std::max(row, col);
            linkActual->getSubLinks().at(idContador).sumarPedestrian();
            
        }
        // linkActual->mostrarSubLinks();
    }
    // double row = std::ceil(position.getX()-linkActual->getNode1()->getCoordX() / static_cast<double>(linkActual->getUnitWidthPartion()));
    // std::cout << linkActual->getSubDivision().getPuntoFinal().at(0).getX() << " ";
    // std::cout << row <<std::endl;
    // double col = std::ceil(position.getY() / static_cast<double>(linkActual->getLength()));
    // std::cout << linkActual->getSubDivision().getCantidadPedestrian().at(row-1);
}
