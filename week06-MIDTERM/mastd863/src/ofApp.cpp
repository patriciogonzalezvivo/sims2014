#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetVerticalSync(true);
	ofBackground(30,30,30);
	ofSetCircleResolution(100);
	radius = 0;
	zAxis = 0.01;
    rGrowth = 0.01;

}

//--------------------------------------------------------------
void ofApp::update(){


}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(40,40,40);

    cam.begin();
    light.enable();
    ofEnableLighting();
    glEnable(GL_DEPTH_TEST);

    float xorig = 0;
	float yorig = 0;
	float zorig = -500;

	float angle = ofGetElapsedTimef()*50;  // This sets up the speed of the arc

	float radiusAngle = ofGetElapsedTimef()*0.5;  // This sets up the speed of the arc

    radius = radius + rGrowth * cos(radiusAngle)*50;

	zAxis = zAxis + rGrowth * sin(radiusAngle)*50;

	float x = xorig + radius * cos(angle);

	float y = yorig + radius * -sin(angle);

	float z = zorig + zAxis;


	ofPoint temp;
	temp.x = x;
	temp.y = y;
	temp.z = z;

	points.push_back(temp);
	if (points.size() > 2000){
		points.erase(points.begin());
	}

	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(200,50,50);
	ofNoFill();

	// ------------------------------------  CONE 1   X  Y  Z-----------------------------------------------------

	ofBeginShape();
	for (int i = 0; i < points.size(); i++) { // This creates the curve, connects each point as a vertex of the same line.
		ofVertex(points[i].x, points[i].y,points[i].z);
	}
	ofEndShape();

	// ------------------------------------  CONE 1   X  Y  Z-----------------------------------------------------

	ofBeginShape();
	for (int i = 0; i < points.size(); i++) { // This creates the curve, connects each point as a vertex of the same line.
		ofVertex(-points[i].x, -points[i].y,-points[i].z);
	}
	ofEndShape();

    glDisable(GL_DEPTH_TEST);
    ofDisableLighting();
    light.disable();
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if (key == 'f'){
        ofToggleFullscreen();
    }
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
