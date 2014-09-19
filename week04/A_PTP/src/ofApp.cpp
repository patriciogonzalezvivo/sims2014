#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //  Create 100 Particles
    //
    for (int i = 0; i < 1000; i++) {
        Particle *newParticle = new Particle();
        newParticle->setInit(ofPoint(ofGetWidth()*0.5,ofGetHeight()*0.5),
                            ofPoint(ofRandom(-1, 1), ofRandom(-1, 1)));
        particles.push_back(newParticle);
    }
    
    img.loadImage("ball.png");
    img.setAnchorPercent(0.5, 0.5);
}

bool particleSort( Particle *_a,  Particle *_b){
    return (_a->pos.x<_b->pos.x);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofPoint mouse = ofPoint(mouseX,mouseY);
    
    sort(particles.begin(),particles.end(),particleSort);
    for (int i = 0; i < particles.size(); i++) {
        for (int j = i-1; j >= 0 && i-j < 100 ; j--) {
            particles[i]->addRepulsion(particles[j], 1.0);
        }
        
        particles[i]->addRepulsion(mouse, 30, 1.0);
        particles[i]->update();
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(ofGetKeyPressed('s')){
        ofBeginSaveScreenAsPDF(ofGetTimestampString()+".pdf");
    }
    
    ofBackground(0, 0, 0);
	ofSetColor(255);
    
    for (auto &it: particles) {
        it->draw(&img);
    }
    
    if(ofGetKeyPressed('s')){
        ofEndSaveScreenAsPDF();
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
