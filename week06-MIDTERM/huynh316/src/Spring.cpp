/*
 *  Spring.cpp
 *  06_Midterm
 *
 *  Created by Julie Huynh on 10/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */


#include "Spring.h"

void Spring::set( SpringJoint *_s1, SpringJoint *_s2, float _k, float _restLength ) {
    s1 = _s1;
    s2 = _s2;
    k = _k;
    restLength = _restLength;

	//xenos	
//	catchUpSpeed = 0.04f;
}

void Spring::update() {
    // spring action
    ofVec3f force = s1->pos - s2->pos;  // the direction
    float len = force.length();
    float stretchLength = len - restLength;
    force.normalize();
    force *= -1 * k * stretchLength;
    
    s1->applyForce( force );
    s2->applyForce( -force );
}

void Spring::draw() {
	ofSetColor(ofColor::lightBlue);
    ofLine( s1->pos, s2->pos );
}


