#include "nodeDestino.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Extra 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "io.h"
#include "nodes.h"
#include "pedestrians.h"
#include "subLink.h"
#include "pedestrian.h"
#include "tiempo.h"
#include <iostream>
#include <string>
#include <vector>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeDestino::totalPersonasEvacuadas=0;
int nodeDestino::maxPersonasEvacuadasGlobal=1000;
bool nodeDestino::evacuacionTotal=false;

std::string nodeDestino::getNodeType() {
    return "nodeDestino";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
nodeDestino::nodeDestino(const int id, const vector2D coordenada)
    : node(id, coordenada),
      maxPersonasEvacuadas(-1),
      lleno(false)
{
}
nodeDestino::nodeDestino(const int id, const vector2D coordenada, const int maxPersonasEvacuadas)
    : node(id, coordenada),
      maxPersonasEvacuadas(maxPersonasEvacuadas),
      lleno(false)
{
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const int nodeDestino::getMaxPersonasEvacuadas() const{
    return maxPersonasEvacuadas;    
}
std::vector<pedestrian*> nodeDestino::getPersonasEvacuadasPtr() const{
    return personasEvacuadasPtr;    
}
bool nodeDestino::getLleno() const{
    return lleno;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool nodeDestino::verificarEvacuacionTotal() {
    /* verifica si todas las personas fueron evacuadas */
    const int totalPersonas = pedestrians::get()->getDbPedestrianTotal().size();
    return totalPersonasEvacuadas == totalPersonas;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void nodeDestino::reiniciar() {
    personasEvacuadasPtr.clear();
    lleno = false;
}
bool nodeDestino::verificarLLeno() const {
    /* verifica si el nodo de evacuacion esta lleno*/
    // compara el tamaño de la lista de personas evacuadas con la cantidad
    // maxima de personas evacuadas en el nodo de evacuacion
    return personasEvacuadasPtr.size() == maxPersonasEvacuadas;

}
estado nodeDestino::estadoPedestrianEnNodo() const {
    /* devuelve el estado de la persona segun el tipo de nodo donde se encuentra */
    return evacuado;
}
bool nodeDestino::verificarNodoEvacuation() const {
    /* verifica si el nodo es un node de evacuacion */
    return true;
}
std::vector<int> nodeDestino::stateObservado() const {
    return {0};
}
void nodeDestino::contabilizarPersona(pedestrian* const persona) {
    personasEvacuadasPtr.push_back(persona);
    totalPersonasEvacuadas++;
}
void nodeDestino::imprimirPersonasEvacuadas(std::fstream* file) {
    *file << personasEvacuadasPtr.size();
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int nodeDestino::getTotalPersonasEvacuadas() {
    return totalPersonasEvacuadas;
}    
void nodeDestino::sumarTotalPersonasEvacuadas() {
    totalPersonasEvacuadas++;
}
void nodeDestino::imprimirNodeEvacuation(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        // impresion de id de nodos, solo en tiempo 1 al inicio
        if (tiempo::get()->getValorTiempo() == 1) {
            // id 1 2 3 4
            file->getFileFstream() << "id,";
            for (int i = 0; i < nodes::get()->getDbNodeEvacuation().size(); i++) {
                file->getFileFstream() << nodes::get()->getDbNodeEvacuation().at(i)->getIdNode();
                // imprime , hasta antes de la ultima
                if (i < nodes::get()->getDbNodeEvacuation().size() - 1) {
                    file->getFileFstream() << ",";
                }
            }
            // salto de linea
            file->getFileFstream() << std::endl;
        }
        // impresion de personas evacuadas por nodo de evacuacion
        // imprime el tiempo
        file->getFileFstream() << tiempo::get()->getValorTiempo() << ",";
        for (int i = 0; i < nodes::get()->getDbNodeEvacuation().size(); i++) {
            // imprime la cantidad de personas evacuadas por nodo
            file->getFileFstream() << nodes::get()->getDbNodeEvacuation().at(i)->getPersonasEvacuadasPtr().size();
            // imprime , hasta antes de la ultima
            if (i < nodes::get()->getDbNodeEvacuation().size() - 1) {
                file->getFileFstream() << ",";
            }
        }
        // salto de linea
        file->getFileFstream() << std::endl;
    }
}
void nodeDestino::imprimirTotalPersonasEvacuadas(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        // impresion de tiempo y personas evacuadas
        file->getFileFstream() << tiempo::get()->getValorTiempo() << ",";
        file->getFileFstream() << totalPersonasEvacuadas;
        file->getFileFstream() << std::endl;
    }
}
std::vector<int> stringToVector(const std::string& str) {
    std::vector<int> result;
    std::string item;
    std::string cleanStr = str;

    // Encontrar el delimitador ';' y eliminar todo lo que está después
    size_t pos = cleanStr.find(';');
    if (pos != std::string::npos) {
        cleanStr = cleanStr.substr(0, pos);
    }

    std::stringstream ss(cleanStr);

    // Divide la cadena en partes usando la coma como delimitador
    while (std::getline(ss, item, ',')) {
        int number;
        std::stringstream(item) >> number; // Convierte la parte a un entero
        result.push_back(number); // Añade el entero al vector
    }

    return result;
}
void nodeDestino::plotearTotalEvacuadosXSimulacion(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        class totalPersonasEvacuadasXSimulacion{
        public:
            std::vector<int> tiempo;
            std::vector<int> totalEvacuados;
        }; 
        // elementos de simulaciones a imprimir
        std::vector<int> tiempoSimulacion;
        auto it1 = dictionary::get()->getControlDict().find("totalEvacuadosXSimulacionAt");
        //atsimulation
        if (it1 != dictionary::get()->getControlDict().end()) {
            // Clave encontrada, proceder con la operación
            static std::string valoresNumeroSimulacion = std::get<std::string>(it1->second);
            tiempoSimulacion = stringToVector(valoresNumeroSimulacion);
        }
        // valores por default
        else {
            tiempoSimulacion = {1,2,3};
        }
        // const std::vector<int> tiempoSimulacion = {1, 2, 3};
        static std::vector<totalPersonasEvacuadasXSimulacion> data(tiempoSimulacion.size());
        auto it = std::find(tiempoSimulacion.begin(), tiempoSimulacion.end(), tiempo::get()->getINumberSimulation());
        // solo entra en el numero de simulacion que pide tiempoSimulacion
        if (it != tiempoSimulacion.end()) {
            // Determinar el índice en el vector `data` basado en la posición en `tiempoSimulacion`
            int index = std::distance(tiempoSimulacion.begin(), it);
            // Agregar el valor del tiempo actual al vector `tiempo` correspondiente
            data.at(index).tiempo.push_back(tiempo::get()->getValorTiempo());
            data.at(index).totalEvacuados.push_back(totalPersonasEvacuadas);
        }
        // imprimir ploteo cuando al final del numero de simulacion y al terminar el tiempo de evacuacion
        if (tiempo::get()->getINumberSimulation() ==  tiempo::get()->getEndNumberSimulation() and tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime()) {
            FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
            if (gnuplotPipe) {
                // Configurar Gnuplot
                fprintf(gnuplotPipe, "set terminal png size 800,600\n");
                // Usa la ruta completa
                fprintf(gnuplotPipe, "set output '%s'\n", file->getFullPath().c_str());
                fprintf(gnuplotPipe, "set xlabel 'Tiempo (s)'\n");
                fprintf(gnuplotPipe, "set ylabel 'Total de personas evacuadas'\n");
                fprintf(gnuplotPipe, "set title 'Personas Evacuadas en el Tiempo'\n");
                fprintf(gnuplotPipe, "set grid\n");
                // Posicionar los títulos a la izquierda
                fprintf(gnuplotPipe, "set key left\n");
                // cracion de plot
                fprintf(gnuplotPipe, "plot ");
                // creando titulo de linea
                for (size_t i = 0; i < data.size(); ++i) {
                    fprintf(gnuplotPipe, "'-' using 1:2 with lines title 'Simulacion %d'", tiempoSimulacion.at(i));
                    if (i < data.size() - 1) {
                        fprintf(gnuplotPipe, ", ");
                    }
                }
                fprintf(gnuplotPipe, "\n");
                // ploteando lineas 
                for (size_t i = 0; i < data.size(); ++i) {
                    for (size_t j = 0; j < data.at(i).tiempo.size(); ++j) {
                        fprintf(gnuplotPipe, "%d %d\n", data.at(i).tiempo.at(j), data.at(i).totalEvacuados.at(j));
                    }
                    fprintf(gnuplotPipe, "e\n");
                }
                fflush(gnuplotPipe);
                pclose(gnuplotPipe);
            }
        }
    }
}
void nodeDestino::imprimirTotalEvacuadosXSimulacion(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        // elementos de simulaciones a imprimir
        std::vector<int> tiempoSimulacion;
        auto it1 = dictionary::get()->getControlDict().find("totalEvacuadosXSimulacionAt");
        if (it1 != dictionary::get()->getControlDict().end()) {
            // Clave encontrada, proceder con la operación
            static std::string valoresNumeroSimulacion = std::get<std::string>(it1->second);
            tiempoSimulacion = stringToVector(valoresNumeroSimulacion);
        }
        // valores por default
        else {
            tiempoSimulacion = {1,2,3};
        }
        // const std::vector<int> tiempoSimulacion = {1, 2, 3};
        auto it = std::find(tiempoSimulacion.begin(), tiempoSimulacion.end(), tiempo::get()->getINumberSimulation());
        // solo entra en el numero de simulacion que pide tiempoSimulacion
        if (it != tiempoSimulacion.end()) {
            // enviar datos a un archivo tabla
            file->getFileFstream() << tiempo::get()->getValorTiempo() << ",";
            file->getFileFstream() << totalPersonasEvacuadas;
            file->getFileFstream() << std::endl;
        }
    }
}
void nodeDestino::plotearMortalidadXSimulacion(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        static std::vector<int> numeroSimulaciones;
        static std::vector<double> mortalidad;
        // numero de simulacion
        const int numeroSimulacion = tiempo::get()->getINumberSimulation();
        // solo guarda segun el perido en segundos que se le asigne
        if (numeroSimulacion % std::get<int>(dictionary::get()->lookupDefault("mortalidadXSimulacionPeriod")) == 0 or numeroSimulacion == 1) {
            // guardo datos en data para luego plotearlos
            numeroSimulaciones.push_back(numeroSimulacion);
            // calculo porcentaje
            const int totalMortalidad = pedestrians::get()->getDbPedestrianTotal().size() - totalPersonasEvacuadas;
            const double porcentajeMortalidad = static_cast<double>(totalMortalidad) / 100.0;
            mortalidad.push_back(porcentajeMortalidad);
        }
        // imprimir ploteo cuando al final del numero de simulacion y al terminar el tiempo de evacuacion
        if (tiempo::get()->getINumberSimulation() ==  tiempo::get()->getEndNumberSimulation()) {
            FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
            if (gnuplotPipe) {
                // Configurar Gnuplot
                fprintf(gnuplotPipe, "set terminal png size 800,600\n");
                // Usa la ruta completa
                fprintf(gnuplotPipe, "set output '%s'\n", file->getFullPath().c_str());
                fprintf(gnuplotPipe, "set xlabel 'Numero de Simulaciones'\n");
                fprintf(gnuplotPipe, "set ylabel 'Mortalidad (%%)'\n"); 
                fprintf(gnuplotPipe, "set grid\n");
                // fprintf(gnuplotPipe, "set xtics 1\n");  // Cambia '1' al intervalo que desees
                fprintf(gnuplotPipe, "set ytics 1\n");  // Cambia '1' al intervalo que desees
                fprintf(gnuplotPipe, "set mytics 4\n");   // 4 sub-ticks entre cada tick principal
                fprintf(gnuplotPipe, "set xrange [1:*]\n"); // Asegura que el eje x comience en 1
                // cracion de plot
                fprintf(gnuplotPipe, "plot '-' with linespoints notitle\n");
                for (size_t j = 0; j < numeroSimulaciones.size(); ++j) {
                    fprintf(gnuplotPipe, "%d %lf\n", numeroSimulaciones.at(j), mortalidad.at(j));
                }
                fprintf(gnuplotPipe, "e\n");
                pclose(gnuplotPipe);
            }
        }
    }
}
void nodeDestino::imprimirMortalidadXSimulacion(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        static std::vector<int> numeroSimulaciones;
        static std::vector<double> mortalidad;
        // numero de simulacion
        const int numeroSimulacion = tiempo::get()->getINumberSimulation();
        // solo guarda segun el perido en segundos que se le asigne
        if (numeroSimulacion % std::get<int>(dictionary::get()->lookupDefault("mortalidadXSimulacionPeriod")) == 0 or numeroSimulacion == 1) {
            // calculo porcentaje
            const int totalMortalidad = pedestrians::get()->getDbPedestrianTotal().size() - totalPersonasEvacuadas;
            const double porcentajeMortalidad = static_cast<double>(totalMortalidad) / 100.0;
            // enviarlo a archivo tablas
            file->getFileFstream() << numeroSimulacion << ","; 
            file->getFileFstream() << porcentajeMortalidad; 
            file->getFileFstream() << std::endl; 
        }
    }
}
void nodeDestino::imprimirVariableTotalPersonasEvacuadas(fileIO* const file) {
    // impresion de tiempo y personas evacuadas
    file->getFileFstream() << totalPersonasEvacuadas;
}
