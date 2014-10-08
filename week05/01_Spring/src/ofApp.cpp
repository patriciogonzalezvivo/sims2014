#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
void ofApp::update(){
    
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

void ofApp::applyForce( ofVec2f force ) {
    acc += force;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofLine( anchor, ball );
    
    ofCircle( anchor, 10 );
    ofCircle( ball, 20 );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    applyForce( ofVec2f(0.5, 0) );
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if( bDragging ){
        ball.set( x, y );
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if( ofVec2f(x, y).distance(ball) < 20 ){
        ball.set( x, y );
        bDragging = true;
        vel *= 0;
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    bDragging = false;
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
