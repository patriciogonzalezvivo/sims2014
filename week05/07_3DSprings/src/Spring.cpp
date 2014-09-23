//
//  Spring.cpp
//  A_PTP
//
//  Created by Patricio Gonzalez Vivo on 9/23/14.
//
//

#include "Spring.h"

//---------------------------------------------------------------------
Spring::Spring(){
    particleA = NULL;
    particleB = NULL;
    k = 0.05;
}

Spring::Spring(Particle *_A, Particle *_B, float _springiness){
    particleA = _A;
    particleB = _B;
    k = _springiness;
    restLength = (_A->pos.distance(_B->pos));
}

//---------------------------------------------------------------------
void Spring::update(){
    if ((particleA == NULL) || (particleB == NULL)){
        return;
    }
    
    ofVec3f force = particleA->pos - particleB->pos;  // the direction
    float len = force.length();
    float stretchLength = len - restLength;
    
    force.normalize();
    force *= k * stretchLength;
    
    particleA->addForce(-force*0.5);
    particleB->addForce(force*0.5);
}


//---------------------------------------------------------------------
void Spring::draw(){
    
    if ((particleA == NULL) || (particleB == NULL)){
        return;
    }
    
    ofLine(particleA->pos, particleB->pos);
}