#include "Particle.h"

Particle::Particle() {
    pos.x = ofGetWindowWidth()*0.5;
    pos.y = ofGetWindowHeight()*0.5;
    pos.z = 0.0;
    
    vel.set(0,0,0);
    acc.set(0,0,0);
    
    damp = 0.97; // de resistance!!!
    radius = 3;
}

void Particle::setInit(ofPoint _pos, ofPoint _vel){
    pos = _pos;
    vel = _vel;
    acc.set(0,0,0);
    life = ofRandom(20,60);
}

ofPoint Particle::getPosition(){
    return pos;
}

ofPoint Particle::getVelocity(){
    return vel;
}

float Particle::getRadius(){
    return radius;
}

void Particle::addForce(ofPoint _force){
    acc += _force;
}

void Particle::addRepulsionForce(ofPoint _pos, float _rad, float _scale){
    
    ofPoint diff = _pos - pos;
    if( diff.length() < _rad ){
        diff *= 1.0-diff.length()/_rad;// PRO way
        addForce(-diff*_scale);
    }
}

void Particle::addAttractionForce(ofPoint _pos, float _rad, float _scale){
    ofPoint diff = _pos - pos;
    if( diff.length() < _rad ){
        diff *= 1.0-diff.length()/_rad;
        addForce(diff*_scale);
    }
}

void Particle::addClockwiseForce( ofPoint _pos, float _rad, float _scale){
	ofVec2f diff = pos - _pos;
	
	if (diff.length() < _rad){
		float pct = 1 - (diff.length() / _rad);
		diff.normalize();
		acc.x -= diff.y * pct * _scale;
		acc.y += diff.x * pct * _scale;
	}
}

void Particle::addCounterClockwiseForce( ofPoint _pos, float _rad, float _scale){
	ofVec2f diff = pos - _pos;
	
	if (diff.length() < _rad){
		float pct = 1 - (diff.length() / _rad);
		diff.normalize();
		acc.x += diff.y * pct * _scale;
		acc.y -= diff.x * pct * _scale;
	}
}

void Particle::addFlockingForce(vector<Particle> &_particles, float _neighborhoodRadius, float _alignmentScale, float _separationScale, float _cohesionScale) {
    
    float zoneRadiusSq = _neighborhoodRadius * _neighborhoodRadius;
    
    ofPoint sep;    //  SEPARATION

    ofPoint ali;    //  ALIGNMENT
    int aliCount = 0;

	ofPoint coh;    //  COHESION
    ofPoint posSum;
    int cohCount = 0;
    
    for (int i = 0 ; i < _particles.size() ; i++) {
        if(this != &_particles[i]){
            ofPoint diff = pos - _particles[i].getPosition();
            float lenSq = diff.lengthSquared();
            
            // We only want a boid to act on another boid if it's with zoneRadiusSq.
            // If they aren't within that distance, they are too far away and don't affect each other.
            if( lenSq < zoneRadiusSq ){
            
                //  add separation force
                //
                ofPoint repulse = diff;
                repulse.normalize();
                repulse /= sqrt(lenSq);
                sep += repulse;
                
                //  add align force
                //
                ali += _particles[i].getVelocity();
                aliCount++;
                
                //  add cohesion force
                //
                posSum += _particles[i].getPosition(); // Add location
                cohCount++;
            }
        }
    }
    
    //  Average of Align
    //
    if (aliCount > 0) {
		ali /= (float)aliCount;
		ali.limit(0.1);
    }
    
    //  Average of cohesion
    //
    if (cohCount > 0){
		posSum /= (float)cohCount;
    }
	coh = posSum - pos;
	coh.limit(0.04);
	
    
    //  Apply forces into acc
    //
	acc += ali * _alignmentScale;
	acc += coh * _separationScale;
	acc += sep * _cohesionScale;
}

void Particle::update() {
    
    vel += acc;
    vel *= damp;
    pos += vel;
    acc *= 0.0;
    
    if(tail.size()>0){
        if(pos.distance(tail[tail.size()-1])>2.){
            tail.push_back(pos);
        }
    } else {
        tail.push_back(pos);
    }
    
    if (tail.size() > life) {
//        tail.erase(tail.begin());
        tail.clear();
        setInit(ofPoint(ofRandom(ofGetWidth()),
                        ofRandom(ofGetHeight())));
    }

}

void Particle::bounceOnWall(){
    if( pos.x < 0.0+radius || pos.x > ofGetWidth()-radius ){
        pos.x -= vel.x; // Bounced back! think of this as an undo;
        vel.x *= -1.0;
    }
    
    if( pos.y < 0.0+radius || pos.y > ofGetHeight()-radius ){
        pos.y -= vel.y; // Bounced back! think of this as an undo;
        vel.y *= -1.0;
    }
}

void Particle::infiniteWalls(){
    if( pos.x < 0.0 ){
        pos.x = ofGetWidth()-1;
        tail.clear();
    }
    
    if( pos.x > ofGetWidth()){
        pos.x = 1;
        tail.clear();
    }
    
    if( pos.y < 0){
        pos.y = ofGetHeight()-1;
        tail.clear();
    }
    
    if( pos.y > ofGetHeight()){
        pos.y = 1;
        tail.clear();
    }
}

void Particle::draw() {
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    glVertex3fv(&pos.x);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < tail.size(); i++) {
        float gray = 1.-(float)i/((float)tail.size()-1);
        glColor4f(0,gray,gray,gray*1.5);
        glVertex3fv(&tail[i].x);
    }
    glEnd();
}