//
//  Spring.cpp
//  03_Particle
//
//  Created by Patricio Gonzalez Vivo on 10/1/14.
//
//

#include "Spring.h"

Spring::Spring(){
    A = NULL;
    B = NULL;
    
    k = 0.5;
}

void Spring::set(Particle * _A, Particle * _B){
    A = _A;
    B = _B;
    
    restDist = A->getPosition().distance(B->getPosition());
}

void Spring::update(){
    
    if(A == NULL || B == NULL ){
        return;
    }

    ofVec3f force = A->pos - B->pos;  // the direction
    float len = force.length();
    float stretchLength = len - restDist;
    
    force.normalize();
    force *= k * stretchLength;
    
    if(A->bFix){
        A->addForce(-force*0.5);
    }
    
    B->addForce(force*0.5);
    
}

void Spring::draw(){
    if(A == NULL || B == NULL ){
        return;
    }
    
    ofLine(A->getPosition(),B->getPosition());
}