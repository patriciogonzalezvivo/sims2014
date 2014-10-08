#pragma once

#include "ofMain.h"

class Particle {
public:
    Particle();
    
    void setInit(ofPoint _pos, ofPoint _vel = ofPoint(0,0));
    
    float   getRadius();
    ofPoint getPosition();
    ofPoint getVelocity();
    
    void    addForce(ofPoint _force);
    
    void    addRepulsionForce(ofPoint _pos, float _rad, float _scale);
    void    addAttractionForce(ofPoint _pos, float _rad, float _scale);
    void    addClockwiseForce( ofPoint _pos, float _rad, float _scale);
    void    addCounterClockwiseForce( ofPoint _pos, float _rad, float _scale);
    
    void    addNoise(float _angle, float _turbulence);
    void	applyFlockingForce(ofPoint *_offSet, float _neighbordhood, float _independece, float _scale);
    void    applyAttractionToNodes(float _pct);
    
    void    update(float _speed);
    void    draw();
    
    ofPoint localOffset;
    
    ofPoint pos;
    ofPoint vel;
    ofPoint acc;
    
    float radius;
};