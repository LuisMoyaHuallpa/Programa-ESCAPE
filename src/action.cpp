#include "action.h"
#include <iostream>

action::action() {
    setIdLink(0);
    setILinkConnection(2);
}
action::action(int idLink) {
    setIdLink(idLink); 
}
action::action(int idLink, int iLinkConnection) {
    setIdLink(idLink); 
    setILinkConnection(iLinkConnection);
}

void action::setIdLink(int idLink) {
    (*this).idLink = idLink; 
}
void action::setILinkConnection(int iLinkConnection) {
    (*this).iLinkConnection = iLinkConnection;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// getters
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int action::getIdLink() const {
    return idLink;
}
int action::getILinkConnection() const {
    return iLinkConnection;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// metodos
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool action::operator==(action state2) {
    if (idLink == state2.getIdLink()) {
        return true;
    }
    return false;
}
void action::mostrarAction() const {
    std::cout << iLinkConnection<< " ";
    std::cout << idLink<< " ";
}
void action::imprimirAction(std::fstream& file) {
    // file << get 
}
