//
//  Ball.cpp
//  BouncingBall
//
//  Created by Charlie Whitney on 9/2/13.
//
//

#include "Ball.h"


Ball::Ball() {
    pos.x = ofGetWindowWidth()*0.5;
    pos.y = ofGetWindowHeight()*0.5;
    pos.z = 0.0;
    
    vel.set(0,0,0);
    acc.set(0,0,0);
    
    damp = 0.9; // de resistance!!!
    radius = 10;
}

void Ball::setInit(ofPoint _pos){
    pos = _pos;
    vel.set(0,0,0);
    acc.set(0,0,0);
}

void Ball::addForce(ofPoint _force){
    acc += _force;
}

void Ball::update() {
    
    vel += acc;
    vel *= damp;
    pos += vel;
    acc *= 0.0;
    
    if( pos.x < 0.0+radius || pos.x > ofGetWidth()-radius ){
        pos.x -= vel.x; // Bounced back! think of this as an undo;
        vel.x *= -1.0;
    }
    
    if( pos.y < 0.0+radius || pos.y > ofGetHeight()-radius ){
        pos.y -= vel.y; // Bounced back! think of this as an undo;
        vel.y *= -1.0;
    }
}

void Ball::draw() {
    ofCircle(pos, radius);
}