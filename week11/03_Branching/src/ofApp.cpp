#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    generation = 0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::branch( float length ) {
    ofPushMatrix();
    ofLine( ofVec2f(0,0), ofVec2f(0, -length) );
    ofTranslate( 0, -length );
    
    generation++;
    
    float noise = ofNoise( generation, ofGetElapsedTimef() * 0.1 );
    
    if( length > 2 ){
        ofPushMatrix();{
            ofRotate( 45 + theta + noise * 10-5 );
            branch( length * 0.666 );
        }ofPopMatrix();
        
        ofPushMatrix();{
            ofRotate( -45 + theta - noise * 10-5 );
            branch( length * 0.666 );
        }ofPopMatrix();
    }
    
    ofPopMatrix();
    
    generation--;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();{
        ofTranslate( ofGetWindowWidth()/2, ofGetWindowHeight() );
        branch( 200 );
    }ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    theta = ofMap(x, 0, ofGetWindowWidth(), -180, 180);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
