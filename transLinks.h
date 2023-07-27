#ifndef transLinks_h
#define transLinks_h

#include "transLink.h"
#include "dbLink.h"
#include <string>
#include <vector>
#include "fstream"
#include "iostream"
#include "sstream"

class transLinks {
private:
    std::string filename;
    std::vector<transLink> dbTransLinks;

public:
    static dbLink listaLink;
    static void setListaLink(const dbLink & dblink);
    transLinks();
    transLinks(std::string filename);

    void leerTransLinks(std::string filename);
    void mostrarTransLinks();
};
#endif
