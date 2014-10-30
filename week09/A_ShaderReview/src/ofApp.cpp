#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofDisableArbTex();
    ofLoadImage(tex, "texture.png");
    
    ofEnableArbTex();
    
    width = ofGetWidth();
    height = ofGetHeight();
    
    shader.load("","shader.frag");
    fbo.allocate(width, height);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    fbo.begin();
    ofClear(0);
    ofSetColor(255);
    shader.begin();
    shader.setUniformTexture("texture", tex,0);
    shader.setUniform2f("mouse", mouseX, mouseY);
    shader.setUniform1f("time", ofGetElapsedTimef());
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1.0, 0);
    glVertex2f(width, 0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(width, height);
    glTexCoord2f(0, 1.0);
    glVertex2f(0, height);
    glEnd();
    shader.end();
    fbo.end();
    
    fbo.readToPixels(pixels);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255);
    fbo.draw(0,0);
    
    ofSetColor(pixels.getColor(width*0.5, height*0.5));
    ofCircle(width*0.5, height*0.5, 50);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    shader.load("","shader.frag");
    
    
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
