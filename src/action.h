#ifndef action_h
#define action_h

#include "iostream"

class action {
private:
    int idLink;
    int iLinkConnection;
public:
    action();
    action(int idLink);
    action(int idLink, int iLinkConnection);

    void setIdLink(int idLink);
    void setILinkConnection(int iLinkConnection);

    int getIdLink();
    int getILinkConnection();

    bool operator==(action actionObject);
    void mostrarAction();
    void imprimirAction(std::fstream& file);
    
    
    
};

#endif
