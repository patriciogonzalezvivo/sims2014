//
//  Boid.cpp
//  Flocking
//
//  Created by Charlie Whitney on 10/20/13.
//
//

#include "Boid.h"

Boid::Boid() {
    damping = 0.98;
}

Boid::Boid( ofVec3f position, ofVec3f velocity) {
    pos = position;
    vel = velocity;
    damping = 0.98;
}

void Boid::applyForce( ofVec3f force ){
    acc += force;
}

void Boid::pullToCenter( ofVec3f center ){
    
    // if the particles stray too far, we want to pull them back on screen
    
    ofVec3f dir = pos - center;
    float dist = dir.length();
    float maxDistance = 300.0;
    
    if( dir.length() > maxDistance ) {
        dir.normalize();
        vel -= dir * ( ( dist - maxDistance ) * 0.0001f );
    }
}

void Boid::update(){
    vel += acc;
    
    // don't move too fast
    vel.limit(3.0);
    
    // but also don't move too slow!
    if( vel.lengthSquared() < 1.0 ){
        vel = vel.normalized() * 1.0;
    }
    
    pos += vel;
    vel *= damping;
    
    acc.set(0);
}

void Boid::draw(){
    ofSetColor(255);
    ofCircle(pos, 2);
    
    ofSetColor( 255, 0, 0 );
    ofLine( pos, pos - vel*5.0);
    
}