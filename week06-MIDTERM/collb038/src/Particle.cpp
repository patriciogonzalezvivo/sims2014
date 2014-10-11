
#include "Particle.h"
#include "Tail.h"

Particle::Particle() {
    pos.x = ofGetWindowWidth()*0.5;
    pos.y = ofGetWindowHeight()*0.5;
    pos.z = 0.0;

    vel.set(0,0,0);
    acc.set(0,0,0);

    radius = 3;
    step = 0;

}

void Particle::setInit(ofPoint _pos, ofPoint _vel){
    pos = _pos;
    vel=_vel;

    rotSeed = ofRandomf()*50;

    breakCounter = 0;

    velMag;
    ofPoint velToColor = getVelocity();
    velMag = velToColor.length();

    colorMap = ofMap(velMag,0,4, 255,0, true);

    if (velMag > 2) {
        isLeaf = true;
    } else {
        isLeaf = false;
    }

    breakPoint = getBreakPoint()*getBreakPoint()*0.1;

    tailWidth = ofRandom(1,3);

}

float Particle::getBreakPoint() {

    /*
    float breakMin=90;
    float breakMax=180;
    while (true) {
        float breakVar = ofRandom(breakMin,breakMax);
        if (breakVar > ofRandom(breakMin,breakMax) && breakVar < ofRandom(breakMin,breakMax)){
            return breakVar;
        }
    }*/

    float mean = 50;
    float gaussian = ofxGaussian();
    float sd = 6;
    float breakVar = ((sd * gaussian) + mean);
    //breakVar *= breakVar*0.01;
    return breakVar;

}

//Thanks to Darren Mothersele for this Gaussian distribution code

float Particle::ofxGaussian() {
    if (haveNextNextGaussian){
        haveNextNextGaussian = false;
        return nextNextGaussian;
  }
  else {
    float v1, v2, s;
    do {
      v1 = 2 * ofRandomf() - 1;
      v2 = 2 * ofRandomf() - 1;
      s = v1 * v1 + v2 * v2;
    }
    while (s >= 1 || s == 0);

    float multiplier = sqrt(-2 * log(s)/s);
    nextNextGaussian = v2 * multiplier;
    haveNextNextGaussian = true;

    return v1 * multiplier;
  }
}

void Particle::update() {

    vel += acc;
    pos += vel;
    acc *= 0.0;

    breakCounter++;

    Tail newTail;
    newTail.setInit(ofPoint(pos.x,pos.y),tailVary,tailWidth,colorMap);

    tail.push_back(newTail);

    if (tail.size() > 100) {
        tail.erase(tail.end());
    }
}

void Particle::draw(int _colState, float _colMult) {

    int colorState = _colState;
    float colorMult = _colMult;

    int r,g,b;

    float windForce = ofRandom(0.4,0.8);
    float gravForce = ofRandom(0.1,0.4);
//ofSeedRandom(10);
    if (vel.length() < 2 && breakCounter <= breakPoint){
         ofRotate(sin((ofGetFrameNum() + rotSeed)*0.001)*ofRandom(-2,2));  //+1
            /*
            if (vel.y < 0) {
        ofRotate(sin((ofGetFrameNum() + rotSeed)*0.001));//+1//*ofRandom(-2,2));
            } else if (vel.y > 0) {
        ofRotate((cos((ofGetFrameNum() + rotSeed)*0.001)));//*ofRandom(-2,2));
            }
            */
    }
    /*
    else if (breakCounter > breakPoint) {
    ofPushMatrix();
    ofTranslate(tail[tail.size()/2].pos);
    step ++;

    ofRotate(step);

    } */

    for (int i = 0; i < tail.size(); i++){

        if (breakCounter >= breakPoint){
            tail[i].addWind(windForce);

            //RADIATION FLOWER:
            /*
            if (ofRandomf() >= 0){
                tail[i].addWind(windForce);
            } else if (ofRandomf() < 0) {
                tail[i].addGravity(ofRandom(0.1,0.4));
            }
            */
        }

        tail[i].update();


        if (colorState % 3 == 1){
            if (isLeaf == false) {
                r = colorMap-(i*0.5);
                g = (colorMap*0.3)-((tail.size()-i)*0.8);
                b = (colorMap*0.6)-((tail.size()-i)*0.5);
            } else {
                r = colorMap-(i*0.4);
                g = colorMap-(i*0.4);
                b = (colorMap*0.6)-((tail.size()-i)*0.8);
            }
        } else if (colorState %3 == 2){
            if (isLeaf == false) {
                r = colorMap-(i*0.1);
                g = colorMap-(i*0.6);
                b = (colorMap*0.6)-((tail.size()-i)*0.8);
            } else {
                r = (colorMap*0.3)-((tail.size()-i)*0.5);
                g = (colorMap*0.8)-((tail.size()-i)*0.8);
                b = colorMap-(i*0.7);
            }
        } else if (colorState % 3 == 0){
                r = (colorMap*0.3)-((tail.size()-i)*0.5);
                g = (colorMap*0.8)-((tail.size()-i)*0.8);
                b = colorMap-(i*0.5);
        }

        /*
        if (colorState == 0){
            r = colorMap-(i*0.5);
            g = (colorMap*0.3)-((tail.size()-i)*0.8);
            b = (colorMap*0.6)-((tail.size()-i)*0.5);
        } else if (colorState == 1){
            r = colorMap-(i*0.4);
            g = colorMap-(i*0.6);
            b = (colorMap*0.6)-((tail.size()-i)*0.8);
        } else if (colorState == 2){
            r = (colorMap*0.3)-((tail.size()-i)*0.5);
            g = (colorMap*0.8)-((tail.size()-i)*0.8);
            b = colorMap-(i*0.5);
        }
        */

        ofSetColor(r,g,b,70);

        tail[i].draw(ofRandom(20),(tail.size()-i)*i*0.03);
    }

}


float Particle::getPetalLoc(){
    float minTailX = ofGetWidth();

    for (int i = 0; i < tail.size(); i++) {

        ofPoint tailPos = tail[i].getPosition();
        if (tailPos.x < minTailX) {
            minTailX = tailPos.x;
        } else {
        minTailX = minTailX;
        }

    }
    return minTailX;
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



void Particle::addWindForce(){
    //float waveSpeed;
    //waveSpeed = ofMap(_heading, -4,2, 0.5,2);
    vel.y += ofRandom(0.1,0.3);
    vel.x = sin((ofGetFrameNum()+ofRandomuf()*10));
}


/*

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

float Particle::getHeading() {
    float heading = atan2(vel.y,vel.x)-PI/2;
    return heading;
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
    }

    if( pos.x > ofGetWidth()){
        pos.x = 1;
    }

    if( pos.y < 0){
        pos.y = ofGetHeight()-1;
    }

    if( pos.y > ofGetHeight()){
        pos.y = 1;
    }
}
*/
