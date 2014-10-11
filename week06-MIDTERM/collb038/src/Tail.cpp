#include "Tail.h"

Tail::Tail()
{
    pos.x = ofGetWindowWidth()*0.5;
    pos.y = ofGetWindowHeight()*0.5;
    pos.z = 0.0;
    vel.set(0,0,0);
    acc.set(0,0,0);

}

void Tail::setInit(ofPoint _pos,ofColor _blueVary,float _tailRad,int _tailCol) {
    pos = _pos;
    tailCol = _tailCol;
    tailRad = _tailRad;

}

void Tail::update() {
    vel += acc;
    pos += vel;
    //acc *= 0.0;


}

void Tail::addWind(float _windSpeed) {
    //if (ofGetFrameNum()>90){
            acc.x += _windSpeed;
            acc.y += sin(ofGetFrameNum()*1);

}

void Tail::addGravity(float _gravity) {
    //if (ofGetFrameNum()>90){
            acc.y += _gravity;
            acc.x += sin(ofGetFrameNum()*1);

        //FLOWER GO BOOM
        //pos.x*=ofRandom(1,1.3);
        //pos.y*=ofRandom(1,1.1);
        //pos.y+=ofRandomuf();
    //}
}

void Tail::draw(int _sinOffset, int _tailGrow) {

    ofRectMode(CENTER);

        //ACTIVATE THIS FOR NIRVANA!!!!!!:
        //ofRotate(sin(ofGetFrameNum()*0.01)*30);

        ofCircle(pos+ofPoint(ofRandomf()*0.1,ofRandomf()*0.1),_tailGrow*0.4);

        //ofCircle(pos+ofPoint(ofRandomf()*0.3,ofRandomf()*0.3),_tailGrow*0.6);

}

ofPoint Tail::getPosition(){
 return pos;
}

Tail::~Tail()
{
    //dtor
}
