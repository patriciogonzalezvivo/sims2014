//
//  Spring.h
//  03_Particle
//
//  Created by Patricio Gonzalez Vivo on 10/1/14.
//
//

#pragma once

#include "ofMain.h"
#include "Particle.h"

class Spring {
public:
    
    Spring();
    
    void set(Particle * _A, Particle * _B);
    void update();
    void draw();
    
    
    float k;
    float restDist;
    
    Particle * A;
    Particle * B;
    
};