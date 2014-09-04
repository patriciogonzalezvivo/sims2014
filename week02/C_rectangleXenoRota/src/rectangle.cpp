#include "rectangle.h"


//------------------------------------------------------------------
rectangle::rectangle(){
	catchUpSpeed = 0.03f;
}


//------------------------------------------------------------------
void rectangle::xenoToPoint(ofPoint _catch){
    set(catchUpSpeed * _catch + (1.-catchUpSpeed) * (*this));
    
    ofPoint diff = *this - _catch;
    
    angle = ofLerp(angle, atan2(diff.y,diff.x), 0.1);

    if (angle < -PI) angle += PI*2.;
    if (angle > PI) angle -= PI*2.;
}

//------------------------------------------------------------------

void rectangle::draw() {
    
    ofPushMatrix();
    ofTranslate(*this);
    
    ofRotate(ofRadToDeg(angle));
    ofSetColor(198,246,55);
    
    ofFill();
	ofSetRectMode(OF_RECTMODE_CENTER);
    ofRect(0,0, 20,20);
    
    ofPopMatrix();
}


