#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //  Create 100 Particles
    //
    for (int i = 0; i < 500; i++) {
        Particle newParticle;
        newParticle.setInit(ofPoint(ofRandom(-100,100),ofRandom(-100,100), ofRandom(-100,100)),
                            ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)));
        newParticle.radius = 2;
        particles.push_back(newParticle);
    }
    
    for (int i = 0; i < 3; i++) {
        Particle newParticle;
        newParticle.setInit(ofPoint(ofRandom(-100,100),ofRandom(-100,100), ofRandom(-100,100)) ,
                            ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)));
        newParticle.radius = 5;
        sharks.push_back(newParticle);
    }
    
    light.setDiffuseColor(ofFloatColor(1.0,1.0,1.0));
    light.setPosition(ofPoint(0.0,0.0,0.0));
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < sharks.size(); i++) {
        
        sharks[i].addChasingForce(particles, 300, 1.0);
        
        for(int j = 0; j < sharks.size(); j++){
            if(i != j){
                sharks[i].addRepulsion(sharks[j].pos, 300, 1.0);
            }
            
        }
        sharks[i].update();
    }
    
    ofPoint center = ofPoint(0,0);
    
    for (int i = 0; i < particles.size(); i++) {
        
        for(int j = 0; j < sharks.size(); j++){
            particles[i].addRepulsion(sharks[j].pos, 50, 0.9);
        }
        
        particles[i].addFlockingForce(particles, 80, 1.0, 1.0, 1.0);
        
        particles[i].addRepulsion(center, 100, 1.0);
        particles[i].addAttraction(center, 1000, 0.0001);
        particles[i].update();
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
	
    
    cam.begin();
    light.enable();
    ofEnableLighting();
    
    ofSetColor(255,0,0);
    for (auto &it: sharks) {
        it.draw();
    }
    
    ofSetColor(255);
    for (auto &it: particles) {
        it.draw();
    }
    
    ofDisableLighting();
    light.disable();
    cam.end();
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
