//
//  Spring.h
//
//  Created by Patricio Gonzalez Vivo on 9/23/14.
//
//

#pragma once

#include "particle.h"

class Spring {
public:
    
    Spring();
    Spring(Particle *_A, Particle *_B, float _k = 0.05);
    
    Particle * particleA;
    Particle * particleB;
    
    float restLength;
    float k;            // springiness constant
    
    void update();
    void draw();
};