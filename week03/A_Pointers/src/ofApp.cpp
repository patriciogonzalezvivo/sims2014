#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(300, 300);
    
//    float var = PI;
//    float var2 = HALF_PI;
//    
//    cout << "1 - Address " << &var << endl;
//    cout << "    How big " << sizeof(var) << endl;
//    cout << "2 - Address " << &var2 << endl;
    
    int array[10];
    for (int i = 0; i < 10; i++) {
        array[i] = i;
    }
    
    for (int i = 0; i < 10; i++) {
        cout << array[i] << "  " << &array[i] << endl;
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ball.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofSetColor(255, 0, 0);
    ball.draw();
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
