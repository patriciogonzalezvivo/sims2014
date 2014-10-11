#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    ofEnableSmoothing();
    ofSetCircleResolution(60);
    ofBackground(0,0,0);
    ofSetFullscreen(true);
    
    
    ofSetFrameRate(60);
    radius = 100;
    pos.set(ofGetWindowSize()/2);
    //pos.Y = ofGetHeight()/2;
    
    startNoise = ofRandom(0,10);
    noiseStep = 0.1;
    
    //damping.set(0.01f);
    width = 100;
    height = 100;
    //
    
   //ofCircle(centX, centY, radius);
}


//--------------------------------------------------------------
void testApp::update(){
    
    float stepStep = 0.01;
    
    startNoise += 0.01;
    noiseStep += stepStep;
    if (noiseStep > 5) {
        stepStep *= -1;
    } else if (noiseStep < -5) {
        stepStep *= -1;
    }
    
    
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    float x, y;
    float noiseval = startNoise;


ofPushMatrix();{
    
    ofBeginShape();{
        
    
    
    for (float i = 0; i < 400; i ++) {
        
        ofSetColor( ofColor(255,0,147));
        ofNoFill();
        
        //noiseval += noiseStep;
        
        rad = ofNoise(i/20, offset+ofGetElapsedTimef()*0.15);
        
        //rad = radius + radVariance;
        //rad = ofDegToRad(ang);
        
        ofVertex( pos.x + (150 + 150 * rad) * cos((i/50) * TWO_PI),
                 pos.y + (150 + 150 * rad) * sin((i/50) * TWO_PI));
    }
    
    float rad = ofNoise(0/50.0f, offset+ofGetElapsedTimef()*0.15);
    
    ofVertex( pos.x + (200 + 200 * rad) * cos((0/100.0) * PI),
             pos.y + (200 + 200 * rad) * sin((0/100.0) * PI));
    
}ofEndShape();


}ofPopMatrix();
    
    
    
    ofPushMatrix();{
        
        ofBeginShape();{
            
            
             ofSetColor( ofColor(255));
            
            for (float i = 0; i < 400; i ++) {
                
          
               
                
                //noiseval += noiseStep;
                
                rad = ofNoise(i/20, offset+ofGetElapsedTimef()*0.15);
                
                //rad = radius + radVariance;
                //rad = ofDegToRad(ang);
                
                ofVertex( pos.x + (width + height * rad) * cos((i/50) * TWO_PI),
                         pos.y + (width + height * rad) * sin((i/50) * TWO_PI));
            }
            
            float rad = ofNoise(0/50.0f, offset+ofGetElapsedTimef()*0.15);
            
            ofVertex( pos.x + (width + height * rad) * cos((0/100.0) * PI),
                     pos.y + (width + height * rad) * sin((0/100.0) * PI));
            
        }ofEndShape();
        
        
    }ofPopMatrix();
}




//--------------------------------------------------------------
void testApp::keyPressed(int key){

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
