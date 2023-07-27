#include "transLink.h"
#include "dbLink.h"
#include "dbNode.h"
#include "transLinks.h"
#include <vector>

transLink::transLink() {

    
    
}

transLink::transLink(int idCentralNode, int numberLinksConnection, std::vector<int> idsLinkConnection) {
    setMainNode(idCentralNode); 
    setNumberLinkConnection(numberLinksConnection);
    setIdsLinkConnection(idsLinkConnection);
}

void transLink::setMainNode(int idMainNode){
    (*this).mainNode = dbLink::listaNode.extracionNode(idMainNode);
}
void transLink::setNumberLinkConnection(int numberLinkConnection) {
    (*this).numberLinkConnection = numberLinkConnection;
}
void transLink::setIdsLinkConnection(std::vector<int> idsLinkConnection){
    for (int i = 0; i < numberLinkConnection; i++) {
        link a = transLinks::listaLink.extraccionLink(idsLinkConnection[i]); 
        linkConnection.push_back(a);
    }
}

node transLink::getMainNode() const {
    return mainNode;
}
int transLink::getNumberLinkConnection() const {
    return numberLinkConnection;
}
std::vector<link> transLink::getLinkConnection() const{
    return linkConnection;
}


