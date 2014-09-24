#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    myField.setup( 1000, 1000, 1000, 50 );
    myField.setPerlin();
    
    particleList.clear();
    
    for( int i=0; i<100000; i++ ){
        addParticle();
    }
    
    ofBackground (0);
    
}

void ofApp::addParticle() {
        Particle part;
        part.pos = ofVec3f( ofRandom(myField.width), ofRandom(myField.height), ofRandom(myField.depth) );
        
        particleList.push_back( part );
    }
    
//--------------------------------------------------------------
void ofApp::update(){
    //myField.update();
    
    for( int i=0; i<particleList.size(); i++ ){
        particleList[i].applyForce( myField.getForceAtPosition(particleList[i].pos ) * 0.005 );
        particleList[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    myCam.begin();
    
    ofPushMatrix(); {
        ofTranslate(myField.width*0.5*-1, myField.height*0.5*-1, myField.depth*0.5*-1);
    
        
        
        //myField.draw();
        
        glBegin(GL_POINTS);
        for( int i=0; i<particleList.size(); i++ ){
            particleList[i].draw();
        }
        glEnd();
    
    } ofPopMatrix();
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
