//
//  MyMoon.cpp
//  A_Orbit
//
//  Created by Patricio Gonzalez Vivo on 9/3/14.
//
//

#include "MyMoon.h"

void MyMoon::set(float _dist, float _intAngle){
    radius =_dist;
    angle = _intAngle;
}

void MyMoon::update(float _step, ofPoint _center){
    angle += _step;
    
    x = _center.x + radius * cos(angle);
    y = _center.y + radius * sin(angle);
}

void MyMoon::draw(){
    ofSetColor(ofColor::red);
    
    ofCircle(*this, 10);
}