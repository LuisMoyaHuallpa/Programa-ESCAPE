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
	std::string valoresNumeroSimulacion = std::get<std::string>(dictionary::get()->lookupDefault("totalEvacuadosVsSimulacionAt"));
	tiempoSimulacion = stringToVector(valoresNumeroSimulacion);

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
                fprintf(gnuplotPipe, "set title 'Personas evacuadas en el tiempo'\n");
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
    class totalPersonasEvacuadasXSimulacion{
    public:
      std::vector<int> tiempo;
      std::vector<int> totalEvacuados;
    }; 
    // elementos de simulaciones a imprimir
    std::vector<int> tiempoSimulacion;
    std::string valoresNumeroSimulacion = std::get<std::string>(dictionary::get()->lookupDefault("totalEvacuadosVsSimulacionAt"));
    tiempoSimulacion = stringToVector(valoresNumeroSimulacion);
    
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
    if (tiempo::get()->getINumberSimulation() ==  tiempo::get()->getEndNumberSimulation() and tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime()) {
      std::size_t nSim = data.size();                                // número de simulaciones
      std::size_t nRows = data[0].tiempo.size();                     // número de filas por simulación
      // 2. Imprime fila a fila
      for (std::size_t row = 0; row < nRows; ++row) {
	// 2.1 Primero, el tiempo (supongamos que es igual en todas las simulaciones)
	file->getFileFstream() << data[0].tiempo[row];
	
	// 2.2 Luego, para cada simulación, su totalEvacuados[row]
	for (std::size_t sim = 0; sim < nSim; ++sim) {
	  file->getFileFstream() << "," << data[sim].totalEvacuados[row];
	}
	file->getFileFstream() << "\n";
      }
    }
  }
}
void nodeDestino::plotearEvacuadosVsTiempo(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        static std::vector<int> numeroSimulaciones;
        static std::vector<double> survivors;
        // numero de simulacion
        const int numeroSimulacion = tiempo::get()->getINumberSimulation();
        // solo guarda segun el perido en segundos que se le asigne
        if (numeroSimulacion % std::get<int>(dictionary::get()->lookupDefault("totalEvacuadosVsSimulacionPeriod")) == 0 or numeroSimulacion == 1) {
            // guardo datos en data para luego plotearlos
            numeroSimulaciones.push_back(numeroSimulacion);
            survivors.push_back(totalPersonasEvacuadas);
        }
        // imprimir ploteo cuando al final del numero de simulacion y al terminar el tiempo de evacuacion
        if (tiempo::get()->getINumberSimulation() ==  tiempo::get()->getEndNumberSimulation()) {
            FILE* gnuplotPipe = popen("gnuplot -persistent", "w");
            if (gnuplotPipe) {
                // Configurar Gnuplot
                fprintf(gnuplotPipe, "set terminal png size 800,600\n");
                // Usa la ruta completa
                fprintf(gnuplotPipe, "set output '%s'\n", file->getFullPath().c_str());
                fprintf(gnuplotPipe, "set xlabel 'Numero de simulaciones'\n");
                fprintf(gnuplotPipe, "set ylabel 'Numero de sobrevivientes'\n"); 
                fprintf(gnuplotPipe, "set grid\n");
                // fprintf(gnuplotPipe, "set xtics 1\n");  // Cambia '1' al intervalo que desees
                // fprintf(gnuplotPipe, "set ytics 1\n");  // Cambia '1' al intervalo que desees
                // fprintf(gnuplotPipe, "set mytics 4\n");   // 4 sub-ticks entre cada tick principal
                fprintf(gnuplotPipe, "set xrange [1:*]\n"); // Asegura que el eje x comience en 1
                // cracion de plot
                fprintf(gnuplotPipe, "plot '-' with linespoints notitle\n");
                for (size_t j = 0; j < numeroSimulaciones.size(); ++j) {
                    fprintf(gnuplotPipe, "%d %lf\n", numeroSimulaciones.at(j), survivors.at(j));
                }
                fprintf(gnuplotPipe, "e\n");
                pclose(gnuplotPipe);
            }
        }
    }
}
void nodeDestino::imprimirEvacuadosVsTiempo(fileIO* const file) {
    // reviza el dictionario la opcion esta activada, por default esta activado
    if (std::get<bool>(dictionary::get()->lookupDefault(file->getFileName())) == true) {
        static std::vector<int> numeroSimulaciones;
        static std::vector<double> mortalidad;
        // numero de simulacion
        const int numeroSimulacion = tiempo::get()->getINumberSimulation();
        // solo guarda segun el perido en segundos que se le asigne
        if (numeroSimulacion % std::get<int>(dictionary::get()->lookupDefault("totalEvacuadosVsSimulacionPeriod")) == 0 or numeroSimulacion == 1) {
            // enviarlo a archivo tablas
            file->getFileFstream() << numeroSimulacion << ","; 
            file->getFileFstream() << totalPersonasEvacuadas; 
            file->getFileFstream() << std::endl; 
        }
    }
}
void nodeDestino::imprimirVariableTotalPersonasEvacuadas(fileIO* const file) {
    // impresion de tiempo y personas evacuadas
    file->getFileFstream() << totalPersonasEvacuadas;
}
