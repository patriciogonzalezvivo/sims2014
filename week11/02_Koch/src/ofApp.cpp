#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    KochLine line( ofVec2f(0, 500), ofVec2f( ofGetWindowWidth(), 500) );
    
    lineList.push_back( line );
    
    ofBackground(0);
    pct = 1.0;
}

//--------------------------------------------------------------
void ofApp::update(){

}

void ofApp::addGeneration() {
    vector<KochLine> newLines;
    
    for( int i=0; i<lineList.size(); i++ ){
        ofVec2f a = lineList[i].a();
        ofVec2f b = lineList[i].b();
        ofVec2f c = lineList[i].c();
        ofVec2f d = lineList[i].d();
        ofVec2f e = lineList[i].e();
        
        newLines.push_back( KochLine(a, b) );
        newLines.push_back( KochLine(b, c) );
        newLines.push_back( KochLine(c, d) );
        newLines.push_back( KochLine(d, e) );
    }
    
    lineList = newLines;
}

//--------------------------------------------------------------
void ofApp::draw(){
    float coastLine = 0;
    
    int pos = ceil( lineList.size() * pct );
    
    for( int i=0; i<pos; i++ ){
        lineList[i].draw();
        coastLine += lineList[i].getLength();
    }
    
    ofDrawBitmapString("Dist: " + ofToString(coastLine), ofVec2f(10,10) );
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    pct = (float)x / ofGetWindowWidth();
    pct = ofClamp(pct, 0.0, 1.0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    addGeneration();
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
