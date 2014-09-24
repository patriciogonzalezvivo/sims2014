//
//  Particle.h
//  VectorField
//
//  Created by Charlie Whitney on 10/7/13.
//
//

#pragma once

#include "ofMain.h"

class Particle {
  public:
    Particle();
    
    ofVec3f pos;
    ofVec3f vel;
    ofVec3f accel;
    float mass;
    
    void applyForce( ofVec3f force );
    void update();
    void draw();
};