/*
 *  SpringJoint.cpp
 *  06_Midterm
 *
 *  Created by Julie Huynh on 10/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include "SpringJoint.h"


void SpringJoint::applyForce(ofVec3f force) {
    acc += force;
	
	//xenos
	catchUpSpeed = 0.05f;
}

void SpringJoint::update() {
//    vel += acc;
//    pos += vel;
//    
//    vel *= 0.95;
//    
//    acc.set(0);
}

void SpringJoint::draw() {
	ofSetColor(ofColor::orange);
    ofCircle( pos, 10 );
}

void SpringJoint::xenoToPoint(float catchX, float catchY){
	vel += acc;
    pos += vel;
    
    vel *= 0.95;
    
    acc.set(0);
	
	pos.x = catchUpSpeed * catchX + (1-catchUpSpeed) * pos.x; 
	pos.y = catchUpSpeed * catchY + (1-catchUpSpeed) * pos.y;
	
}