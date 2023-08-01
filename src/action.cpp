#include "action.h"
#include <iostream>
#include <vector>
// #include "dbLink.h"

action::action() {
    (*this).idNode = 0;
    (*this).numberAction = 0;
}
action::action(int idNode) {
    (*this).idNode = idNode;
}

void action::setNumberActions(int numberAction){
    (*this).numberAction = numberAction;
}
void action::setActions(std::vector<int> actions){
    (*this).actions = actions;
}

int action::getNumberAction(){
    return numberAction;
}
std::vector<int> action::getActions(){
    return actions;
}

void action::calcularNumberAction() {
    // () dbLink::listaNode.extracionNode(idNode);

    // idNode;
    
}
