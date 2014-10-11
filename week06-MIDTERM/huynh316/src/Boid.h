/*
 *  Boid.h
 *  06_Midterm
 *
 *  Created by Julie Huynh on 10/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class Boid {
public:
    Boid();
    Boid( ofVec3f position, ofVec3f velocity );
    
    void applyForce( ofVec3f force );
    void pullToCenter( ofVec3f center );
    
    void update();
    void draw();
    
    float   damping;
    ofVec3f pos, vel, acc;
};