#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class Particle{
public:
	
    Particle();
    
    void setInitialCondition(float px, float py, float vx, float vy);
    
    void addForce(float x, float y);
    void resetForce();
    
    void update();
    void bounceOffWalls();
    
    void draw();
	
    float damping;
    
private:
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f acc;
};

#endif // PARTICLE_H
