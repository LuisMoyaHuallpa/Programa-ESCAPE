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

#ifndef dictionary_h
#define dictionary_h
/*---------------------------------------------------------------------------*\
    mejorar interfaz usuario
\*---------------------------------------------------------------------------*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header generales
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <string>
#include <fstream>
#include "iostream"
#include <sstream>
#include <map>
#include <variant>
#include <algorithm>
#include <vector>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// header propios
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class dictionary {
private:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static member
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static dictionary* dictionaryInstance;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // endTime               |-->| TIEMPO DE TERMINO DE LA SIMULACION
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    const std::string nameDictionary = "controlDict";
    const std::string systemCarpet = "system/";
    std::map<std::string, std::variant<std::string, int, double, bool>> controlDict;
    const std::map<std::string, std::variant<std::string, int, double, bool>> controlDictDefault = {
        {"nodesFile", std::string("nodes.csv")},
        {"linksFile", std::string("links.csv")},
        {"populationsFile", std::string("population.csv")},
        {"stopAt", std::string("endTime")},
        {"graphicPrintout", true},
        {"graphicPrintoutPeriod", 1},
        {"pedestrianCountPeriod", 1},
        {"computationContinued", false},
        {"observationStatePedestrian", true},
        {"evacuatedCount", true},
        {"totalEvacuatedCount", true},
        {"process", std::string("calibration")},
        {"stopSimulationAt", std::string("endNumberSimulation")},
        {"pythonVersion", false},
        {"pythonOption", std::string("in")},
        {"figureTotalEvacuadosVsSimulacion", true},
        {"figureEvacuadosVsTiempo", true},
        {"tableTotalEvacuadosVsSimulacion", true},
        {"tableEvacuadosVsTiempo", true},
        {"totalEvacuadosVsSimulacionPeriod", 1},
        {"evacuadosVsTiempoAt", std::string("1,2,3")},
        {"opcionSubdivision", std::string("anchoSubdivision")},
        {"cantidadSubdivisiones", 10},
        {"anchoSubdivision", 2.0}
    };
    const std::map<std::string, std::string> typeControlDict = {
        {"nodesFile", "string"},
        {"linksFile", "string"},
        {"populationsFile", "string"},
        {"process", "string"},
        {"stopAt", "string"},
        {"stopSimulationAt", "string"},
        {"startTime", "int"},
        {"endTime", "int"},
        {"deltaT", "int"},
        {"meanRayleigh", "int"},
        {"exploration", "double"},
        {"endNumberSimulation", "int"},
        {"graphicPrintout", "bool"},
        {"graphicPrintoutPeriod", "int"},
        {"pedestrianCountPeriod", "int"},
        {"computationContinued", "bool"},
        {"previousComputationFile", "string"},
        {"observationStatePedestrian", "bool"},
        {"evacuatedCount", "bool"},
        {"totalEvacuatedCount", "bool"},
        {"stopSimulationAt", "string"},
        {"pythonVersion", "bool"},
        {"pythonOption", "string"},
        {"figureTotalEvacuadosVsSimulacion", "bool"},
        {"figureEvacuadosVsTiempo", "bool"},
        {"tableTotalEvacuadosVsSimulacion", "bool"},
        {"tableEvacuadosVsTiempo", "bool"},
        {"evacuadosVsTiempoAt", "string"},
        {"totalEvacuadosVsSimulacionPeriod", "int"},
        {"opcionSubdivision", "string"},
        {"cantidadSubdivisiones", "int"},
        {"anchoSubdivision", "double"}

    };
    std::map<std::string, std::vector<std::string>> controlDictOptions = {{"sarsaProcesses", {"calibration", "trained"}}
    };



    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    dictionary();
    dictionary(std::string nameDictionary);

public:

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // setters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // void setNameDictionary(std::string nameDictionary);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string getNameDictionary();
    std::map<std::string, std::variant<std::string, int, double, bool>>& getControlDict();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static getters
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    static dictionary* get();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // metodos
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void leerDictionary();
    std::variant<std::string, int, double, bool> lookup(std::string keyword);
    std::variant<std::string, int, double, bool> lookupDefault(std::string keyword);
    bool verificarOptions(std::string keyword, std::string value) const;
    bool verificarType(std::string keyword, std::string value);


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static metods
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    void mostrarControlDict();
    
};
#endif
