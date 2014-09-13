#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSeedRandom();
    
    
    dest1 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    dest2 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    
    car1.setInit( ofGetWindowSize() / 2, ofPoint(10, -5) );
    car2.setInit( ofGetWindowSize() / 2, ofPoint(10, 5) );
    
    car1.color = ofColor(0,255,0);
    car2.color = ofColor(0,0,255);
    
    ofBackground(255);
    
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // apply steering force
    car1.seek( dest1 );
    car2.seek( dest2 );
    
    // apply repelling force
    float area = 200;
    if( car1.getPosition().distance( car2.getPosition() ) < area ){
        car1.color = ofColor(255,0,0);
        car2.color = ofColor(255,0,0);
        
        car1.addRepulsionForce( car2.getPosition(), area,  0.1 );
        car2.addRepulsionForce( car1.getPosition(), area, 0.1 );
    }else{
        car1.color = ofColor(0,255,0);
        car2.color = ofColor(0,0,255);
    }
    
    // update physics
    car1.update();
    car2.update();
    
    if( car1.getPosition().distance(dest1) < 5){
        dest1 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    }
    
    if( car2.getPosition().distance(dest2) < 5){
        dest2 = ofPoint( ofRandomWidth(), ofRandomHeight() );
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofSetColor( car1.color );
    ofCircle( dest1, 4 );
    car1.draw();
    
    ofSetColor( car2.color );
    ofCircle( dest2, 4 );
    car2.draw();
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
