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

#include <cstdlib>
#include <functional>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <variant>
#include "dictionary.h"
#include "pedestrian.h"
#include "tiempo.h"
#include "nodes.h"
#include "links.h"
#include "stateMatrixs.h"
#include "pedestrians.h"
#include <getopt.h>

int main(int argc, char* argv[]) {
  // comandos
  static struct option long_opts[] = {
    {"input",  required_argument, nullptr, 'i'},
    {"pythonOption",  required_argument, nullptr, 'p'},
    {"stateMatrixFile",  required_argument, nullptr, 's'},
    {"output", required_argument, nullptr, 'o'},
    {"help",   no_argument,       nullptr, 'h'},
    {nullptr, 0,                 nullptr,  0}
  };
  
  int opt, idx;
  while ((opt = getopt_long(argc, argv, "i:o:h:p", long_opts, &idx)) != -1) {
    switch (opt) {
    case 'i':
      std::cout << "Input = " << optarg << "\n";
      break;
    case 'o':
      std::cout << "Output = " << optarg << "\n";
      break;
    case 'h':
      /* mostrar ayuda */ return 0;
    case 'p':
      dictionary::get()->getControlDict()["pythonVersion"] = "yes";
      dictionary::get()->getControlDict()["pythonOption"] = optarg;
      std::cout << "python mode = " << optarg << "\n";
      break;
    case 's':
      dictionary::get()->getControlDict()["previousComputationFile"] = optarg;
      std::cout << "state mode = " << optarg << "\n";
      break;
    case '?':
      /* opción desconocida */ return 1;
    }
  }
    // imprimi malla de calles.
    links::get()->imprimirMeshLinks();
    // Lectura de simulaciones pasadas.
    stateMatrixs::get()->leerDbStateMatrixs();
    // segun el número de simulaciones
    while (tiempo::get()->getINumberSimulation() <= tiempo::get()->getEndNumberSimulation()) {
        // calcula el valor el valor del randomChoiceRate
        tiempo::get()->calcularRandomChoiceRate();
        // loop para una evacuacion
        while (tiempo::get()->running()) {
            tiempo::get()->aumentarTiempo();
           // modelamiento de pedestrian.
            pedestrians::get()->modelamientoPedestrians();
            // contador de personas un tiempo atras de la funcion modelamiento
            links::get()->contarPedestrians();
            io::get()->imprimirOutput();
            // pone en 0 los elementos valores sublink            
            links::get()->resetSublinks();
        }
        // mostrar resultados simulation
        tiempo::get()->mostrarIResultadosSimulacion();
        // aumentar el numero de simulacion y reiniciar valores
        tiempo::get()->aumentarINumberSimulation();
    }
}
