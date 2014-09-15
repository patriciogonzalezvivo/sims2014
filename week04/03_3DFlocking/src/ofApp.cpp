#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //  Create 100 Particles
    //
    for (int i = 0; i < 500; i++) {
        Particle newParticle;
        newParticle.setInit(ofPoint(ofRandom(-100,100),ofRandom(-100,100),ofRandom(-100,100)),
                            ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)));
        particles.push_back(newParticle);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofPoint mouse = ofPoint(mouseX,mouseY);
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i].addFlockingForce(particles, 80, 0.33, 0.5, 0.2);
        particles[i].addAttractionForce(ofPoint(0,0), 1000, 0.0001);
        particles[i].addRepulsionForce(ofPoint(0,0), 100, 0.9);
        particles[i].update();
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
	ofSetColor(255);
    
    ofPushMatrix();
    cam.begin();
    light.enable();
    ofEnableLighting();
    glEnable(GL_DEPTH_TEST);
    
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
    
    glDisable(GL_DEPTH_TEST);
    ofDisableLighting();
    light.disable();
    cam.end();
    ofPopMatrix();
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
