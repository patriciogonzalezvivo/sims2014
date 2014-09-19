#pragma once

#include "ofMain.h"

class Particle {
public:
    Particle();
    
    void setInit(ofPoint _pos, ofPoint _vel = ofPoint(0,0));
    
    void addForce(ofPoint _force);
    
    void addRepulsion(Particle *_other, float _scale);
    void addRepulsion(ofPoint &_pos, float _rad, float _scale);
    void addAttraction(ofPoint &_pos, float _rad, float _scale);
    void addClockwiseForce( ofPoint &_pos, float _rad, float _scale);
    void addCounterClockwiseForce( ofPoint &_pos, float _rad, float _scale);
    
    void update();
    void draw(ofImage *_img);

    ofPoint pos;
    ofPoint vel;
    ofPoint acc;

    float radius;
    float damp;
};