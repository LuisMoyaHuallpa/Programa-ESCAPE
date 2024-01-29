#include "dictionary.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const std::string dictionary::systemCarpet = "system/";
std::map<std::string, std::string> dictionary::controlDict;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

dictionary::dictionary(std::string nameDictionary) {
    (*this).nameDictionary = nameDictionary;
    leerDictionary();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void dictionary::setNameDictionary(std::string nameDictionary) {
    (*this).nameDictionary = nameDictionary;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string dictionary::getNameDictionary() {
    return nameDictionary;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void dictionary::leerDictionary() {
    std::string fileName = dictionary::systemCarpet + getNameDictionary();
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
    std::string keyword_str, value_str;
    while (std::getline(file, line)) {
        // Si el archivo tiene comentarios con # o es una linea vacia,
        // no leerlos.
        if (line[0] == '#' or line.empty()) {
            continue;
        }
        // Guardar cada line en la variable line. 
        std::istringstream iss(line);
        // Guardar cada valor en las variables.
        // guarda la primera para palabra hasta el primer espacio
        iss >> keyword_str;
        std::getline(iss >> std::ws, value_str, ';');
        // guarda los valores en un dictionario
        controlDict[keyword_str] = value_str;

    }
    file.close(); 


}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // static metods
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void dictionary::mostrarControlDict() {
    std::cout << "Contents of controlDict:" << std::endl;
    for (const auto& entry : controlDict) {
        std::cout << entry.first << ": " << entry.second << std::endl;
    }
}
    
