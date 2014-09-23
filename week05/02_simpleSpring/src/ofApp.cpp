#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    for( int i=0; i<4; i++ ){
        SpringJoint sj;
        sj.pos = ofVec2f( ofGetWindowWidth() / 2, 10 + i*195);
        jointList.push_back( sj );
    }
    
    
    Spring spring1, spring2, spring3;
    
    spring1.set( &jointList[0], &jointList[1], 0.05, 200.0 );
    spring2.set( &jointList[1], &jointList[2], 0.05, 200.0 );
    spring3.set( &jointList[2], &jointList[3], 0.05, 200.0 );
    
    springList.push_back( spring1 );
    springList.push_back( spring2 );
    springList.push_back( spring3 );
    
    bDragging = false;
    
    ofSetFrameRate(60.0);
    ofSetVerticalSync( true );
    ofBackground(0);
}

/**
 *  We're working with Hookes law here http://en.wikipedia.org/wiki/Hooke's_law
 *  F = -k * x;
 */

//--------------------------------------------------------------
void ofApp::update(){
    
    if( bDragging ){
        return;
    }
    
    for( int i=0; i<springList.size(); i++ ){
        springList[i].update();
    }
    
    for( int i=0; i<jointList.size(); i++ ){
        jointList[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for( int i=0; i<springList.size(); i++ ){
        springList[i].draw();
    }
    
    for( int i=0; i<jointList.size(); i++ ){
        jointList[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    int rand = floor( ofRandom( jointList.size() ) );
    
    jointList[rand].applyForce( ofVec2f(ofRandom(-10, 10), 0) );
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
    bDragging = false;
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
