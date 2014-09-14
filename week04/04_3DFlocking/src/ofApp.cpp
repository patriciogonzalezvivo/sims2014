#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    ofBackground(0);
    
    flocker.addParticle( 1000 );
    
    ofEnableDepthTest();
    myCam.setDistance(1000);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    flocker.applyForces(80, 0.4, 0.75);
    flocker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    myCam.begin();
    
    ofPushMatrix();{
//        ofTranslate( ofGetWindowSize() / 2.0 );
        flocker.draw();
    }ofPopMatrix();
    
    myCam.end();
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
    flocker.addParticle( 50 );
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
