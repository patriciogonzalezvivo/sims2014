//
//  Spring.h
//  Springs
//
//  Created by Charlie Whitney on 11/11/13.
//
//

#pragma once 

#include "ofMain.h"
#include "SpringJoint.h"

class Spring {
  public:
    void set( SpringJoint *_s1, SpringJoint *_s2, float _k, float _restLength );
    void applyForce( ofVec2f force );
    void update();
    void draw();
    
    void connect( Spring *s );
    
    SpringJoint *s1, *s2;
    float   k, restLength;
};