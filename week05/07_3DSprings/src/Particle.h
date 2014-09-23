#pragma once

#include "ofMain.h"

class Particle {
public:
    Particle();
    Particle(float _posX, float _posY, float _posZ = 0.0);
    
    void setInit(ofPoint _pos, ofPoint _vel = ofPoint(0,0));
    
    void addForce(ofPoint _force);
    
    void addFlockingForce(vector<Particle> &_particles, float _neighborhoodRadius, float _scaleSep, float _scelAlig, float _scaleCohe);
    
    void addChasingForce(vector<Particle> &_particles, float _radius, float _scale);
    
    void addRepulsion(ofPoint &_pos, float _rad, float _scale);
    void addAttraction(ofPoint &_pos, float _rad, float _scale);
    void addClockwiseForce( ofPoint &_pos, float _rad, float _scale);
    void addCounterClockwiseForce( ofPoint &_pos, float _rad, float _scale);
    
    void checkBorders();
    void infiniteWalls();
    
    void bounceOnBoxWalls(float _size);
    
    void update();
    void draw();

    ofPoint pos;
    ofPoint vel;
    ofPoint acc;

    float radius;
    float damp;
};