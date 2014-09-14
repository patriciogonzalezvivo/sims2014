//
//  Boid.h
//  Flocking
//
//  Created by Charlie Whitney on 10/20/13.
//
//

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