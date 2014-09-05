#include "Particle.h"
#include "ofMain.h"


//------------------------------------------------------------
Particle::Particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.09f;
}

//------------------------------------------------------------
void Particle::resetForce(){
    // we reset the forces every frame
    acc.set(0,0);
}

//------------------------------------------------------------
void Particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    acc.x = acc.x + x;
    acc.y = acc.y + y;
}

//------------------------------------------------------------
void Particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    acc.x = acc.x - vel.x * damping;
    acc.y = acc.y - vel.y * damping;
}


//------------------------------------------------------------
void Particle::addRepulsionForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = *this - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		acc.x += diff.x * pct * strength;
		acc.y += diff.y * pct * strength;
	}
	
}

//------------------------------------------------------------
void Particle::addAttractionForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = *this - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		acc.x -= diff.x * pct * strength;
		acc.y -= diff.y * pct * strength;
	}
	
}


//------------------------------------------------------------
void Particle::addClockwiseForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = *this - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		acc.x -= diff.y * pct * strength;
		acc.y += diff.x * pct * strength;
	}
	
}

//------------------------------------------------------------
void Particle::addCounterClockwiseForce( float px, float py, float radius, float strength){
	
	
	ofVec2f posOfForce;
	posOfForce.set(px, py);
	
	ofVec2f diff = *this - posOfForce;
	
	if (diff.length() < radius){
		float pct = 1 - (diff.length() / radius);
		diff.normalize();
		acc.x += diff.y * pct * strength;
		acc.y -= diff.x * pct * strength;
	}
	
}

//------------------------------------------------------------
void Particle::setInitialCondition(float px, float py, float vx, float vy){
    set(px,py);
	vel.set(vx,vy);
}

//------------------------------------------------------------
void Particle::update(){	
	vel += acc;
	*this += vel;
}

//------------------------------------------------------------
void Particle::draw(){
    ofCircle(*this, 3);
}

