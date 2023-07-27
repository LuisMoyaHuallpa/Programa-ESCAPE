#ifndef pedestrian_h
#define pedestrian_h

#include "node.h"

class pedestrian {
private:
    int id;
    int edad;
    int hhType;
    int hhId;
    node nearNode;

    

public:
<<<<<<< HEAD
    static int surviveReward;
    static int deadReward;
    static int stepReward;
=======
    static const int surviveReward;
    static const int deadReward;
    static const int stepReward;
>>>>>>> 4d6f88e (lectura de transLink)

    
    pedestrian();
    pedestrian(int id, int edad, int hhType, int hhId, int idNearNode);

    /* setters */
    void setId(int id);
    void setEdad(int edad);
    void setHHType(int hhType);
    void setHHId(int hhId);
    void setIdNearNode(int idNearNode);

    int getId() const;
    int getEdad() const;
    int getHHType() const;
    int getHHId() const;
    node getNearNode() const;
    
    
    
};

#endif
