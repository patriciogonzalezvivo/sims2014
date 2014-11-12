#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground( 0 );
    ofSetColor( 255 );
    
    
}

void ofApp::drawDiamond(float x, float y, float size ){
    ofSetRectMode( OF_RECTMODE_CENTER );
    
    if( size > 16 ){
        drawDiamond( x + size/2, y, size/2 );
        drawDiamond( x - size/2, y, size/2 );
        
        drawDiamond( x, y + size/2, size/2 );
        drawDiamond( x, y - size/2, size/2 );
    }
    
    ofPushMatrix();{
        ofTranslate( x, y);
        ofRotate( 45 );
        ofRect( 0, 0, size, size );
    }ofPopMatrix();
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofNoFill();
    drawDiamond( ofGetWindowWidth()/2, ofGetWindowHeight()/2, ofGetWindowWidth()/2 );
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
