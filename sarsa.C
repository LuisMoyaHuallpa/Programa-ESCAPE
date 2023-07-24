#include "sarsa.H"

void sarsa::update() {
    int a = 1;
    q[current_S, current_A] += alpha; 
}
