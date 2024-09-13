#include "io.h"
#include "dictionary.h"
#include "nodeEvacuation.h"
#include "pedestrians.h"
#include "tiempo.h"
#include "stateMatrixs.h"
#include <ios>
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                  dirIO
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dirIO::dirIO(const std::string& dirName) :
    dirName(dirName),
    directory(nullptr),
    fullPath(dirName + '/')
{
    if (!verificarDirExists()) {
        crearDir();
    }
}
dirIO::dirIO(const std::string& dirName, const dirIO* directory) :
    dirName(dirName),
    directory(directory),
    fullPath(directory->getFullPath() + dirName + '/')
{
    if (!verificarDirExists()) {
        crearDir();
    }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const std::string dirIO::getDirName() const {
    return dirName;
}
const std::string dirIO::getFullPath() const {
    return fullPath;    
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void dirIO::crearDir() {
    // permisos del directorio S_ para ejecutar, leer y escribir
    if (directory == nullptr) {
        mkdir(dirName.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
    else {
        std::string dir = directory->fullPath + dirName.c_str();
        mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    }
}
bool dirIO::verificarDirExists() const{
    struct stat info;
    if (stat(dirName.c_str(), &info) != 0) {
        // No se pudo acceder al directorio (puede que no exista)
        return false;
    } else if (info.st_mode & S_IFDIR) {
        // Existe y es un directorio
        return true;
    } else {
        // Existe pero no es un directorio
        return false;
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                fileIO
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
fileIO::fileIO(const std::string& fileName) :
    fileName(fileName),
    fullPath(fileName),
    directory(nullptr)
{
    crearFile();
}
fileIO::fileIO(const std::string& fileName, const bool checkFile) :
    fileName(fileName),
    fullPath(fileName),
    directory(nullptr)
{
    // solo crear si checkFile es true
    if (checkFile) {
        crearFile();
    }
}
fileIO::fileIO(const std::string& fileName, const std::string extension,const bool checkFile) :
    fileName(fileName),
    fullPath(fileName + "." +  extension),
    directory(nullptr)
{
    // solo crear si checkFile es true
    if (checkFile) {
        crearFile();
    }
}
fileIO::fileIO(const std::string& fileName,  const std::string extension, const std::string& inoutStr, const bool checkFile) :
    fileName(fileName),
    fullPath(fileName + "." +  extension),
    directory(nullptr)
{
    std::cout << fileName << std::endl;
    // solo crear si checkFile es true
    if (checkFile) {
        openFile(inoutFile(inoutStr));
    }
}
fileIO::fileIO(const std::string& fileName,const dirIO* directory) :
    fileName(fileName),
    directory(directory),
    fullPath(directory->getFullPath() + fileName)
{
    crearFile();
}
fileIO::fileIO(const std::string& fileName,const std::string extension, const dirIO* directory) :
    fileName(fileName),
    directory(directory),
    fullPath(directory->getFullPath() + fileName + "." + extension)
{
    crearFile();
}
fileIO::fileIO(const std::string& fileName,  const std::string extension, const std::string& inoutStr, const bool checkFile, const dirIO* directory) :
    fileName(fileName),
    directory(directory),
    fullPath(directory->getFullPath() + fileName + "." + extension)
{
    // solo crear si checkFile es true
    if (checkFile) {
        openFile(inoutFile(inoutStr));
    }
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const std::string fileIO::getFileName() const {
    return fileName;
}
std::fstream& fileIO::getFileFstream() {
    return fileFstream; 
}
const std::string fileIO::getFullPath() const {
    return fullPath;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void fileIO::crearFile() {
    fileFstream.open(fullPath, std::ios::out);
}
void fileIO::openFile(const std::ios_base::openmode& inout) {
    fileFstream.open(fullPath, inout);
}
std::ios_base::openmode fileIO::inoutFile(const std::string& inout) {
    if (inout == "in") {
        return std::ios::in;    
    }
    else if (inout == "out") {
        return std::ios::out;
    }
    else {
        throw std::runtime_error("No se pudo abrir el archivo: ");
    }
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//                                io
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static member
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
io* io::ioInstance = nullptr;

size_t io::tamanoElementosIO = 10;
dirIO io::directoryData("data");
dirIO io::directoryPostprocessing("postprocessing");
dirIO io::directorySnapshot("snapshot", &directoryPostprocessing);
dirIO io::directoryStateMatrices("stateMatrices");
fileIO io::fileTotalEvacuatedCount("totalEvacuatedCount", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained", &directoryData);
fileIO io::fileEvacuatedCount("evacuatedCount", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained", &directoryData);
fileIO io::fileActionsDb("actionsdb", "csv", std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")), std::get<bool>(dictionary::get()->lookupDefault("pythonVersion")));
fileIO io::fileTranstionsDb("transitionsdb", "csv", std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")) == "out");
fileIO io::figureTotalEvacuadosXSimulacion("figureTotalEvacuadosXSimulacion", "png", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);
fileIO io::fileTotalEvacuadosXSimulacion("totalEvacuadosXSimulacion", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);
fileIO io::figureMortalidadXSimulacion("figureMortalidadXSimulacion", "png", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);
fileIO io::fileMortalidadXSimulacion("mortalidadXSimulacion", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// constructor
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
io::io() {
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// static getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
io* io::get() {
    /* si aun no existe crea la unica instancia de nodes*/
    if (!ioInstance) {
        ioInstance =  new io();
    }
    return ioInstance;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// std::fstream& io::getFileEvacuatedCount() {
//     return fileTotalPersonasEvacuadas;
// }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dirIO* io::crearCarpetaTiempo() {
    /* Crea carpetas de cada tiempo de evacuacion*/
    dirIO* dirTime = new dirIO(std::to_string(tiempo::get()->getValorTiempo()), &directoryData);
    // crear carpeta de los tiempos en segundos para almacenar informacion
    mkdir(dirTime->getFullPath().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return dirTime;
}
void io::imprimirOutput() {
    /* manejo de las output*/
    // exportacion cuando esta entrenado
    if (std::get<std::string>(dictionary::get()->lookupDefault("process")) == "trained") {
        if (tiempo::get()->verificarGraphicPrintoutPeriod()) {
            // crear carpetas de tiempo
            dirIO* dirTiempo = crearCarpetaTiempo();
            // imprimir datos de personas: posicion y velocidad
            fileIO xy("xy", dirTiempo);
            fileIO U("U", dirTiempo);
            pedestrians::get()->imprimirPedestrians(&xy, &U);
            // imprimir datos de personas: cantidad de personas evacuadas
            fileIO cantPedestrianEvacuated("cantPedestrianEvacuated", dirTiempo);
            nodeEvacuation::imprimirVariableTotalPersonasEvacuadas(&cantPedestrianEvacuated);
            delete dirTiempo;
            dirTiempo = nullptr; 
            // archivos de tablas de exportacion
            // imprime personas totales evacuadas
            nodeEvacuation::imprimirTotalPersonasEvacuadas(&fileTotalEvacuatedCount);
            // imprime personas evacuadas por node evacuacion
            nodeEvacuation::imprimirNodeEvacuation(&fileEvacuatedCount);
        }
    }
    // exportacion durante la calibracion
    else if (std::get<std::string>(dictionary::get()->lookupDefault("process")) == "calibration") {
        // imprime data de statematrix cada termino de simulaciont
        // solo lo imprime al final de la evacuacion
        if (tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime()) {
            fileIO stateMatrice(stateMatrixs::get()->creacionFileStateMatrix(), &directoryStateMatrices);
            stateMatrixs::get()->imprimirDbStateMatrixs(&stateMatrice);
            // ploteo mortalidad por simulacion
            nodeEvacuation::plotearMortalidadXSimulacion(&figureMortalidadXSimulacion);
            nodeEvacuation::imprimirMortalidadXSimulacion(&fileMortalidadXSimulacion);
        }
        // ploteo total personas evacuadas por simulacion
        nodeEvacuation::plotearTotalEvacuadosXSimulacion(&figureTotalEvacuadosXSimulacion);
        nodeEvacuation::imprimirTotalEvacuadosXSimulacion(&fileTotalEvacuadosXSimulacion);
        // imprimir actionDb
        if (std::get<bool>(dictionary::get()->lookupDefault("pythonVersion")) == true and std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")) == "out") {
            // cuando este numero de simulacion 1 y sea final de la evacuacion
            if (tiempo::get()->getINumberSimulation() == tiempo::get()->getStartNumberSimulation()
            and tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime()) {
                nodes::get()->imprimirActionsDb(fileActionsDb.getFileFstream());
                nodes::get()->imprimirTransitionsDb(fileTranstionsDb.getFileFstream());
            }
        }
    }
}
