#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	
	
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
	
	ofBackground(255, 255, 255);
	
	for (int i = 0; i < 50; i++){
		Particle myParticle;
		myParticle.setInitialCondition(300,300,ofRandom(-10,10), ofRandom(-10,10));
		// more interesting with diversity :)
		//myParticle.damping = ofRandom(0.001, 0.05);
		particles.push_back(myParticle);
	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].addForce(0.0, 0.28);
		particles[i].bounceOffWalls();
		particles[i].update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
	ofSetColor(255,0,0);
	
	for (int i = 0; i < particles.size(); i++){
		particles[i].draw();
	}

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
	for (int i = 0; i < particles.size(); i++){
		particles[i].setInitialCondition(mouseX,mouseY,ofRandom(-10,10), ofRandom(-10,10));
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(){
}
