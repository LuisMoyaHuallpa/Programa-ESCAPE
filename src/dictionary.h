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
    const std::map<std::string, std::variant<std::string, int,double, bool>> controlDictDefault = {
        {"nodesFile", "nodes.csv"},
        {"linksFile", "links.csv"},
        {"populationsFile", "population.csv"},
        {"stopAt", "endTime"},
        {"graphicPrintout", true},
        {"graphicPrintoutPeriod", 1},
        {"pedestrianCountPeriod", 1},
        {"computationContinued", false},
        {"readPedestrianMassState", false},
        {"numberLinkDivision", 10},
        {"evacuatedCount", true},
        {"totalEvacuatedCount", true},
        {"sarsaProcesses", "calibration"},
        {"stopSimulationAt", "endNumberSimulation"}
    };
    const std::map<std::string, std::string> typeControlDict = {
        {"nodesFile", "string"},
        {"linksFile", "string"},
        {"populationsFile", "string"},
        {"sarsaProcesses", "string"},
        {"stopAt", "string"},
        {"stopSimulationAt", "string"},
        {"startTime", "int"},
        {"endTime", "int"},
        {"deltaT", "int"},
        {"meanRayleigh", "int"},
        {"exploration", "double"},
        {"addNumberSimulation", "int"},
        {"graphicPrintout", "bool"},
        {"graphicPrintoutPeriod", "int"},
        {"pedestrianCountPeriod", "int"},
        {"computationContinued", "bool"},
        {"previousComputationFile", "string"},
        {"readPedestrianMassState", "bool"},
        {"numberLinkDivision", "int"},
        {"evacuatedCount", "bool"},
        {"totalEvacuatedCount", "bool"},
        {"stoSimulationAt", "string"}
    };
    std::map<std::string, std::vector<std::string>> controlDictOptions = {
        {"sarsaProcesses", {"calibration", "trained"}}
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
