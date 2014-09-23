#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofSetVerticalSync(true);
    
    thing.init("00.png", ofPoint(800,ofGetHeight()*0.5));
//    thing.load("00.xml", ofPoint(800,270) );
    thing.startEditMode();
    bEdit = true;
    
    VF.setupField( ofGetWidth()/20, ofGetHeight()/20, ofGetWidth(), ofGetHeight());
    bPlay = false;
    bNoise = false;
}

//--------------------------------------------------------------
void ofApp::update(){

    if (bPlay){
        VF.fadeField(0.99);
        if (bNoise)
            VF.noiseField();
        
        thing.update( &VF );
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    VF.draw();
    
    thing.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'e'){
        bEdit = !bEdit;
        thing.togleEditMode();
        bPlay = !bEdit;
    } else if (key == 'p'){
        bPlay = !bPlay;
    } else if (key == 'r'){
        thing.restart();
    } else if (key == 'c'){
        thing.clear();
    } else if (key == 's'){
        string filename = "t"+ofToString(ofGetDay())+"-"+ofToString(ofGetHours())+"-"+ofToString(ofGetMinutes())+"-"+ofToString(ofGetSeconds());
        thing.save(filename+".xml");
    } else if (key == 'n'){
        bNoise = !bNoise;
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
    if (!bEdit){
        float diffx = x - prevMouseX;
        float diffy = y - prevMouseY;
        
        VF.addVectorCircle((float)x, (float)y, diffx*0.3, diffy*0.3, 60, 0.3f);
        
        prevMouseX = x;
        prevMouseY = y;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    prevMouseX = x;
	prevMouseY = y;
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