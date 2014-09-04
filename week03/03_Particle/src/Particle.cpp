#include "Particle.h"


//------------------------------------------------------------
Particle::Particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.01f;
}

//------------------------------------------------------------
void Particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void Particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    acc.x = acc.x + x;
    acc.y = acc.y + y;
}

//------------------------------------------------------------
void Particle::update(){	
	vel = vel + acc;
    vel = vel * (1.0-damping);
	pos = pos + vel;
    acc *= 0.0;
}

//------------------------------------------------------------
void Particle::draw(){
    ofCircle(pos, 5);
}

