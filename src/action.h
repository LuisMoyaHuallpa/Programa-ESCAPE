#ifndef action_h
#define action_h

#include "vector"
#include <vector>

class action {

private:
    
    int idNode;
    int numberAction;
    std::vector<int> actions;

public:
    action();
    action(int idNode);

    void setIdNode(int idNode);
    void setNumberActions(int numberAction);
    void setActions(std::vector<int> actions);

    int getNumberAction();
    std::vector<int> getActions(); 

    void calcularNumberAction();

    
};
#endif
