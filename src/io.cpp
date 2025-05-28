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

#include "io.h"
#include "dictionary.h"
#include "nodeDestino.h"
#include "pedestrians.h"
#include "subLink.h"
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
dirIO::dirIO(const std::string& dirName, const dirIO* directory, const bool checkCreation) :
    dirName(dirName),
    directory(directory),
    fullPath(directory->getFullPath() + dirName + '/')
{
    if (checkCreation) {
        if (!verificarDirExists()) {
            crearDir();
        }
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
const dirIO* const fileIO::getDirectory() const {
    return directory;
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
dirIO io::directoryTime("time", &directoryData, std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained");
// dirIO io::directoryPostprocessing("postprocessing");
// dirIO io::directorySnapshot("snapshot", &directoryPostprocessing);
dirIO io::directoryMedia("media", &directoryData, std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained");
dirIO io::directoryImages("images", &directoryMedia, std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained");
dirIO io::directoryVideos("videos", &directoryMedia, std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained");
dirIO io::directoryStateMatrices("stateMatrices");
fileIO io::fileTotalEvacuatedCount("totalEvacuatedCount", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained", &directoryData);
fileIO io::fileEvacuatedCount("evacuatedCount", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained", &directoryData);
fileIO io::fileActionsDb("actionsdb", "csv", std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")), std::get<bool>(dictionary::get()->lookupDefault("pythonVersion")));
fileIO io::fileTranstionsDb("transitionsdb", "csv", std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")) == "out");
fileIO io::fileStateMatrixPython("stateMatrixPython", "csv", std::get<std::string>(dictionary::get()->lookupDefault("pythonOption")) == "in");
fileIO io::figureTotalEvacuadosVsSimulacion("figureTotalEvacuadosVsSimulacion", "png", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);
fileIO io::figureEvacuadosVsTiempo("figureEvacuadosVsTiempo", "png", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);
fileIO io::tableTotalEvacuadosVsSimulacion("tableTotalEvacuadosVsSimulacion", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);
fileIO io::tableEvacuadosVsTiempo("tableEvacuadosVsTiempo", "csv", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="calibration", &directoryData);
fileIO io::figurePedestrians("figurePedestrians", "png", "out", std::get<std::string>(dictionary::get()->lookupDefault("process"))=="trained", &directoryData);

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
    dirIO* dirTime = new dirIO(std::to_string(tiempo::get()->getValorTiempo()), &directoryTime);
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
            nodeDestino::imprimirVariableTotalPersonasEvacuadas(&cantPedestrianEvacuated);
            delete dirTiempo;
            dirTiempo = nullptr; 
            // archivos de tablas de exportacion
            // imprime personas totales evacuadas
            nodeDestino::imprimirTotalPersonasEvacuadas(&fileTotalEvacuatedCount);
            // imprime personas evacuadas por node evacuacion
            nodeDestino::imprimirNodeEvacuation(&fileEvacuatedCount);
            // imprimir personas en las calles
            std::string nombreArchivo = "Figure-" + std::to_string(tiempo::get()->getValorTiempo()); // O el formato que desees
	    char buf[16];
	    std::snprintf(buf, sizeof(buf), "Figure-%04d", tiempo::get()->getValorTiempo());
            fileIO images(buf, "png", &directoryImages);
            pedestrian::plotearPedestrians(&images);
        }
    }
    // exportacion durante la calibracion
    else if (std::get<std::string>(dictionary::get()->lookupDefault("process")) == "calibration") {
        // imprime data de statematrix cada termino de simulaciont
        // solo lo imprime al final de la evacuacion
        if (tiempo::get()->getValorTiempo() == tiempo::get()->getEndTime() or nodeDestino::verificarEvacuacionTotal()) {
            fileIO stateMatrice(stateMatrixs::get()->creacionFileStateMatrix(), &directoryStateMatrices);
            stateMatrixs::get()->imprimirDbStateMatrixs(&stateMatrice);
            // ploteo mortalidad por simulacion
            nodeDestino::plotearEvacuadosVsTiempo(&figureEvacuadosVsTiempo);
            nodeDestino::imprimirEvacuadosVsTiempo(&tableEvacuadosVsTiempo);
        }
        // ploteo total personas evacuadas por simulacion
        nodeDestino::plotearTotalEvacuadosXSimulacion(&figureTotalEvacuadosVsSimulacion);
        nodeDestino::imprimirTotalEvacuadosXSimulacion(&tableTotalEvacuadosVsSimulacion);
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
