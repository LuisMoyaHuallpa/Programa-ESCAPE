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
std::map<std::string, std::variant<std::string, int, bool>>& dictionary::getControlDict() {
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
        auto it = typeControlDict.find(keyword_str);
        if (it != typeControlDict.end()) {
            std::string type = it->second;
            if (type == "string") {
                controlDict[keyword_str] = value_str;
            }
            else if (type == "int") {
                controlDict[keyword_str] = std::stoi(value_str);
                std::cout << value_str;
            }
            else if (type == "bool") {
                if (value_str == "yes") {
                    controlDict[keyword_str] = true;
                }
                else {
                    controlDict[keyword_str] = false;
                }
            }

        }
    }
    file.close(); 
}
std::variant<std::string, int, bool> dictionary::lookup(std::string keyword) {
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
std::variant<std::string, int, bool> dictionary::lookupDefault(std::string keyword) {
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
std::variant<std::string, int, bool> dictionary::convertToType(const std::string& key, const std::string& value) {
    auto it = typeControlDict.find(key);
    if (it != typeControlDict.end()) {
        const std::string& type = it->second;
        if (type == "string") {
            return value;
        } else if (type == "int") {
            try {
                return std::stoi(value);
            } catch (const std::invalid_argument&) {
                throw std::runtime_error("Invalid integer value for key: " + key);
            }
        } else if (type == "bool") {
            std::string lowerValue = value;
            std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(), ::tolower);
            if (lowerValue == "true") return true;
            if (lowerValue == "false") return false;
            throw std::runtime_error("Invalid boolean value for key: " + key);
        }
    }
    throw std::runtime_error("Unknown type for key: " + key);
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

