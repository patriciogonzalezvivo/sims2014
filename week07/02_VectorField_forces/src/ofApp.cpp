#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myField.setup( ofGetWindowWidth(), ofGetWindowHeight(), 20 );
        
    ofBackground(0);
    
    particleList.clear();
    
    for( int i=0; i<300; i++ ){
        addParticle();
    }
}

void ofApp::addParticle() {
    Particle part;
    part.pos = ofVec2f( ofRandomWidth(), ofRandomHeight() );
    
    particleList.push_back( part );
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for( int i=0; i<particleList.size(); i++ ){
        ofVec2f forceAtPos = myField.getForceAtPosition(particleList[i].pos) * 0.005;
        particleList[i].applyForce( forceAtPos );
        particleList[i].update();
    }
    
    myField.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    myField.draw();
    
    ofSetColor(0, 255, 255);
    for( int i=0; i<particleList.size(); i++ ){
        particleList[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == '1'){
        myField.setRandom( 20.0 );
    }else if( key == '2' ){
        myField.setPerlin();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
    if( button == OF_MOUSE_BUTTON_1 ){
//        myField.addRepelForce(x, y, 100, 2.0);
        myField.addCircularForce(x, y, 300, 2.0);
    }else{
        myField.addAttractForce(x, y, 100, 2.0);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mouseDragged(x, y, button);
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
