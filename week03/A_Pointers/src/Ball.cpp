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
    
    xVelocity = ofRandom(0.0, 1.0);
    yVelocity = ofRandom(0.0, 1.0);
    
    position.x = ofGetWindowWidth() / 2;
    position.y = ofGetWindowHeight() / 2;
    
    ofSetRectMode( OF_RECTMODE_CENTER );
}

void Ball::update() {
    position.x += xVelocity * 10.0;
    position.y += yVelocity * 10.0;
    
    if( position.x < 0.0 || position.x > ofGetWidth() ){
        xVelocity = xVelocity * -1.0;
    }
    
    if( position.y < 0.0 || position.y > ofGetHeight() ){
        yVelocity = yVelocity * -1.0;
    }
}

void Ball::draw() {
    ofCircle(position.x, position.y, 5, 5);
}