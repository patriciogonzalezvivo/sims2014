/*
 *  SpringJoint.h
 *  06_Midterm
 *
 *  Created by Julie Huynh on 10/8/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

//
//  SpringJoint.h
//  Springs
//
//  Base sketch Created by Charlie Whitney on 11/11/13.
//
//

#pragma once

#include "ofMain.h"

class SpringJoint {
public:
    void update();
    void draw();
    void applyForce( ofVec3f force );
    
    ofVec3f pos, vel, acc, targetPos;
	
	//xenos
	void xenoToPoint(float catchX, float catchY);
	
	
	float catchUpSpeed; //take this pct of where i wanna be, +1 catch up of my pos
	
	float radius;
};