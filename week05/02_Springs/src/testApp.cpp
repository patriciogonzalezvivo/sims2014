#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

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
void testApp::update(){
    
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
void testApp::draw(){
    for( int i=0; i<springList.size(); i++ ){
        springList[i].draw();
    }
    
    for( int i=0; i<jointList.size(); i++ ){
        jointList[i].draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    int rand = floor( ofRandom( jointList.size() ) );
    
    jointList[rand].applyForce( ofVec2f(ofRandom(-10, 10), 0) );
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
   
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
  
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bDragging = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
