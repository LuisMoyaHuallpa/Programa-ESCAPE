#ifndef sarsa_H
#define sarsa_H

class sarsa{

private:
    int surviveReward;
    int deadReward;
    int stepReward;
    double discount;
    double alpha;
    
    

public: 
    void update();
    
};

#endif 
