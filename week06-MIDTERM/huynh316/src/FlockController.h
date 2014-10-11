/*
 *  FlockController.h
 *  06_Midterm
 *
 *  Created by Julie Huynh on 10/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once 

#include "ofMain.h"
#include "Boid.h"

class FlockController {
public:
    FlockController();
    
    void applyForces( float zoneRadius, float separateThresh=0.4, float alignThresh=0.7 );
    
    void addParticle( int numParticles=1 );
    void update();
    void draw();
    
    vector<Boid>    boidList;
};