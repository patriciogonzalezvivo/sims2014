//
//  Particle.cpp
//  BouncingParticle
//
//  Created by Charlie Whitney on 9/2/13.
//
//

#include "Particle.h"


Particle::Particle() {
    pos.x = ofGetWindowWidth()*0.5;
    pos.y = ofGetWindowHeight()*0.5;
    pos.z = 0.0;
    
    vel.set(0,0,0);
    acc.set(0,0,0);
    
    damp = 0.95; // de resistance!!!
    radius = 5;
}

void Particle::setInit(ofPoint _pos, ofPoint _vel){
    pos = _pos;
    vel = _vel;
    acc.set(0,0,0);
}

void Particle::addForce(ofPoint _force){
    acc += _force;
}

void Particle::addRepulsion(ofPoint _pos, float _rad, float _scale){
    
//    //  if is inside the radius
//    if( pos.distance(_pos) < _rad ){
//        // - calculate de difference
//        ofPoint diff = pos - _pos;
//    
//        // - add like a opposite force
//        addForce(-diff);
//    }
    
    ofPoint diff = _pos - pos;
    if( diff.length() < _rad ){
//        diff *= ofMap(diff.length(),0,_rad,1.0,0.0);  // Easy way
        diff *= 1.0-diff.length()/_rad;// PRO way
        addForce(-diff*_scale);
    }
}

void Particle::addAttraction(ofPoint _pos, float _rad, float _scale){
    ofPoint diff = _pos - pos;
    if( diff.length() < _rad ){
        diff *= 1.0-diff.length()/_rad;
        addForce(diff*_scale);
    }
}

void Particle::update() {
    
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

void Particle::draw() {
    ofCircle(pos, radius);
}