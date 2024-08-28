#include "io.h"
#include "nodeEvacuation.h"
#include "pedestrians.h"
#include "tiempo.h"
#include "stateMatrixs.h"
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
    dirNamePwd(dirName + '/'),
    directory(nullptr)
{
    if (!verificarDirExists()) {
        crearDir();
    }
}
dirIO::dirIO(const std::string& dirName, const dirIO* directory) :
    dirName(dirName),
    directory(directory),
    dirNamePwd(directory->getDirNamePwd() + dirName + '/')
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
const std::string dirIO::getDirNamePwd() const {
    return dirNamePwd;
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
        std::string dir = directory->dirNamePwd + dirName.c_str();
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
    fileNameCsv(fileName + ".csv"),
    fileNamePwd(fileName),
    directory(nullptr)
{
    crearFile();
}

fileIO::fileIO(const std::string& fileName,const dirIO* directory) :
    fileName(fileName),
    fileNameCsv(fileName + ".csv"),
    directory(directory),
    fileNamePwd(directory->getDirNamePwd() + fileName)
{
    crearFile();
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const std::string fileIO::getFileName() const {
    return fileName;
}
const std::string fileIO::getFileNamePwd() const {
    return fileNamePwd;
}
std::fstream& fileIO::getFileFstream() {
    return fileFstream; 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void fileIO::crearFile() {
    
    fileFstream.open(fileNamePwd, std::ios::out);
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

dirIO io::directoryData("data");
dirIO io::directoryPostprocessing("postprocessing");
dirIO io::directorySnapshot("snapshot", &directoryPostprocessing);
dirIO io::directoryStateMatrices("stateMatrices");
fileIO io::fileTotalEvacuatedCount("totalEvacuatedCount", &directoryData);
fileIO io::fileEvacuatedCount("evacuatedCount", &directoryData);
fileIO io::figureTotalEvacuadosXSimulacion("figureTotalEvacuadosXSimulacion", &directoryData);
fileIO io::figureMortalidadXSimulacion("figureMortalidadXSimulacion", &directoryData);

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
    mkdir(dirTime->getDirNamePwd().c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    return dirTime;
}
void io::imprimirOutput() {
    /* manejo de las output*/
    // exportacion cuando esta entrenado
    if (std::get<std::string>(dictionary::get()->lookup("sarsaProcesses")) == "trained") {
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
    else if (std::get<std::string>(dictionary::get()->lookup("sarsaProcesses")) == "calibration") {
        // imprime data de statematrix cada termino de simulaciont
        // solo lo imprime al final de la evacuacion
        if (tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime()) {
            fileIO stateMatrice(stateMatrixs::get()->creacionFileStateMatrix(), &directoryStateMatrices);
            stateMatrixs::get()->imprimirDbStateMatrixs(&stateMatrice);
        }
        // ploteo total personas evacuadas por simulacion
        nodeEvacuation::plotearTotalEvacuadosXSimulacion(&figureTotalEvacuadosXSimulacion);
    }
}
