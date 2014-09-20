#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    k = 0.05;
    restLength = 200.0;
    
    anchor  = ofVec2f( ofGetWindowWidth() / 2, 10);
    ball    = ofVec2f( ofGetWindowWidth() / 2, restLength+50);
    
    bDragging = false;
    
    ofSetFrameRate(60.0);
    ofSetVerticalSync( true );
    ofBackground(0);
}

/**
 *  We're working with Hookes law here http://en.wikipedia.org/wiki/Hooke's_law
 *  F = -k * x;
 */

//--------------------------------------------------------------
void testApp::update(){
    
    if( bDragging ){
        return;
    }
    
    ofVec2f force = ball - anchor;  // the direction
    float len = force.length();
    float stretchLength = len - restLength;
    
    
    force.normalize();
    force *= -1 * k * stretchLength;
    
    applyForce( force );
    applyForce( ofVec2f(0,1.0) );
    
    
    vel += acc;
    vel *= 0.95;
    
    ball += vel;
    
    acc *= 0;
    
}

void testApp::applyForce( ofVec2f force ) {
    acc += force;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofLine( anchor, ball );
    
    ofCircle( anchor, 10 );
    ofCircle( ball, 20 );
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    applyForce( ofVec2f(0.5, 0) );
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    if( bDragging ){
        ball.set( x, y );
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    if( ofVec2f(x, y).distance(ball) < 20 ){
        ball.set( x, y );
        bDragging = true;
        vel *= 0;
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bDragging = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
