#ifndef transLinks_h
#define transLinks_h

#include <string>
#include <vector>
#include "fstream"
#include "iostream"
#include "sstream"
#include "transLink.h"


class transLinks {
private:
    std::string filename;
    std::vector<transLink> dbTransLink;
    
public:
    static links listaLink;
    static void setListaLink(const links & dblink);

    transLinks();
    transLinks(std::string filename);

    void leerTransLinks(std::string filename);
    void mostrarTransLinks();
};
#endif
