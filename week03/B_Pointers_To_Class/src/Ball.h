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
    
    void update();
    void draw();
    
    ofPoint position;
    float xVelocity;
    float yVelocity;
};