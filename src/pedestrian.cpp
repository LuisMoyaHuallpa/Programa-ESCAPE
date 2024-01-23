#include "pedestrian.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int pedestrian::contador = 1;
const int pedestrian::surviveReward = 100000;
const int pedestrian::deadReward = -1000; 
const int pedestrian::stepReward = -1;
std::vector<std::shared_ptr<node>> pedestrian::dbNodeTotal;
std::vector<link> pedestrian::dbLinkTotal;
std::vector<pedestrian> pedestrian::dbPedestrianTotal;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrian::pedestrian() : nodeFinal() {
    (*this).idPedestrian = 0;
    (*this).edad = 0;
    (*this).hhType = 0;
    (*this).hhId = 0;
}
pedestrian::pedestrian(int edad, int gender, int hhType, int hhId, node *nodeInicio)
    : nodeFinal(nullptr), nodeInicioAnterior(nullptr), direccionPedestrian(), velocidad(),
      stateMatrixPedestrian(), stateMatrixPedestrianAnterior(), sarsaAlgorithm() {
    setIdPedestrian(contador++);
    setEdad(edad);
    setGender(gender);
    setHHType(hhType);
    setHHId(hhId);
    setNodeInicio(nodeInicio);
    setTiempoInicial(0);
    // setNodeAnterior(nodeInicio);
    // setEmpezoCaminar(false);
    // setPrimerTiempo(true);
    // setSaltoLink(false);
    setEvacuado(false);
    setReward(0);
    verificarPedestrianEvacuation();
    // setRetorno(0);
    // double x = nodeInicio->getCoordX();
    // double y = nodeInicio->getCoordY();
    // vector2D position(x, y);
    // setPosition(position);
    // eleccionRandomLinkActual();
    // setLinkPasado(linkActual);
    // calcularNodeFinal();
    // calcularOrientacion();
    // velocidad.setOrientacion(orientacion);
    // qStateAction = new stateActionQ;
    // // qStateAction->setA(linkActual->getIdLink());
    // // qStateAction->setS(calcularLevelDensityLinks());
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
void pedestrian::setPosition(vector2D position) {
    (*this).position = position;
}
void pedestrian::setNodeInicio(node* nodeInicio){
    (*this).nodeInicio = nodeInicio;
}
void pedestrian::setNodeFinal(node* nodeFinal) {
    (*this).nodeFinal = nodeFinal;
}
void pedestrian::setNodeInicioAnterior(node* nodeInicioAnterior) {
    (*this).nodeInicioAnterior = nodeInicioAnterior;
}
void pedestrian::setLinkActual(link* linkActual) {
    (*this).linkActual = linkActual;
}
void pedestrian::setLinkPasado(link *linkPasado) {
    (*this).linkPasado = linkPasado;
}
// void pedestrian::setqStateAction(stateActionQ* qStateAction) {
//     (*this).qStateAction = qStateAction;
// }
void pedestrian::setDireccionPedestrian(vector2D direccionPedestrian) {
    (*this).direccionPedestrian = direccionPedestrian;
}
void pedestrian::setVelocidad(vector2DVelocidad velocidad) {
    (*this).velocidad = velocidad;
}
void pedestrian::setTiempoInicial(int tiempoInicial) {
    (*this).tiempoInicial = tiempoInicial;
}
void pedestrian::setStateMatrixPedestrian(stateMatrix stateMatrixPedestrian) {
    (*this).stateMatrixPedestrian = stateMatrixPedestrian;
}
void pedestrian::setStateMatrixPedestrianAnterior(stateMatrix stateMatrixPedestrianAnterior) {
    (*this).stateMatrixPedestrianAnterior = stateMatrixPedestrianAnterior;
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
void pedestrian::setEvacuado(bool evacuado) {
    (*this).evacuado = evacuado;
}
void pedestrian::setReward(int reward) {
    (*this).reward = reward;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
vector2D pedestrian::getPosition() {
    return position;
}
node* pedestrian::getNodeInicio() const{
    return nodeInicio;
}
node* pedestrian::getNodeFinal() {
    return nodeFinal;  
}
node* pedestrian::getNodeInicioAnterior() {
    return nodeInicioAnterior;  
}
link* pedestrian::getLinkActual() {
    return linkActual;
}
link* pedestrian::getLinkPasado() {
    return linkPasado;
}
vector2D pedestrian::getDireccionPedestrian() {
    return direccionPedestrian;
}
vector2DVelocidad& pedestrian::getVelocidad() {
    return velocidad;
}
int pedestrian::getTiempoInicial() {
    return tiempoInicial;
}
stateMatrix& pedestrian::getStateMatrixPedestrian() {
    return stateMatrixPedestrian;
}
stateMatrix& pedestrian::getStateMatrixPedestrianAnterior() {
    return stateMatrixPedestrianAnterior;
}
// stateActionQ* pedestrian::getqStateAction() {
//     return qStateAction;
// }

// vector2D pedestrian::getOrientacionLinkPasado() {
//     return orientacionLinkPasado;
// }


// int pedestrian::getTiempoFinal() {
//     return tiempoFinal;  
// }
// bool pedestrian::getEmpezoCaminar() {
//     return empezoCaminar;
// }
// bool pedestrian::getPrimerTiempo() {
//     return primerTiempo;  
// }
// bool pedestrian::getSaltoLink() {
//     return saltoLink;  
// }
bool pedestrian::getEvacuado() {
    return evacuado;
}
int pedestrian::getReward() {
    return reward;  
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
std::vector<std::shared_ptr<node>> pedestrian::getDbNodeTotal() {
    return dbNodeTotal;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrian::caminar() {
    position += velocidad * tiempo::deltaTiempo;
}
void pedestrian::eleccionRandomLinkActual() {
    /* La persona esta en una interseccion y tiene multiples opciones para elegir una calle.
        segun aletoriedad se decide cual sera la calle a tomar y se guardará en linkActual.*/
    std::random_device rd;
    // Algoritmo Motor Mersenne Twister
    std::mt19937 generador(rd());
    int limite_max = nodeInicio->getIdLinkConnection().size() - 1 ;
    // Crear una distribución uniforme usando el rango especificado
    std::uniform_int_distribution<int> distribucion(0, limite_max);
    int numero_aleatorio = distribucion(generador);
    setLinkActual(&dbLinkTotal.at(getNodeInicio()->getIdLinkConnection().at(numero_aleatorio)));
    // enviando informacion de action al stateMatrix
    getStateMatrixPedestrian().getActionValue().setILinkConnection(numero_aleatorio);
    getStateMatrixPedestrian().getActionValue().setIdLink(linkActual->getIdLink());
    // sabiendo la calle defino el nodo final.
    calcularNodeFinal();
    // verificar si el nodo final es un nodo de evacucion.
    verificarPedestrianEvacuation();
}
// int pedestrian::iEleccionRandomLinkActual() {
//     // Eleccion de la calle de los posibles de la variables LinkConnection
//     // cuando se esta en una intersección.
//     // Obtener una semilla aleatoria del hardware
//     std::random_device rd;
//     // Algoritmo Motor Mersenne Twister
//     std::mt19937 generador(rd());
//     int limite_max = nodeInicio->getIdLinkConnection().size() - 1 ;
//     // Crear una distribución uniforme usando el rango especificado
//     std::uniform_int_distribution<int> distribucion(0, limite_max);
//     // int numero_aleatorio = distribucion(generador);
//     return distribucion(generador);
// }
// void pedestrian::updateLinkActual(int iLinkConnection) {
//     // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     // // iLinkConnection          |-->| POSICION EN EL ARREGLO linkConection
//     // //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     // // Actualizar la calle o linkActual, que es la calle por donde ira la persona. 
//     // link* linkSeleccionado = getNodeInicio()->getLinkConnection().at(iLinkConnection);
//     // setLinkActual(linkSeleccionado);
// }
// void pedestrian::updateStateAction(int iLinkConnection) {
//     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     // iLinkConnection          |-->| POSICION EN EL ARREGLO linkConection
//     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//     // Crear la action con idLink y iLinkConnection
//     action a(linkActual->getIdLink(), iLinkConnection);
//     qStateAction->setA(a);
//     std::cout << qStateAction->getA().getILinkConnection() << std::endl;
// }
// // Eleccion del caminar mas recomendable 
// void pedestrian::eleccionProbalistica() {
//     // double Qmayor = 0;
//     // int idMayor = 0;
//     // for (int i = 0; i < nodeInicio->getLinkConnection().size(); i++) {
//     //     if (nodeInicio->getQTable()->at(i).getQ()> Qmayor) {
//     //         Qmayor = nodeInicio->getQTable()->at(i).getQ();
//     //         idMayor = i;
//     //     }
//     // }
//     // link* linkSeleccionado = getNodeInicio()->getLinkConnection().at(idMayor);
//     // setLinkActual(linkSeleccionado);
// }
// // verifica si el nodo ya sali o esta punto final
bool pedestrian::verificarEndLink() {
    // Da verdadero si la persona se encuentra ubicada en el termino de calle.
    bool terminoLink = false;
    if (position.getX()*std::copysign(1, direccionPedestrian.getX()) >= nodeFinal->getCoordenada().getX()*std::copysign(1, direccionPedestrian.getX()) and
    position.getY()*std::copysign(1, direccionPedestrian.getY()) >= nodeFinal->getCoordenada().getY()*std::copysign(1, direccionPedestrian.getY())){
        std::cout << "veri: " << position.getX()*std::copysign(1, direccionPedestrian.getX()) << " ";
        std::cout << nodeFinal->getCoordenada().getX()*std::copysign(1, direccionPedestrian.getX()) << std::endl;
        terminoLink = true;
    }
    return terminoLink;
}
void pedestrian::calcularNodeFinal() {
    /* busqueda del node final segun la calle que se encuentre
        cada calle tiene un nodo de inicio y final depeendiendo
        si esta de ida o vuelta delvolvera el nodo final
        esto seria ida */
    if(nodeInicio->getIdNode() == linkActual->getIdNode1()){
        setNodeFinal(dbNodeTotal.at(linkActual->getIdNode2()).get());
    }
    // esto seria vuelta
    else {
        setNodeFinal(dbNodeTotal.at(linkActual->getIdNode1()).get());
    }
}
int pedestrian::calcularSignoNumero(double numero) {
    if (numero >= 0) {
        return 1;
    }
    else {
        return -1;
    }
}
// void pedestrian::updateLinkParameter() {
//     if (verificarEndLink()) {
//         // algoritmoSarsa();
//     }
// }
void pedestrian::cambioCalle() {
    /* se cambia de calle cuando se termina de recorre la calle actual*/
    if (verificarEndLink()) {
        // guarda el la intersesccional inicial anterior antes que sea cambiada
        setNodeInicioAnterior(nodeInicio);
        // guarda el stateMatrix para calculos del algoritmo sarsa.
        setStateMatrixPedestrianAnterior(stateMatrixPedestrian);
        // ahora la interseccion final es la interseccion inicial.
        setNodeInicio(getNodeFinal());
        // correcion de la posicion cuando se llega cerca al nodo.
        setPosition({getNodeInicio()->getCoordenada().getX(), getNodeInicio()->getCoordenada().getY()});
        // calculo del stateMatrix para obtener datos de state.
        calcularLevelDensityAtNode();
        // eleccionde de la calle
        eleccionRandomLinkActual();
        // guarda infomacion de stateMatrix de la persona en una tabla en nodo.
        stateMatrixtoTableAtNode();
        // algoritmo sarsa
        algoritmoSarsa();
        // direccion de la persona en la calle.
        calcularDireccionPedestrian();
        // envio informacion de direccion al vector de velocidad.
        getVelocidad().setDireccion(getDireccionPedestrian());
        // falta mejor para que ajuste tambien esta velcoida
    }
}
// void pedestrian::updateCalle() {
//     // Actualizacion del parametros del peaton cuando ya esta en nueva calle.
//     setNodeInicio(nodeFinal);
//     verificarPedestrianEvacuation();
//     position.setX(getNodeInicio()->getCoordX());
//     position.setY(getNodeInicio()->getCoordY());
//     eleccionRandomLinkActual();
//     calcularNodeFinal();
//     calcularOrientacion();
//     velocidad.setOrientacion(orientacion);
//     velocidad.calcularVectorVelocidad();
//     // falta mejor para que ajuste tambien esta velcoida
// }
// void pedestrian::updateParametrosPeaton() {
//     // Actualizacion del parametros del peaton cuando ya esta en nueva calle.
//     setNodeInicio(nodeFinal);
//     verificarPedestrianEvacuation();
//     position.setX(getNodeInicio()->getCoordX());
//     position.setY(getNodeInicio()->getCoordY());
//     int iLinkConnection = iEleccionRandomLinkActual();
//     std::cout << "iLink: ";
//     std::cout << iLinkConnection << std::endl;
//     updateLinkActual(iLinkConnection);
//     updateStateAction(iLinkConnection);
//     std::cout << qStateAction->getA().getILinkConnection();
//     // eleccionRandomLinkActual();
//     calcularNodeFinal();
//     calcularOrientacion();
//     velocidad.setOrientacion(orientacion);
//     velocidad.calcularVectorVelocidad();
//     // falta mejor para que ajuste tambien esta velcoida
// }
// void pedestrian::calcularOrientacion() {
//     /* deberia modificar a direccion usando link para que calcule la orientacion
//       la direccion desde estar aca solo eso*/
//     double x = nodeFinal->getCoordX() - nodeInicio->getCoordX();
//     double y = nodeFinal->getCoordY() - nodeInicio->getCoordY();
//     // Calcula la magnitud del vector de dirección
//     double magnitud = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
//     // Normaliza el vector de dirección (divide cada e por la magnitud)
//     orientacion.setX(x / magnitud);
//     orientacion.setY(y / magnitud);
// }
void pedestrian::calcularDireccionPedestrian() {
    setDireccionPedestrian(linkActual->getOrientacionLink() * calcularSignoDireccion());
}
vector2D pedestrian::calcularSignoDireccion() {
    double x = calcularSignoNumero(nodeFinal->getCoordenada().getX() - nodeInicio->getCoordenada().getX());
    double y = calcularSignoNumero(nodeFinal->getCoordenada().getY() - nodeInicio->getCoordenada().getY());
    return vector2D(x,y);
}
void pedestrian::calcularReward() {
    /* calculo del reward por paso*/
    if (evacuado == true) {
        reward += surviveReward;
    }
    else {
        reward += stepReward;
    }
}
void pedestrian::verificarPedestrianEvacuation(){
    /* verifica si el nodoFinal a la cual la persona esta caminado es un nodo de evacuacion */
    if (nodeInicio->getNodeType() == "nodeEvacuation") {
        setEvacuado(true);
        nodeEvacuation::sumarPersonaEvacuada();
    }
    else {
    }
}
// void pedestrian::contarPedestrainSubdivision() {
//     // int idContador;
//     // double index_x = (position.getX() - linkActual->getNode1()->getCoordX()) / static_cast<double>(linkActual->getUnitWidthPartion());
//     // double index_y = (position.getY() - linkActual->getNode1()->getCoordY()) / static_cast<double>(linkActual->getUnitWidthPartion());
//     // int index_hipo = std::trunc(std::sqrt(std::pow(index_x,2) + pow(index_y, 2)));
//     // if (index_hipo > linkActual->getSubLinks().size()-1) {
//     //     index_hipo = linkActual->getSubLinks().size()-1;
//     // }
//     // idContador = index_hipo;
    
//     // if (verificarSaltoLink()) {
//     //     if (linkActual == linkPasado) {
//     //         if (getOrientacion().getX() >= 0 and getOrientacion().getY() >= 0 and !(idContador == 0)) {
//     //             linkActual->getSubLinks().back().quitarPedestrianId(getIdPedestrian());
//     //         }
//     //         else if (getOrientacion().getX() <= 0 and getOrientacion().getY() <= 0 and !(idContador == linkActual->getSubLinks().size()-1)) {
//     //             linkActual->getSubLinks().begin()->quitarPedestrianId(getIdPedestrian());
//     //         }
//     //     }
//     //     if (getOrientacionLinkPasado().getX() >= 0 and getOrientacionLinkPasado().getY() >= 0  and !getPrimerTiempo() and (idContador == 0 or idContador == linkActual->getSubLinks().size()-1)) {
//     //         linkPasado->getSubLinks().back().quitarPedestrianId(getIdPedestrian());
//     //     }
//     //     else if (getOrientacionLinkPasado().getX() <= 0 and getOrientacionLinkPasado().getY() <= 0 and !getPrimerTiempo() and (idContador == 0 or idContador == linkActual->getSubLinks().size()-1) ) {
//     //         linkPasado->getSubLinks().at(0).quitarPedestrianId(getIdPedestrian());
//     //     }
//     // }

//     // if (!verificarEndLink1()) {
//     //     if (!linkActual->getSubLinks().at(idContador).verificarPedestrianId(getIdPedestrian())) {
//     //         linkActual->getSubLinks().at(idContador).agregarPedestrianId(getIdPedestrian());
//     //         linkActual->getSubLinks().at(idContador).calcularDensidad(linkActual->getLength(), linkActual->getWidth());
//     //         velocidad.actualizarVelocidad(linkActual->getSubLinks().at(idContador).getDensidad());
            
//     //         if (getOrientacion().getX() >= 0 and getOrientacion().getY() >= 0 and !(idContador == 0)) {
//     //             linkActual->getSubLinks().at(idContador-1).quitarPedestrianId(getIdPedestrian());
//     //             setSaltoLink(false);
//     //         }
//     //         else if (getOrientacion().getX() <= 0 and getOrientacion().getY() <= 0 and !(idContador == linkActual->getSubLinks().size()-1)) {
//     //             linkActual->getSubLinks().at(idContador+1).quitarPedestrianId(getIdPedestrian());
//     //             setSaltoLink(false);
//     //         }
//     //     }
//     // }    
//     // else {
//     //     linkPasado = linkActual;
//     //     orientacionLinkPasado = orientacion;
//     //     setSaltoLink(true);
//     // }
//     // // linkActual->mostrarSubLinks();
//     // // mostrarPedestrian();
// }
// // verifica si link concide con node1 y nodeinicia
// // bool pedestrian::verificarDirectionLink() {
// //     // return nodeInicio == linkActual->getNode1();
// // }
// void pedestrian::encontrarPrimerTiempo() {
//     if (primerTiempo) {
//         primerTiempo = false;
//     }   
// }
// bool pedestrian::verificarEndLink1() {
//     if (position.getX() >= nodeFinal->getCoordX() and position.getY() >= nodeFinal->getCoordY()
//     and getOrientacion().getX() >= 0 and getOrientacion().getY() >= 0) {
//         return true; 
//     }
//     else if (position.getX() <= nodeFinal->getCoordX() and position.getY() <= nodeFinal->getCoordY()
//     and getOrientacion().getX() <= 0 and getOrientacion().getY() <= 0) {
//         return true; 
//     }
//     return false;
// }
// bool pedestrian::verificarSaltoLink() {
//     if (getSaltoLink() == true) {
//         return true;
//     }
//     return false;
// }
// void pedestrian::correctionPosition(node* nodoBase) {
//   /* correge la posicion de la persona para que calze exactamente en las
//       intersecciones, que tiene como variable nodoBase.
//       debido a la velocidad y tiempo no recorre estamente la distancia al nodo,
//       puede ser un poco mas o menos pero bastante pequeño.*/
//     setPosition({nodoBase->getCoordX(), nodoBase->getCoordY()});
//     // position.setX(nodeFinal->getCoordX());
//     // position.setY(nodeFinal->getCoordY());
// }
void pedestrian::algoritmoSarsa() {
    /* nodoInicioAnterior es la interseccion inicial de la calle anterior o justo
        antes que cambia a la nueva calle
        y nodoInicia es la intersecion incial actual empezando en la nueva calle*/
    // R
    sarsaAlgorithm.setR(getReward());
    // QPrevious
    double QPrevious = nodeInicioAnterior->getStateMatrixTable().at(stateMatrixPedestrianAnterior.getIStateMatrixTable()).getQVector().at(stateMatrixPedestrianAnterior.getActionValue().getILinkConnection());
    sarsaAlgorithm.setQPrevious(QPrevious);
    // QCurrent
    double QCurrent = nodeInicio->getStateMatrixTable().at(stateMatrixPedestrian.getIStateMatrixTable()).getQVector().at(stateMatrixPedestrian.getActionValue().getILinkConnection());
    sarsaAlgorithm.setQCurrent(QCurrent);
    // calcular Q
    sarsaAlgorithm.sarsaActualizarQ();
    nodeInicioAnterior->getStateMatrixTable().at(stateMatrixPedestrianAnterior.getIStateMatrixTable()).getQVector().at(stateMatrixPedestrianAnterior.getActionValue().getILinkConnection()) = sarsaAlgorithm.getQPrevious();
    // reinica el reward de la persona
    setReward(0);
}
void pedestrian::calcularLevelDensityAtNode() {
    /* cuando una persona llega a una interseccion debe saber los estados de las
        diferentes calle, esta informacion se enviará a objeto stateMatrix */
    // std::cout << nodeInicio->getLinkConnection().size()<< std::endl;
    // 
    // std::cout << "idConnection: ";
    // std::cout << nodeInicio->getIdLinkConnection().size() << std::endl;
    stateMatrixPedestrian.getStateValue().getDensityLinks().resize(nodeInicio->getIdLinkConnection().size());
    // std::cout << stateMatrixPedestrian.getStateValue().getDensityLinks().size() << std::endl;
    for (int i = 0; i < nodeInicio->getIdLinkConnection().size(); i++) {
        // nodeInicio->getIdLinkConnection().at(i)->calcularDensityLevel();
        pedestrian::dbLinkTotal.at(nodeInicio->getIdLinkConnection().at(i)).calcularDensityLevel();
        // std::cout << nodeInicio->getLinkConnection().at(i)->getDensityLevel();
        // densityLinks.push_back(nodeInicio->getLinkConnection().at(i)->getDensityLevel());
        stateMatrixPedestrian.getStateValue().getDensityLinks().at(i) = pedestrian::dbLinkTotal.at(i).getDensityLevel();
    }
}
// void pedestrian::crearqState(node* nodeActual) {
//     // // Es un setter del state de la variable qStateAction. 
//     // std::vector<int> densityLinks;
//     // densityLinks.resize(nodeActual->getLinkConnection().size(),0);
//     // // std::cout << nodeInicio->getIdNode() << std::endl;
//     // // std::cout << nodeInicio->getLinkConnection().size() << std::endl;
//     // for (int i = 0; i < nodeActual->getLinkConnection().size(); i++) {
//     //     nodeActual->getLinkConnection().at(i)->calcularDensityLevel();
//     //     // densityLinks.push_back(nodeInicio->getLinkConnection().at(i)->getDensityLevel());
//     //     // densityLinks.insert(densityLinks.cbegin()+ i,nodeInicio->getLinkConnection().at(i)->getDensityLevel());
//     //     densityLinks[i] = nodeActual->getLinkConnection().at(i)->getDensityLevel();
//     // }
//     // qStateAction->setS(densityLinks);
// }
void pedestrian::stateMatrixtoTableAtNode() {
    // Inicializar action en el primer instante. 
    stateMatrix stateMatrixEncontrado;
    bool verificarStateMatrix = false;
    int idq = 0;
    nodeInicio->buscarStateMatrix(stateMatrixPedestrian, verificarStateMatrix, idq);
    if (verificarStateMatrix) {

    }
    else {
        nodeInicio->getStateMatrixTable().push_back(stateMatrixPedestrian);
        stateMatrixPedestrian.setIStateMatrixTable(nodeInicio->getStateMatrixTable().size()-1);
    }
}
// // void pedestrian::crearStateAction() {
// // //     qAnterior.setA(linkActual->getIdLink());
// // //     qAnterior.setS(calcularLevelDensityLinks());
// // //     nodeInicio->addqQTable(qAnterior);
// // }

void pedestrian::mostrarMovimientoPedestrian(){
    /* muestra la interseccion de partida y final de una calle, cuando
      una persona pasa por una calle. Asimismo muestra la posicion actual
      la persona.*/
    std::cout << getIdPedestrian() << ' ';
    std::cout << std::setw(6) << getNodeInicio()->getIdNode() << ' ';
    std::cout << "start: ";
    // decimales para imprecion
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::setw(5) << getNodeInicio()->getCoordenada().getX() << ' ';
    std::cout << std::setw(5) << getNodeInicio()->getCoordenada().getY() << ' ';
    std::cout << "now: ";
    std::cout << std::setw(5) << getPosition().getX() << " ";
    std::cout << std::setw(5) << getPosition().getY() << " ";
    std::cout << "end: ";
    std::cout << std::setw(5) << getNodeFinal()->getCoordenada().getX() << ' ';
    std::cout << std::setw(5) << getNodeFinal()->getCoordenada().getY() << ' ';
    // std::cout << std::setw(5) << getReward() << ' ';
    std::cout << std::endl;
}
void pedestrian::imprimirPedestrianPosition(std::fstream& file){
    // if (getEvacuado()) {
    // decimales para guardar en archivos.
    file << std::fixed << std::setprecision(2);
    file << getPosition().getX() << " ";
    file << getPosition().getY() << " ";
    file << std::endl;
    // }
}
void pedestrian::imprimirPedestrianVelocity(std::fstream& file){
    file << getVelocidad().getMagnitud() << " ";
    file << std::endl;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrian::leerPedestrians(std::string fileName){
    std::fstream file;
    file.open(fileName, std::ios::in);
    
    if (file.fail()) {
        std::cout << "Error opening the file " <<fileName << std::endl;
        exit(1);
    }
    // Variables de una fila del archivo nodos, que seria un solo node
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // edad                 |-->| EDAD DE LA PERSONA
    // gender               |-->| GENERO DE LA PERSONA
    // hhType               |-->| 
    // hhId                 |-->| 
    // idNodeInicio         |-->| ID DEL NODO DE INICIO 
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string line;
    std::string a1_str, a2_str, a3_str, a4_str, a5_str;
    std::string edad_str, gender_str, hhType_str, hhId_str, idNodeInicio_str;
    while (std::getline(file, line)) {
        // Si el archivo tiene comentarios con #, no leerlos.
        if (line[0] == '#') {
            continue;
        }
        // Guardar cada line en la variable line. 
        std::istringstream iss(line);
        // Guardar cada valor en las variables.
        std::getline(iss, edad_str, ',');
        std::getline(iss, gender_str, ',');
        std::getline(iss, hhType_str, ',');
        std::getline(iss, hhId_str, ',');
        std::getline(iss, idNodeInicio_str, '\n');
        // Cambiar de str a int
        int edad = std::stoi(edad_str);
        int gender = std::stoi(gender_str);
        int hhType = std::stoi(hhType_str);
        int hhId = std::stoi(hhId_str);
        int idNodeInicio = std::stoi(idNodeInicio_str);
        // Creacion de cada persona en la data base.
        pedestrian::dbPedestrianTotal.push_back(pedestrian(edad, gender, hhType, hhId, pedestrian::dbNodeTotal.at(idNodeInicio).get()));
    }
    file.close(); 
}

double generate_uniform_random(std::mt19937& gen) {
    // Generar un número aleatorio uniforme en el rango (0, 1)
    return std::generate_canonical<double, std::numeric_limits<double>::digits>(gen);
}

double generate_rayleigh_random(double sigma, std::mt19937& gen) {
    // Generar un número aleatorio uniforme
    double u = generate_uniform_random(gen);

    // Calcular el número aleatorio según la distribución Rayleigh
    double random_number = sigma * sqrt(-2.0 * log(1.0 - u));

    return random_number;
}

void pedestrian::tiempoInicioDistribution() {
    /* calcula el tiempo de inicio, mediante con la distribucion rayleigh*/
    std::random_device rd;
    std::mt19937 gen(rd());

    // Set the parameters for the Rayleigh distribution
    double meanRayleigh = 7 * 60;
    double scaleRayleigh = meanRayleigh * std::pow((2/M_PI), 05);

    for (int i = 0; i < dbPedestrianTotal.size(); ++i) {
        double random_number = generate_rayleigh_random(scaleRayleigh, gen);
        // debe mejorar,
        // tengo problemas cuando la persona empiza a moverse en 0
        if(random_number < 2.0){
            dbPedestrianTotal.at(i).setTiempoInicial(2);
        }
        else {
            dbPedestrianTotal.at(i).setTiempoInicial(random_number);
        }
    }
}

void pedestrian::modelamientoPedestrians(int valorTiempo) {
    //  
    for (int i = 0; i < dbPedestrianTotal.size(); i++) {
        // personas que aun no estan evacuadas
        if (!dbPedestrianTotal.at(i).getEvacuado()) {
            if (valorTiempo == dbPedestrianTotal.at(i).getTiempoInicial()) {
                // set la posicion de inicio del pedestrian
                dbPedestrianTotal.at(i).setPosition({dbPedestrianTotal.at(i).nodeInicio->getCoordenada().getX(), dbPedestrianTotal.at(i).nodeInicio->getCoordenada().getY()});
                // calculo del stateMatrix para obtener datos de state.
                dbPedestrianTotal.at(i).calcularLevelDensityAtNode();
                // eleccionde de la calle
                dbPedestrianTotal.at(i).eleccionRandomLinkActual();
                // guarda infomacion de stateMatrix de la persona en una tabla en nodo.
                dbPedestrianTotal.at(i).stateMatrixtoTableAtNode();
                
                // dbPedestrianTotal.at(i).getStateMatrixPedestrian().mostrarStateMatrix();
                
                // dbPedestrianTotal.at(i).calcularAction();
                // direccion de la persona en la calle.
                dbPedestrianTotal.at(i).calcularDireccionPedestrian();
                // envio informacion de direccion al vector de velocidad.
                dbPedestrianTotal.at(i).getVelocidad().setDireccion(dbPedestrianTotal.at(i).getDireccionPedestrian());
            }
            if (valorTiempo > dbPedestrianTotal.at(i).getTiempoInicial()) {
                // dbPedestrianTotal.at(i).contarPedestrainSubdivision();
                dbPedestrianTotal.at(i).caminar();
                dbPedestrianTotal.at(i).mostrarMovimientoPedestrian();
                std::cout << "orientacion: ";
                dbPedestrianTotal.at(i).getLinkActual()->getOrientacionLink().mostrarVector();
                std::cout << "direcion: ";
                dbPedestrianTotal.at(i).getDireccionPedestrian().mostrarVector();
                // calculo del reward
                dbPedestrianTotal.at(i).calcularReward();
                // verifica el termino de la calle y actualiza a una nueva.
                dbPedestrianTotal.at(i).cambioCalle();
                // dbPedestrianTotal.at(i).encontrarPrimerTiempo();
            }
        }
        else {

                }
        // if (valorTiempo == dbPedestrianTotal.at(i).getTiempoInicial()) {
        //     dbPedestrianTotal.at(i).verificarPedestrianEvacuation();
        //     // set la posicion de inicio del pedestrian
        //     dbPedestrianTotal.at(i).setPosition({dbPedestrianTotal.at(i).nodeInicio->getCoordX(), dbPedestrianTotal.at(i).nodeInicio->getCoordY()});
        //     // calculo del stateMatrix para obtener datos de state.
        //     dbPedestrianTotal.at(i).calcularLevelDensityAtNode();
        //     // eleccionde de la calle
        //     dbPedestrianTotal.at(i).eleccionRandomLinkActual();
        //     // guarda infomacion de stateMatrix de la persona en una tabla en nodo.
        //     dbPedestrianTotal.at(i).stateMatrixtoTableAtNode();

        //     dbPedestrianTotal.at(i).getStateMatrixPedestrian().mostrarStateMatrix();

        //     //
        //     // dbPedestrianTotal.at(i).calcularAction();
        //     // direccion de la persona en la calle.
        //     dbPedestrianTotal.at(i).calcularDireccionPedestrian();
        //     // envio informacion de direccion al vector de velocidad.
        //     dbPedestrianTotal.at(i).getVelocidad().setDireccion(dbPedestrianTotal.at(i).getDireccionPedestrian());

        //     // dbPedestrianTotal.at(i).setEmpezoCami
        //     // dbPedestrianTotal.at(i).inicializarq();
        //     // dbPedestrian.at(i).getqStateAction()->mostrarQ();
        //     // dbPedestrianTotal.at(i).getNodeInicio()->mostrarQTable();
        // }
        // if (!dbPedestrianTotal.at(i).getEvacuado()) {
        //     if (valorTiempo > dbPedestrianTotal.at(i).getTiempoInicial()) {
        //         // dbPedestrianTotal.at(i).mostrarMovimientoPedestrian();                  
        //         // dbPedestrianTotal.at(i).contarPedestrainSubdivision();
        //         dbPedestrianTotal.at(i).caminar();
        //         dbPedestrianTotal.at(i).calcularReward();
        //         // std::cout << dbPedestrianTotal.at(i).getReward() << std::endl;
        //         // verifica el termino de la calle y actualiza a una nueva.
        //         dbPedestrianTotal.at(i).cambioCalle();
        //         // dbPedestrianTotal.at(i).encontrarPrimerTiempo();
        //         // dbPedestrianTotal.at(i).updateLinkParameter();
        //         // dbPedestrianTotal.at(i).calcularReward();
        //     }
        // }
    }
}

void pedestrian::mostrarDbPedestrianTotal() {
    for (int i = 0; i < dbPedestrianTotal.size(); i++) {
        dbPedestrianTotal.at(i).mostrarMovimientoPedestrian();
    }
}
void pedestrian::imprimirPedestrians(int valorTiempo){
    /* imprimir datos de posicion, cantidad de evacuados y velocidad.*/
    std::string folderName = std::to_string(valorTiempo);
    std::fstream file1, file2, file3;
    file1.open(folderName + "/xy", std::ios::out);
    file2.open(folderName + "/U", std::ios::out);
    file3.open(folderName + "/cantPedestrianEvacuated", std::ios::out);
    if (file1.is_open()) {
        for (int i=0; i < dbPedestrianTotal.size(); i++) {
            if (valorTiempo >= dbPedestrianTotal.at(i).getTiempoInicial()) {
                dbPedestrianTotal.at(i).imprimirPedestrianPosition(file1);
                dbPedestrianTotal.at(i).imprimirPedestrianVelocity(file2);
            }
        }
        nodeEvacuation::imprimirNodeEvacuation(file3);
    }
}
