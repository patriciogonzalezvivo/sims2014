#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class Particle {
public:
    
    Particle();
    virtual ~Particle(){};
    
    void resetForce();
    void addForce(float x, float y);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addAttractionForce(float x, float y, float radius, float scale);
    void addRepulsionForce(Particle &p, float radius, float scale);
    void addAttractionForce(Particle &p, float radius, float scale);
    
    void addDampingForce();
    
    void setInitialCondition(float px, float py, float vx, float vy);
    void update();
    void draw();
	
    void bounceOffWalls();
	
    float damping;

protected:
private:
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
};

#endif // PARTICLE_H
