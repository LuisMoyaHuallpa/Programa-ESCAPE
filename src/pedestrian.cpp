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

#include "pedestrian.h"

#include "io.h"
#include "node.h"
#include "link.h"
#include "nodeDestino.h"
#include "sarsa.h"
#include "stateMatrix.h"
#include "stateMatrixs.h"
#include "tiempo.h"
#include "vector2D.h"
#include "velocidad.h"
#include <iostream>
#include <vector>
#include "pedestrians.h"
#include <limits> // Para std::numeric_limits

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int pedestrian::contador = 1;
const int pedestrian::meanRayleigh = std::get<int>(dictionary::get()->lookup("meanRayleigh"));
const int pedestrian::surviveReward = 100000;
const int pedestrian::deadReward = -1000; 
const int pedestrian::stepReward = -1;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrian::pedestrian(const int edad, const int gender, const int hhType, const int hhId, node* nodeArranque)
    : idPedestrian(contador++),
      edad(edad),
      gender(gender),
      hhType(hhType),
      hhId(hhId),
      nodeArranque(nodeArranque),
      tiempoInicial(calcularRayleighDistribution(calcularScaleRayleigh())),
      position(nodeArranque->getCoordenada()),
      nodeInicioPtr(nodeArranque),
      nodeFinalPtr(nullptr),
      direccionPedestrian(),
      velocidadPedestrian(),
      estadoPedestrian(pasivo),
      reward(0),
      tiempoAnteriorInterseccion(0),
      interseccion(true),
      stateMatrixCurrentPtr(nullptr),
      QCurrentPtr(nullptr),
      QPreviousPtr(nullptr),
      linkCurrentPtr(nullptr)
{
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void pedestrian::setPosition(vector2D position) {
//     (*this).position = position;
// }
void pedestrian::setNodeInicio(node* nodeInicio){
    (*this).nodeInicioPtr = nodeInicio;
}
// void pedestrian::setNodeFinal(node* nodeFinal) {
//     (*this).nodeFinal = nodeFinal;
// }
// void pedestrian::setNodeInicioAnterior(node* nodeInicioAnterior) {
//     (*this).nodeInicioAnterior = nodeInicioAnterior;
// }
// void pedestrian::setLinkActual(link* linkActual) {
//     (*this).linkActual = linkActual;
// }
// void pedestrian::setLinkPasado(link *linkPasado) {
//     (*this).linkPasado = linkPasado;
// }
void pedestrian::setDireccionPedestrian(vector2D direccionPedestrian) {
    (*this).direccionPedestrian = direccionPedestrian;
}
void pedestrian::setVelocidadPedestrian(double velocidadPedestrian) {
    (*this).velocidadPedestrian.setMagnitud(velocidadPedestrian);
}
void pedestrian::setEstadoPedestrian(estado estadoPedestrian) {
    (*this).estadoPedestrian = estadoPedestrian;
}
// void pedestrian::setOrientacionLinkPasado(vector2D orientacionLinkPasado) {
//     (*this).orientacionLinkPasado = orientacionLinkPasado;
// }
// void pedestrian::setTiempoFinal(int tiempoFinal) {
//     (*this).tiempoFinal = tiempoFinal;
// }
// void pedestrian::setEmpezoCaminar(bool empezoCaminar) {
//     (*this).empezoCaminar = empezoCaminar;
// }
// void pedestrian::setPrimerTiempo(bool primerTiempo) {
//     (*this).primerTiempo = primerTiempo;
// }
// void pedestrian::setSaltoLink(bool saltoLink) {
//     (*this).saltoLink = saltoLink;
// }
void pedestrian::setReward(int reward) {
    (*this).reward = reward;
}
void pedestrian::setInterseccion(bool interseccion) {
    (*this).interseccion = interseccion;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int pedestrian::getIdPedestrian() const {
    return idPedestrian;
}
const int pedestrian::getEdad() const{
    return edad;
}
const int pedestrian::getGender() const {
    return gender;
}
const int pedestrian::getHHType() const{
    return hhType;
}
const int pedestrian::getHHId() const{
    return hhId;
}
const node* pedestrian::getNodeArranque() const {
    return nodeArranque;
}
const int pedestrian::getTiempoInicial() const {
    return tiempoInicial;
}
vector2D pedestrian::getPosition() const{
    return position;
}
node* pedestrian::getNodeInicio() const{
    return nodeInicioPtr;
}
node* pedestrian::getNodeFinal() const {
    return nodeFinalPtr;  
}
vector2D pedestrian::getDireccionPedestrian() const {
    return direccionPedestrian;
}
velocidad& pedestrian::getVelocidadPedestrian() {
    return velocidadPedestrian;
}
estado& pedestrian::getEstadoPedestrian() {
    return estadoPedestrian;
}
int pedestrian::getReward() const {
    return reward;  
}
int pedestrian::getTiempoAnteriorInterseccion() const{
    return tiempoAnteriorInterseccion;
}
bool pedestrian::getInterseccion() const {
    return interseccion;    
}
link* pedestrian::getLinkCurrent() const {
    return linkCurrentPtr;
}
stateMatrix *pedestrian::getStateMatrixCurrent() const {
    return stateMatrixCurrentPtr;    
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool pedestrian::operator==(const pedestrian& pedestrian2) const{
    /* compara si dos pedestrian son iguales*/
    // la comparacion es con id
    return idPedestrian == pedestrian2.idPedestrian;
}
void pedestrian::caminar() {
    /* formula de desplazamiento*/
    const vector2D velocidad = direccionPedestrian * velocidadPedestrian.getMagnitud();
    position += velocidad * tiempo::get()->getDeltaT();
}
double pedestrian::calcularIdSublink() {
    /* Calcula la ubicacion de la persona en el array del subLink*/
    // distancia de la persona al nodo 1 de la calle
    const double anchoSubdivision = linkCurrentPtr->getAnchoSubdivisiones();
    const double index_x = position.getX() - linkCurrentPtr->getNode1Ptr()->getCoordenada().getX();
    const double index_y = position.getY() - linkCurrentPtr->getNode1Ptr()->getCoordenada().getY();
    int index_hipo = std::sqrt(std::pow(index_x,2) + pow(index_y, 2)) / anchoSubdivision;
    // si encuentra en una subdivision mayor a lo que no tiene es porque ya a punto de entrar a una interseccion
    if (index_hipo >= linkCurrentPtr->getCantidadSubdivisiones()) {
        interseccion = true;
        // index_hipo = linkCurrentPtr->getCantidadSubdivisiones() - 1;    
    }
    return index_hipo;
}
bool pedestrian::verificarEndLink() const {
    // Calcula la distancia euclidiana entre las coordenadas actuales y el punto objetivo
    const double umbral = velocidadPedestrian.getMagnitud();
    const double distancia = std::sqrt(std::pow(position.getX() - nodeFinalPtr->getCoordenada().getX(), 2) + std::pow(position.getY() - nodeFinalPtr->getCoordenada().getY(), 2));
    // Verifica si la distancia es menor o igual al umbral
    return distancia <= umbral;
}
int pedestrian::calcularIdEndSublink() const {
    /* Permite saber cual es el ultimo sublink*/
    // averguio si estoy al final o al inicio
    if (nodeInicioPtr == linkCurrentPtr->getNode1Ptr()) {
        // si estoy al inicio es el ultimo subdivione
        return linkCurrentPtr->getSubdiviones().size() - 1; 
    } 
    // esta al inicio
    else {
        return 0;
    }
}
link* pedestrian::eleccionGeneralLink() const {
    // la primera eleccion debe ser random
    if (tiempo::get()->getValorTiempo() == tiempoInicial and std::get<std::string>(dictionary::get()->lookupDefault("process")) == "calibration") {
        return eleccionRandomLink();
    }
    if (estadoPedestrian == evacuado) {
        return nullptr;
    }
    // Configurar el generador de números aleatorios
    else {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<double> dis(0.0, 1.0);
        // Generar un número aleatorio en el rango [0.0, 1.0)
        const double randomNumber = dis(gen);
        // compara el numero aletorio con optima choice rate
        // este ultimo debe ir descendiendo cuando halla mas simulaciones
        // a mayor simulaciones mas uso de la elecion sarsa
        switch (randomNumber <= tiempo::get()->getRandomChoiceRate() ? 1 : 2) {
            case 1:
                return eleccionRandomLink();
            case 2:
                return eleccionSarsaLink();
        }
    }
    return nullptr;
}
link* pedestrian::eleccionRandomLink() const {
    /* La persona esta en una interseccion y tiene multiples opciones para elegir una calle.
        segun aletoriedad se decide cual sera la calle a tomar y se guardará en linkActual.*/
    // Algoritmo Motor Mersenne Twister
    static std::random_device rd;
    static std::mt19937 generador(rd());
    // linkConnection del nodo de inicio 
    const std::vector<link*> linkConnection = nodeInicioPtr->getLinkConnectionsPtr();
    const int limite_max = linkConnection.size() - 1 ;
    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<size_t> distribucion(0, limite_max);
    // eleccion de una calle de forma aletoria
    const size_t numero_aleatorio = distribucion(generador);
    // eleccion de la calle nueva, parte principal de la funcion
    return linkConnection.at(numero_aleatorio);
}
link* pedestrian::eleccionSarsaLink() const {
    // busca el elemento mayor de Q del stateMatrix experimentado
    const Q* Qmax = stateMatrixCurrentPtr->buscarQMax();
    return const_cast<link*>(Qmax->getCallePtr());
}
// void pedestrian::eleccionDosCallesContinuas() {
//     // linkActual es la calle a punto de cambiar
//     if (!(nodeInicio->getLinkConnection().at(0)->getIdLink() == linkActual->getIdLink())) {
//         // setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(0)));
//         // setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(0)).get());
//         setLinkActual(nodeInicio->getLinkConnection().at(0));
//         // enviando informacion de action al stateMatrix
//         stateMatrixPedestrian.getActionValue().setILinkConnection(0);
//         stateMatrixPedestrian.getActionValue().setIdLink(linkActual->getIdLink());
//         // sabiendo la calle defino el nodo final.
//         calcularNodeFinal();
//         // verificar si el nodo final es un nodo de evacucion.
//         verificarPedestrianEvacuation();
//     }
//     else {
//         // setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(1)));
//         // setLinkActual(links::get()->getDbLinkTotal().at(getNodeInicio()->getIdLinkConnection().at(1)).get());
//         setLinkActual(nodeInicio->getLinkConnection().at(0));
//         // enviando informacion de action al stateMatrix
//         stateMatrixPedestrian.getActionValue().setILinkConnection(1);
//         stateMatrixPedestrian.getActionValue().setIdLink(linkActual->getIdLink());
//         // sabiendo la calle defino el nodo final.
//         calcularNodeFinal();
//         // verificar si el nodo final es un nodo de evacucion.
//         verificarPedestrianEvacuation();
//     }
// }
int pedestrian::calcularSignoNumero(double numero) {
    if (numero >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}
void pedestrian::calcularDireccionPedestrian() {
    direccionPedestrian = linkCurrentPtr->getOrientacionLink() * calcularSignoDireccion();
}
vector2D pedestrian::calcularSignoDireccion() {
    double x = calcularSignoNumero(nodeFinalPtr->getCoordenada().getX() - nodeInicioPtr->getCoordenada().getX());
    double y = calcularSignoNumero(nodeFinalPtr->getCoordenada().getY() - nodeInicioPtr->getCoordenada().getY());
    return vector2D(x,y);
}
int pedestrian::calcularReward() const {
    /* calculo del reward por paso*/
    const int tiempoDesplazamiento = calcularTiempoDesplazamiento();
    const int pasos = tiempoDesplazamiento / tiempo::get()->getDeltaT();
    return pasos * stepReward;
}
int pedestrian::calcularTiempoDesplazamiento() const {
   /* calcula el proximo tiempo donde el pedestrian estará en una interseccion*/
    const int tiempoDesplazado = tiempo::get()->getValorTiempo() - tiempoAnteriorInterseccion;
    return  tiempoDesplazado;
}
void pedestrian::modelamientoPedestrian() {
    if(!(estadoPedestrian == evacuado)){
        const int tiempoActual = tiempo::get()->getValorTiempo();
        // cuando la persona esta en pasivo, cambia el estado a evacuado cuando llegue su tiempo de salida
        if (estadoPedestrian == pasivo && tiempoInicial == tiempoActual) {
            estadoPedestrian = evacuando;
        }
        // realiza el movimiento solo cuando esta evacuando
        if (estadoPedestrian == evacuando or estadoPedestrian==evacuado) {
                // modelamiento cuando la persona esta en una interseccion
            if (interseccion) {
                // si no ha evacuado realizar lo siguiente
                // si fuera un tiempo diferente al inicial, guardar lo presente en lo pasado
                if(!(tiempoInicial == tiempoActual)){
                    // reinicia el valor del reward
                    reward = 0;
                    // guarda el Qcurents antes que sea cambiado
                    // stateMatrixPreviousPtr = stateMatrixCurrentPtr;
                    QPreviousPtr = QCurrentPtr;
                    // ahora la interseccion final es la interseccion inicial.
                    nodeInicioPtr = nodeFinalPtr;
                    // correcion de la posicion cuando se llega cerca al nodo.
                    position = {nodeInicioPtr->getCoordenada().getX(), nodeInicioPtr->getCoordenada().getY()};
                    // verifico si estoy en un punto de evacuacion
                }
                // nodeInicioPtr->mostrarNode();
                estadoPedestrian = nodeInicioPtr->estadoPedestrianEnNodo();
                // observa el estado del nodo o nodeEvacuation
                const std::vector<int> stateObservado = nodeInicioPtr->stateObservado();
                // obtener stateMatrix
                stateMatrixCurrentPtr = stateMatrix::creacionObtencionStateMatrix(nodeInicioPtr, stateObservado);
               // stateMatrixCurrentPtr->mostrarStateMatrix();
                // eleccion de la calle
                linkCurrentPtr = eleccionGeneralLink();
                if (estadoPedestrian == evacuando) {
                    // // agrego a la personas en la calle
                    // linkCurrentPtr->agregarPedestrian(this);
                    // obtener nodo final
                    nodeFinalPtr = const_cast<node*>(nodeInicioPtr->buscarNodoFinal(linkCurrentPtr));
                    // direccion de la persona en la calle.
                    calcularDireccionPedestrian();
                    // calcular idEndSublink
                    idEndSublink = calcularIdEndSublink();
                }
                // obtener Qcurrent
                QCurrentPtr = stateMatrixCurrentPtr->buscarQ(linkCurrentPtr);
                // aumentar observacion
                QCurrentPtr->aumentar1Observacion();
                // excepto al iniciar
                if (estadoPedestrian == evacuado) {
                    dynamic_cast<nodeDestino*>(nodeInicioPtr)->contabilizarPersona(this);
                }
                if (std::get<std::string>(dictionary::get()->lookupDefault("process")) == "calibration"){
                    if(!(tiempoInicial == tiempoActual)){
                        reward = calcularReward();
                        sarsa::sarsaActualizarQ(QPreviousPtr->getValor(), QCurrentPtr->getValor(), reward);
                    }
                }
                // guarda la anteror interseccion
                tiempoAnteriorInterseccion = tiempoActual;
                // paso a la calle
                interseccion=false;
            }
            else {
                // modelamiento cuando la persona esta dentro de la calle
                if (estadoPedestrian == evacuando) {
                    // solo agrega cuando no esta en la interseccion
                    if (tiempo::get()->getPedestrianCountPeriod()) {
                        // velocidad con random
                        velocidadPedestrian.calcularAjusteRandom();
                    }
                    // camina la persona
                    caminar();    
                   // calcula posicion en subdivion 
                    const int idSublink = calcularIdSublink();
                    // cuando esta en un sublink cercano a nodoFinal
                    if (idSublink == idEndSublink and interseccion == false) {
                        // verifica cuando esta cerca a una interseccion
                        interseccion = verificarEndLink();
                    }
                    // verifica cada cuanto debe contar
                    if (tiempo::get()->getPedestrianCountPeriod()) {
                        // solo agrega cuando no esta en la interseccion
                        if (interseccion==false) {
                            // agrega persona en sublink
                            linkCurrentPtr->agregarPedestrianSublink(this, idSublink);
                        }
                    }
                }
            }
        }
    }
}
void pedestrian::reiniciar() {
    /* reiniciar valores para proxima simulacion*/
    nodeInicioPtr = const_cast<node*>(nodeArranque);
    position = nodeInicioPtr->getCoordenada();
    estadoPedestrian = pasivo;
    interseccion = true;
    // reward = 0;
}
void pedestrian::mostrarMovimientoPedestrian() const {
    /* muestra la interseccion de partida y final de una calle, cuando
        la persona.*/
    if (estadoPedestrian == evacuando or estadoPedestrian== evacuado) {
        std::cout << idPedestrian << ' ';
        std::cout << std::setw(6) << nodeInicioPtr->getIdNode() << ' ';
        std::cout << "start: ";
        // decimales para imprecion
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::setw(5) << nodeInicioPtr->getCoordenada().getX() << ' ';
        std::cout << std::setw(5) << nodeInicioPtr->getCoordenada().getY() << ' ';
        std::cout << "now: ";
        std::cout << std::setw(5) << position.getX() << " ";
        std::cout << std::setw(5) << position.getY() << " ";
        std::cout << "end: ";
        
        std::cout << std::setw(5) << nodeFinalPtr->getCoordenada().getX() << ' ';
        std::cout << std::setw(5) << nodeFinalPtr->getCoordenada().getY() << ' ';
        std::cout << std::setw(5) << getReward() << ' ';
        std::cout << std::endl;
    }
}
void pedestrian::mostrarPedestrian() const {
    std::cout << idPedestrian << ' ';
    std::cout << nodeInicioPtr->getIdNode() << ' ';
    std::cout << "ti: " << tiempoInicial;
}
void pedestrian::imprimirPedestrianPosition(fileIO* file) const {
    // if (getEvacuado()) {
    // decimales para guardar en archivos.
    file->getFileFstream() << std::fixed << std::setprecision(2);
    file->getFileFstream() << position.getX() << " ";
    file->getFileFstream() << position.getY() << " ";
    file->getFileFstream() << std::endl;
    // }
}
void pedestrian::imprimirPedestrianVelocity(fileIO* file) const{
    file->getFileFstream() << velocidadPedestrian.getMagnitud() << " ";
    file->getFileFstream() << std::endl;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const double pedestrian::calcularScaleRayleigh() {
    return static_cast<double>(meanRayleigh) * std::pow((2.0/M_PI), 0.5);
}
double generate_uniform_random(std::mt19937& gen) {
    // Generar un número aleatorio uniforme en el rango (0, 1)
    return std::generate_canonical<double, std::numeric_limits<double>::digits>(gen);
}
double pedestrian::calcularRayleighDistribution(const double sigma) {
    /* calcula un numero segun la distribucion rayliegh, como parametro necesita
        la variable sigma que es la scaleRayleigh */
    std::random_device rd;
    std::mt19937 gen(rd());
    // Generar un número aleatorio uniforme
    double u = generate_uniform_random(gen);
    // Calcular el número aleatorio según la distribución Rayleigh
    return sigma * std::sqrt(-2.0 * std::log(1.0 - u));
}
void pedestrian::plotearPedestrians(fileIO* const file) {
    // Inicializa valores máximos y mínimos
    static double minX = std::numeric_limits<double>::max();
    static double maxX = std::numeric_limits<double>::lowest();
    static double minY = std::numeric_limits<double>::max();
    static double maxY = std::numeric_limits<double>::lowest();
    // lo leo solo al incio 
    if (tiempo::get()->getValorTiempo() == 1) {
      // elimina las imagenes al iniciar el programa
        const std::string deleteCommand = "rm -f " + io::get()->directoryImages.getFullPath() + "Figure-*.png";
        int deleteResult = system(deleteCommand.c_str());

        const auto& lineasCalles = links::get()->getDbLinkTotal();
        for (const auto lc : lineasCalles) {
            // Obtener puntos de inicio y fin para la línea
            const auto puntoInicial = lc->getNode1Ptr();
            const auto puntoFinal = lc->getNode2Ptr();
            
            // Obtener las coordenadas
            double x1 = puntoInicial->getCoordenada().getX();
            double y1 = puntoInicial->getCoordenada().getY();
            double x2 = puntoFinal->getCoordenada().getX();
            double y2 = puntoFinal->getCoordenada().getY();
            
            // Actualiza los valores máximos y mínimos
            minX = std::min(minX, std::min(x1, x2));
            maxX = std::max(maxX, std::max(x1, x2));
            minY = std::min(minY, std::min(y1, y2));
            maxY = std::max(maxY, std::max(y1, y2));
        }
    }
    FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
    if (gnuplotPipe) {
        // Configurar Gnuplot
        fprintf(gnuplotPipe, "set output '%s'\n", file->getFullPath().c_str());
        fprintf(gnuplotPipe, "set terminal png size 1920,1080\n");
	fprintf(gnuplotPipe, "set size ratio -1\n");
        fprintf(gnuplotPipe, "set yrange [%lf:%lf]\n", minY, maxY);
        fprintf(gnuplotPipe, "set xrange [%lf:%lf]\n", minX, maxX);
        fprintf(gnuplotPipe, "unset border\n");
        fprintf(gnuplotPipe, "set palette rgbformulae 10,13,22\n");
        fprintf(gnuplotPipe, "set colorbox\n");
        fprintf(gnuplotPipe, "set cbrange [0.2:1.2]\n"); // Reemplaza min y max con tus valores fijos
        fprintf(gnuplotPipe, "set grid\n");
        fprintf(gnuplotPipe, "set tmargin 3\n"); // Margen inferior aumentado
        int minutos =  tiempo::get()->getValorTiempo() / 60; // Dividir para obtener minutos completos
        int segundos =  tiempo::get()->getValorTiempo() % 60; // Resto para los segundos que sobran
	fprintf(gnuplotPipe,
		"set label 't = %d.%d min, evacuated: %d of %d' "
		"font 'Arial,24' "
		"at screen 0.5, 0.98 center\n",
		minutos,
		segundos,
		nodeDestino::totalPersonasEvacuadas,
		static_cast<int>(pedestrians::get()->getDbPedestrianTotal().size()));


        // creacion de plot
        std::string plotCommand = "plot";
        plotCommand += " '-' with lines lc 'black' notitle,";
        // verificar si hay peatones evacuando
        bool peatonesEvacuado = false;
        for (const pedestrian& ped : pedestrians::get()->getDbPedestrianTotal()) {
            if (ped.estadoPedestrian == evacuando) {
                peatonesEvacuado = true;
                break;
            }
        } 
        if (peatonesEvacuado) {
            plotCommand += " '-' with points pt 7 palette notitle,";
        }
        // agregar siempre los puntos de evacuacion
        plotCommand += " '-' with points pt 12 ps 3.0 lc 'red' notitle";
        fprintf(gnuplotPipe, "%s\n", plotCommand.c_str());
        const auto& dbPedestrianTotal = pedestrians::get()->getDbPedestrianTotal();
        const auto& puntosEvacuacion = nodes::get()->getDbNodeEvacuation();
        const auto& lineasCalles = links::get()->getDbLinkTotal();
        // ploteo de lineas de calle
        for (const auto lc : lineasCalles) {
            // Obtener puntos de inicio y fin para la línea
            const auto puntoInicial = lc->getNode1Ptr();
            const auto puntoFinal = lc->getNode2Ptr();
            fprintf(gnuplotPipe, "%lf %lf\n", puntoInicial->getCoordenada().getX(), puntoInicial->getCoordenada().getY());
            fprintf(gnuplotPipe, "%lf %lf\n", puntoFinal->getCoordenada().getX(), puntoFinal->getCoordenada().getY());
            fprintf(gnuplotPipe, "\n");  // Espacio entre las líneas
            // std::cout << puntoInicial->getCoordenada().getX() << " " << puntoInicial->getCoordenada().getY() << " ";
            // std::cout << puntoFinal->getCoordenada().getX() << " " << puntoFinal->getCoordenada().getY() << std::endl;
        }
        fprintf(gnuplotPipe, "e\n");
        // fprintf(gnuplotPipe, "e\n");
        // Itera sobre el vector de peatones utilizando iteradores
        if (peatonesEvacuado) {
            for (const pedestrian& ped : dbPedestrianTotal) {
                if(ped.estadoPedestrian == evacuando){
                    fprintf(gnuplotPipe, "%lf %lf %lf\n", ped.position.getX(), ped.position.getY(), ped.velocidadPedestrian.getMagnitud());
                    // std::cout <<  ped.position.getX() << " " <<  ped.position.getY()<< " "<<ped.velocidadPedestrian.getMagnitud() << std::endl;
                }
            }
            fprintf(gnuplotPipe, "e\n");
        }
        // Segunda serie de puntos (ejemplo: posición inicial)
        for (const nodeDestino* const pe : puntosEvacuacion) {
            fprintf(gnuplotPipe, "%lf %lf\n", pe->getCoordenada().getX() , pe->getCoordenada().getY());
        }
        fprintf(gnuplotPipe, "e\n");
        pclose(gnuplotPipe);
    }
    if (tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime() or nodeDestino::verificarEvacuacionTotal()) {
      const std::string inDir  = io::get()->directoryImages.getFullPath();
      const std::string outDir = io::get()->directoryVideos.getFullPath();
      const std::string comando =
	"ffmpeg -y "
	"-framerate 5 "
	"-pattern_type glob "
	"-i \"" + inDir + "*.png\" "
	"-c:v libx264 "
	"-pix_fmt yuv420p "
	"\"" + outDir + "animation.mp4\" "
	"> /dev/null 2>&1";
      int resultado = system(comando.c_str());
    }

}

