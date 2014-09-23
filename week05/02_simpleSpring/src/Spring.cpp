//
//  Spring.cpp
//  Springs
//
//  Created by Charlie Whitney on 11/11/13.
//
//

#include "Spring.h"

void Spring::set( SpringJoint *_s1, SpringJoint *_s2, float _k, float _restLength ) {
    s1 = _s1;
    s2 = _s2;
    k = _k;
    restLength = _restLength;
}

void Spring::update() {
    // spring action
    ofVec2f force = s1->pos - s2->pos;  // the direction
    float len = force.length();
    float stretchLength = len - restLength;
    force.normalize();
    force *= -1 * k * stretchLength;
    
    s1->applyForce( force );
    s2->applyForce( -force );
}

void Spring::draw() {
    ofLine( s1->pos, s2->pos );
}