#include "dictionary.h"
#include <algorithm>

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dictionary* dictionary::dictionaryInstance = nullptr;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dictionary::dictionary() {
    std::cout << "dictionary" <<std::endl;
    leerDictionary();
}
dictionary::dictionary(std::string nameDictionary) {
    leerDictionary();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// setters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// void dictionary::setNameDictionary(std::string nameDictionary) {
//     (*this).nameDictionary = nameDictionary;
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
std::string dictionary::getNameDictionary() {
    return nameDictionary;
}
std::map<std::string, std::variant<std::string, int, double, bool>>& dictionary::getControlDict() {
    return controlDict;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dictionary* dictionary::get() {
    /* si aun no existe crea la unica instancia de dictionario*/
    if (!dictionaryInstance) {
        dictionaryInstance =  new dictionary();
    }
    return dictionaryInstance;
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
        // busca el tipo de valor del elemento
        if (verificarOptions(keyword_str, value_str)) {
            verificarType(keyword_str, value_str);
        }
    }
    file.close(); 
}
std::variant<std::string, int, double, bool> dictionary::lookup(std::string keyword) {
    /* busca la keyword y devuelve su respuesta*/
    auto it = controlDict.find(keyword);
    // si no lo encuentra
    if (it != controlDict.end()) {
        return it->second;
    }
    else {
        std::cout << "El keyword "<< keyword << " no está presente en el controDict.\n";
        // Terminar el programa con un código de error
        std::exit(EXIT_FAILURE);
    }
    return 0; 
}
std::variant<std::string, int, double, bool> dictionary::lookupDefault(std::string keyword) {
    /* busca la keyword y devuelve su respuesta*/
    auto it = controlDict.find(keyword);
    // si no lo encuentra
    if (it != controlDict.end()) {
        return it->second;
    }
    else {
        return controlDictDefault.at(keyword);
    }
}
bool dictionary::verificarOptions(std::string keyword, std::string value) const {
    // busca si existe el keyword dentro de controlDictOptions
    auto it = controlDictOptions.find(keyword);
    if (it != controlDictOptions.end()) {
        const auto& options = it->second;
        if (!(std::find(options.begin(), options.end(), value) != options.end())) {
            std::cout << "El keyword "<< keyword << " no tiene un valor válido." << std::endl;
            std::cout << "Los valores posibles: ";
            for (const auto& option : options) {
                std::cout << option << " ";
            }       
            std::cout << std::endl;
            return false;
        }
    }
    return true;
}
bool dictionary::verificarType(std::string keyword, std::string value)  {
    // busca en el typeControlDict el keyword solicitado y lo guarda en it
    std::map<std::string, std::string>::const_iterator it = typeControlDict.find(keyword);
    std::cout << keyword << std::endl;
    if (it != typeControlDict.end()) {
        std::string type = it->second;
        if (type == "string") {
            controlDict[keyword] = value;
            return true;
        }
        else if (type == "int") {
            controlDict[keyword] = std::stoi(value);
            return true;
        }
        else if (type == "double") {
            controlDict[keyword] = std::stod(value);
            return true;
        }
        else if (type == "bool") {
            if (value=="yes" or value=="true" or value=="si") {
                controlDict[keyword] = true;
                return true;
            }
            else if (value == "no" or value == "false") {
                controlDict[keyword] = false;
                return true;
            }
            else {
                std::cout << "El keyword "<< keyword << " no tiene un valor invalido." << std::endl;
                return false;    
            }
        }
    }
    return false;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void dictionary::mostrarControlDict() {
    std::cout << "Contents of controlDict:" << std::endl;
    for (const auto& entry : controlDict) {
        std::cout << entry.first << ": ";
        std::visit([](auto&& value) { std::cout << value; }, entry.second);
        std::cout << std::endl;
        // std::cout << entry.first << ": " << entry.second << std::endl;
    }
}

