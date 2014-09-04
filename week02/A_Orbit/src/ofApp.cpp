#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    luna.set(70, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    mouse.set(mouseX, mouseY);
    
    luna.update(0.01, ofPoint(ofGetWidth()*0.5, ofGetHeight()*0.5));
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor(0, 0, 255);
    ofCircle(ofGetWidth()*0.5, ofGetHeight()*0.5, 30);
    
    luna.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
