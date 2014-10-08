#include "Particle.h"

Particle::Particle() {
    pos.x = ofGetWindowWidth()*0.5;
    pos.y = ofGetWindowHeight()*0.5;
    pos.z = 0.0;
    
    vel.set(0,0,0);
    acc.set(0,0,0);
    
    localOffset.set(ofRandom(-1.0f,1.0f),ofRandom(-1.0f,1.0f),ofRandom(-1.0f,1.0f));

    radius = 1;
}

void Particle::setInit(ofPoint _pos, ofPoint _vel){
    pos = _pos;
    vel = _vel;
    acc.set(0,0,0);
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

void Particle::addNoise(float _angle, float _turbulence){

    float angle = ofSignedNoise( pos.x * 0.005f, pos.y * 0.005f) * _angle;
    ofPoint noiseVector( cos( angle ), sin( angle ) );
    acc += noiseVector * _turbulence;
}

void Particle::applyFlockingForce(ofPoint * _offset, float _neighbordhood, float _independece, float _scale){
    addForce( ofVec3f(ofSignedNoise(pos.x / _neighbordhood + _offset->x + localOffset.x * _independece,
                                    pos.y / _neighbordhood,
                                    pos.z / _neighbordhood),
                      ofSignedNoise(pos.x / _neighbordhood,
                                    pos.y / _neighbordhood + _offset->y  + localOffset.y * _independece,
                                    pos.z / _neighbordhood),
                      ofSignedNoise(
                                    pos.x / _neighbordhood,
                                    pos.y / _neighbordhood,
                                    pos.z / _neighbordhood + _offset->z + localOffset.z * _independece)) * _scale );
}

void Particle::update(float _speed){
    
    vel += acc;
    vel *= _speed;
    pos += vel;
    acc *= 0.0;

}

void Particle::draw() {
    glVertex3f(pos.x,pos.y,pos.z);
}