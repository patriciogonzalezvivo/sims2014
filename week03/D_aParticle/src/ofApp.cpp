#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //  Create 100 Particles
    //
    for (int i = 0; i < 100; i++) {
        Particle newParticle;
        newParticle.setInit(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5),
                            ofPoint(ofRandom(-1, 1), ofRandom(-1, 1)));
        particles.push_back(newParticle);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofPoint mouse = ofPoint(mouseX,mouseY);
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i].addRepulsion(mouse, 30, 0.5);
        particles[i].addAttraction(mouse, 100, 0.1);
        particles[i].update();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
	ofSetColor(255);
    
    for (auto &it: particles) {
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
