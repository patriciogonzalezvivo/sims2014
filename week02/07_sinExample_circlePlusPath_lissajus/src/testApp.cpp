#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetVerticalSync(true);
	
//    ofSetBackgroundAuto(false);
    ofBackground(0);
	ofSetCircleResolution(100);
	ofEnableAlphaBlending();
    
    ofFill();
	ofSetRectMode( OF_RECTMODE_CORNER );
    ofSetColor(0,0,0,255);
    ofRect( ofGetWindowRect() );
}

//--------------------------------------------------------------
void testApp::update(){
	
	

}

//--------------------------------------------------------------
void testApp::draw(){
    
//    ofFill();
//	ofSetRectMode( OF_RECTMODE_CORNER );
//    ofSetColor(0,0,0,255*0.01);
//    ofRect( ofGetWindowRect() );
    
    ofSetColor(255, 255, 255, 255);
	float xorig = 500;
	float yorig = 300;
	float angle = ofGetElapsedTimef()*3.5;
	float radius = 200;
	float x = xorig + radius * cos(angle * 3.4);    // 3.4
	float y = yorig + radius * sin(angle * 4.7);   // 4.7
	
	ofPoint temp;
	temp.x = x;
	temp.y = y;
	points.push_back(temp);
	if (points.size() > 400){
		points.erase(points.begin());
	}
	
	
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(255,0,127);
	ofFill();
	ofCircle(x,y,10);
	
	ofSetColor(255,255,255);
	
	ofNoFill();
	ofBeginShape();
	for (int i = 0; i < points.size(); i++){
		ofVertex(points[i].x, points[i].y);
	}
	ofEndShape();
	
	
	
	
	
	
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

