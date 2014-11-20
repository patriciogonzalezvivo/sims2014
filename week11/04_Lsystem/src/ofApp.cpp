#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    // sierpinski
//    vector<Rule> myRules;
//    myRules.push_back( Rule('F',"F--F--F--G") );
//    myRules.push_back( Rule('G',"GG") );
//    
//    system.setup("F--F--F", myRules);
//    turtle.setup( 10, 60 );
//    turtle.setInstructions( system.sentence );
    
    
    // boxes
//    vector<Rule> myRules;
//    myRules.push_back( Rule('F',"F[F]-F+F[--F]+F-F") );
//    system.setup( "F-F-F-F", myRules );
//    turtle.setup( 10, 90 );
//    turtle.setInstructions( system.sentence );
    
    // tree
    vector<Rule> myRules;
    myRules.push_back( Rule('F',"FF+[+F-F-F]-[-F+F+F]") );
    system.setup("F", myRules);
    turtle.setup( 10, 25 );
    turtle.setInstructions( system.sentence );
    
    ofBackground( 0 );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
        ofTranslate( 0, ofGetWindowHeight() );
//        ofRotate( -90 );
        turtle.draw();
    ofPopMatrix();
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
    system.addGeneration();
    turtle.setInstructions( system.sentence );
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
