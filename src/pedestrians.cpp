#include "pedestrians.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::vector<pedestrian> pedestrians::dbPedestrianTotal;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
pedestrians::pedestrians() {
    (*this).fileName = "population.csv";
    leerPedestrians(fileName);
    tiempoInicioDistribution();
}
pedestrians::pedestrians(std::string fileName) {
    leerPedestrians(fileName);  
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void pedestrians::caminarPedestrians(int valorTiempo) {
    //  
    for (int i = 0; i < dbPedestrianTotal.size(); i++) {
        if (valorTiempo == dbPedestrianTotal.at(i).getTiempoInicial()) {
            dbPedestrianTotal.at(i).setEmpezoCaminar(true);
            // dbPedestrianTotal.at(i).inicializarq();
            // dbPedestrian.at(i).getqStateAction()->mostrarQ();
            // dbPedestrianTotal.at(i).getNodeInicio()->mostrarQTable();
        }
        if (!dbPedestrianTotal.at(i).getEvacuado()) {
            if (valorTiempo > dbPedestrianTotal.at(i).getTiempoInicial()) {
                // dbPedestrianTotal.at(i).contarPedestrainSubdivision();
                dbPedestrianTotal.at(i).caminar();
                // dbPedestrianTotal.at(i).encontrarPrimerTiempo();
                // dbPedestrianTotal.at(i).updateLinkParameter();
                // dbPedestrianTotal.at(i).calcularRetorno();
            }
        }
    }
}
// void pedestrians::caminarPedestrians(int valorTiempo, sarsa* sarsaAlgorithm) {
//     for (int i = 0; i < dbPedestrian.size(); i++) {
//         if (valorTiempo == dbPedestrian.at(i).getTiempoInicial()) {
//             dbPedestrian.at(i).setEmpezoCaminar(true);
//             // dbPedestrian.at(i).crearStateAction();
//         }
//         if (!dbPedestrian.at(i).getEvacuado()) {
//             if (valorTiempo > dbPedestrian.at(i).getTiempoInicial()) {
//                 dbPedestrian.at(i).contarPedestrainSubdivision();
//                 dbPedestrian.at(i).caminar();
//                 dbPedestrian.at(i).encontrarPrimerTiempo();
//                 dbPedestrian.at(i).updateLinkParameter(sarsaAlgorithm);
//                 dbPedestrian.at(i).calcularRetorno();
//             }
//         }
//     }
// }
// boost::math::rayleigh_distribution<double> pedestrians::calcularDistribucionRayleigh() {
//     // calcula la distribucion rayleigh.
//     boost::random::mt19937 gen;
//     // Set the parameters for the Rayleigh distribution
//     double meanRayleigh = 7 * 60;
//     double scaleRayleigh = meanRayleigh * std::pow((2/M_PI), 05);
//     boost::math::rayleigh_distribution<double> rayleighDistribution(scaleRayleigh);
//     return rayleighDistribution;
//     for (int i = 0; i < dbPedestrianTotal.size(); ++i) {
//         int number = std::round(boost::math::quantile(rayleighDistribution, boost::random::uniform_01<double>()(gen)));
//         dbPedestrianTotal.at(i).setTiempoInicial(number);
//         // std::cout << dbPedestrian.at(i).getTiempoInicial() << " ";
//     }
// }
void pedestrians::tiempoInicioDistribution() {
    // calcula el tiempo de inicio, calculado con la distribucion rayleigh
    boost::random::mt19937 gen;
    // Set the parameters for the Rayleigh distribution
    double meanRayleigh = 7 * 60;
    double scaleRayleigh = meanRayleigh * std::pow((2/M_PI), 05);
    boost::math::rayleigh_distribution<double> rayleighDistribution(scaleRayleigh);
    for (int i = 0; i < dbPedestrianTotal.size(); ++i) {
        int number = std::round(boost::math::quantile(rayleighDistribution, boost::random::uniform_01<double>()(gen)));
        dbPedestrianTotal.at(i).setTiempoInicial(number);
        std::cout << dbPedestrianTotal.at(i).getTiempoInicial() << std::endl;
    }
}
void pedestrians::leerPedestrians(std::string fileName){
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
        pedestrians::dbPedestrianTotal.push_back(pedestrian(edad, gender, hhType, hhId, &(nodes::dbNodeTotal.at(idNodeInicio))));
    }
    file.close(); 
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// mostrar
void pedestrians::mostrarPedestrians(){
    // recorrer todos los pedestrianas utilizando su funcion mostrar de cada persona.
    for (int i=0; i < dbPedestrianTotal.size(); i++) {
        dbPedestrianTotal.at(i).mostrarPedestrian();
    }
}
// void pedestrians::imprimirPedestrians(std::string folderName){
//     std::fstream file,file2;
//     file.open(folderName + "/xy",std::ios::out);
//     file2.open(folderName + "/U",std::ios::out);
//     if (file.is_open()) {
//         for (int i=0; i < dbPedestrian.size(); i++) {
//             if (dbPedestrian.at(i).getEmpezoCaminar()) {
//                 dbPedestrian.at(i).imprimirPedestrianPosition(file);
//                 dbPedestrian.at(i).imprimirPedestrianVelocity(file2);
//             }
//         }
//     }
// }
