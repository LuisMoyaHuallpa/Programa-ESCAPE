#include "pedestrians.h"
#include "dictionary.h"
#include "tiempo.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrians* pedestrians::pedestriansInstance = nullptr;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrians::pedestrians() {
    // creacion de data de personas
    leerPedestrians(dictionary::get()->lookupDefault("populationsFile"));
    // tiempo de inicio segun la distribucion rayleigh
    tiempoInicioDistribution();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<pedestrian>& pedestrians::getDbPedestrianTotal() {
    return dbPedestrianTotal; 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrians* pedestrians::get() {
    /* si aun no existe crea la unica instancia de pedestrians*/
    if (!pedestriansInstance) {
        pedestriansInstance =  new pedestrians();
    }
    return pedestriansInstance;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrians::leerPedestrians(std::string fileName){
    std::fstream file;
    file.open(fileName, std::ios::in);
    // verificar si existe el archivo
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
    std::string edad_str, gender_str, hhType_str, hhId_str, idNodeArranque_str;
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
        std::getline(iss, idNodeArranque_str, '\n');
        // Cambiar de str a int
        int edad = std::stoi(edad_str);
        int gender = std::stoi(gender_str);
        int hhType = std::stoi(hhType_str);
        int hhId = std::stoi(hhId_str);
        int idNodeArranque = std::stoi(idNodeArranque_str);
        // Creacion de cada persona en la data base.
        dbPedestrianTotal.push_back(pedestrian(edad, gender, hhType, hhId, nodes::get()->getDbNodeTotal().at(idNodeArranque).get()));
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

void pedestrians::tiempoInicioDistribution() {
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
void pedestrians::contarPedestriansInSublink() {
    /* cuenta la personas que no han sido evacuadas y hayan empezado a caminar
        solo donde hay personas*/ 
    if (tiempo::get()->verificarPedestrianCountPeriod()) {
        for (auto it = dbPedestrianTotal.begin(); it != dbPedestrianTotal.end(); ++it) {
            if (!it->getEvacuado()and
            tiempo::get()->getValorTiempo() > it->getTiempoInicial()) {
                it->contarPedestrianInSublink(); 
            }
        }
        // calcula el nivel de densidad de todas las calles con los datos anterios
        links::get()->calcularDensityLevelLinks();
    }
}
void pedestrians::reiniciarPedestriansNodeArranque() {
    // regresa a la persona a su posicion de salida inicial antes de empezar la evacuacion
    for (int i = 0; i < dbPedestrianTotal.size(); i++) {
        dbPedestrianTotal.at(i).setEvacuado(false);
        dbPedestrianTotal.at(i).setNodeInicio(const_cast<node*>(dbPedestrianTotal.at(i).getNodeArranque()));
    }
}
void pedestrians::reiniciarConteoPedestrians() {
    //  
    for (auto it = dbPedestrianTotal.begin(); it != dbPedestrianTotal.end(); ++it) {
        // it->modelamientoPedestrian();
    }
}
void pedestrians::modelamientoPedestrians() {
    //  
    for (auto it = dbPedestrianTotal.begin(); it != dbPedestrianTotal.end(); ++it) {
        it->modelamientoPedestrian();
    }
}
void pedestrians::mostrarDbPedestrianTotal() {
    for (int i = 0; i < dbPedestrianTotal.size(); i++) {
        dbPedestrianTotal.at(i).mostrarMovimientoPedestrian();
    }
}
void pedestrians::imprimirPedestrians(){
    /* imprimir datos de posicion, cantidad de evacuados y velocidad.*/
    // imprimir solo en la ultima simulacion
    if (tiempo::get()->getINumberSimulation() == tiempo::get()->getEndNumberSimulation() ) {
        // imprime segun el valor de graphicPrintoutPeriod del controlDict
        if (tiempo::get()->verificarGraphicPrintout()) {
            //crea la carpeta de tiempo
            tiempo::get()->crearCarpetaTiempo();
            // impresion de datos
            std::string folderName = std::to_string(tiempo::get()->getValorTiempo());
            std::fstream file1, file2, file3, file4;
            file1.open(folderName + "/xy", std::ios::out);
            file2.open(folderName + "/U", std::ios::out);
            file3.open(folderName + "/cantPedestrianEvacuated", std::ios::out);
            file4.open("transientNumberEvacuated.csv", std::ios::app);
            nodeEvacuation::imprimirTrasientNumberEvacuated(file4);
            if (file1.is_open()) {
                for (auto it = dbPedestrianTotal.begin(); it != dbPedestrianTotal.end(); ++it) {
                    if (tiempo::get()->getValorTiempo() >= it->getTiempoInicial()) {
                        it->imprimirPedestrianPosition(file1);
                        it->imprimirPedestrianVelocity(file2);
                    }
                }
                nodeEvacuation::imprimirNodeEvacuation(file3);
            }
        }
    }
}
