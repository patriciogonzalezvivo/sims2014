//
//  Ball.cpp
//  BouncingBall
//
//  Created by Charlie Whitney on 9/2/13.
//
//

#include "Ball.h"


Ball::Ball() {
    ofSeedRandom();
    
    velocity.x = ofRandom(0.0, 1.0);
    velocity.y = ofRandom(0.0, 1.0);
    
    position.x = ofGetWindowWidth() / 2;
    position.y = ofGetWindowHeight() / 2;
    
    ofSetRectMode( OF_RECTMODE_CENTER );
}

void Ball::update() {
    position.x += velocity.x * 10.0;
    position.y += velocity.y * 10.0;
    
    if( position.x < 0.0 || position.x > ofGetWidth() ){
        velocity.x = velocity.x * -1.0;
    }
    
    if( position.y < 0.0 || position.y > ofGetHeight() ){
        velocity.y = velocity.y * -1.0;
    }
}

void Ball::draw() {
    ofCircle(position, 5);
}