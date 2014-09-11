//
//  Ball.h
//  BouncingBall
//
//  Created by Charlie Whitney on 9/2/13.
//
//

#pragma once

#include "ofMain.h"

class Ball {
public:
    Ball();
    
    void setInit(ofPoint _pos);
    void addForce(ofPoint _force);
    
    void update();
    void draw();
    
    ofPoint pos;
    ofPoint vel;
    ofPoint acc;
    
    float radius;
    float damp;
};