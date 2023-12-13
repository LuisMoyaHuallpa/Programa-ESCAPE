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

int action::getIdLink() {
    return idLink;
}
int action::getILinkConnection() {
    return iLinkConnection;
}

bool action::operator==(action stateObject) {
    if (getIdLink() == stateObject.getIdLink()) {
        return true;
    }
    return false;
}
void action::mostrarAction() {
    std::cout << getIdLink()<< " ";
}
void action::imprimirAction(std::fstream& file) {
    // file << get 
}
