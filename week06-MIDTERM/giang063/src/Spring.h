//
//  Spring.h
//  Springs
//
//  Created by Charlie Whitney on 11/11/13.
//
//

#pragma once

#include "ofMain.h"
#include "Particle.h"

class Spring {
public:
    void set( Particle *_s1, Particle *_s2, float _k, float _restLength );
    void applyForce( ofPoint force );
    void update();
    void draw();
    
    void connect( Spring *s );
    
    Particle *s1, *s2;
    float   k, restLength;
};