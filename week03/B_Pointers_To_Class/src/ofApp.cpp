#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    cout << &myBall.position.x << endl;
    cout << &myBall.position.y << endl;
    cout << &myBall.position.z << endl;
    cout << &myBall.xVelocity << endl;
    cout << &myBall.yVelocity << endl;
    
    pointerX = &myBall.xVelocity;
    pointerY = &myBall.yVelocity;
}

//--------------------------------------------------------------
void ofApp::update(){
    myBall.update();
    
    *pointerX *= 0.5;
    *pointerX += ofRandom(-1, 1)*0.5;
    *pointerY *= 0.5;
    *pointerY += ofRandom(-1, 1)*0.5;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
	ofSetColor(255,255,255);
    myBall.draw();
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
