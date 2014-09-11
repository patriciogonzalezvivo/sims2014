#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //  Create 3 balls
    //
    for (int i = 0; i < 100; i++) {
        Ball newBall;
        newBall.setInit(ofPoint(ofGetWidth()*ofRandomf(),ofGetHeight()*ofRandomf()));
        balls.push_back(newBall);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //  Go throught all the balls and update the position
    //
    for (int i = 0; i < balls.size(); i++) {
        balls[i].addForce(ofVec3f(0,0.98));
        balls[i].update();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
	ofSetColor(255);
    
    //  Draw them all
    //
//    for (int i = 0; i < balls.size(); i++) {
//        balls[i].draw();
//    }
    
    for (auto &it: balls) { // Cooler way ;P
        it.draw();
    }
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
    ofPoint mouse = ofPoint(mouseX,mouseY);
    ofPoint pmouse = ofPoint(ofGetPreviousMouseX(),ofGetPreviousMouseY());
    
    ofPoint diff = mouse-pmouse;
    diff *= 0.1;
    
    for (int i = 0; i < balls.size(); i++) {
        balls[i].addForce(diff);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    Ball newBall;
    newBall.setInit(ofPoint(x,y));
    balls.push_back(newBall);
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
