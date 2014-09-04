#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	ofBackground(255, 255, 255);
	
	p.setInitialCondition(300,300,ofRandom(-1,1), ofRandom(-1,1));
}

//--------------------------------------------------------------
void ofApp::update(){

	p.addForce(0, 0.1);
	p.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofBackground(0, 0, 0);
	ofSetColor(255,0,0);
    
	p.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){ 
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	p.setInitialCondition(x,y,ofRandom(-10,10), ofRandom(-10,10));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(){
}
