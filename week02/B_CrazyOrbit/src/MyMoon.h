//
//  MyMoon.h
//  A_Orbit
//
//  Created by Patricio Gonzalez Vivo on 9/3/14.
//
//

#pragma once

#include "ofMain.h"

class MyMoon : public ofPoint {
public:
    
    void set(float _dist, float _intAngle);
    
    void update(ofPoint _center);
    
    void draw();
    
    float radius;
    float angle;
    
    vector< ofPoint > tail;
};