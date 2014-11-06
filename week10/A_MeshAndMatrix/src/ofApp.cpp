#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
}

//--------------------------------------------------------------
void ofApp::update(){

    mesh.clear();
    
    float offset = 0;
    float width = 10;
    float height = 10;
    ofMatrix4x4 M;
    M.makeIdentityMatrix();
    for (int i = 0 ; i < 1000; i++) {
        ofMatrix4x4 R;
        R.makeRotationMatrix(0.5, ofVec3f(1,0,0));
        
        M *= R; // Push
        mesh.addVertex(M*ofPoint(width*0.5,offset-height*0.5));   // 1,0
        mesh.addVertex(M*ofPoint(-width*0.5,offset-height*0.5));  // 0,0
        mesh.addVertex(M*ofPoint(width*0.5,offset+height*0.5));   // 1,1
        mesh.addVertex(M*ofPoint(-width*0.5,offset+height*0.5));  // 0,1

        offset += height;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    
    cam.begin();
    mesh.draw();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        mesh.save("mesh.ply");
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
