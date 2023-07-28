#ifndef transLink_h
#define transLink_h

#include "node.h"
#include "link.h"
#include <vector>
#include "dbLink.h"

class transLink {

private:
    node mainNode;
    int numberLinkConnection;
    /* mejorar nombre de esta clase no queda claro */
    std::vector<link> linkConnection;

public:
    transLink();
    transLink(int idCentralNode, int numberLinksConnection, std::vector<int> idsLinkConnection);
    void setMainNode(int idMainNode);
    void setNumberLinkConnection(int numberLinkConnection);
    void setIdsLinkConnection(std::vector<int> idsLinkConnection);

    node getMainNode() const;
    int getNumberLinkConnection() const;
    std::vector<link> getLinkConnection() const;
};
#endif
