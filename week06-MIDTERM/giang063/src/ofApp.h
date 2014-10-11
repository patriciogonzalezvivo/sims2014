#pragma once

#include "ofMain.h"
#include "Ribbon.h"
#include "ofxUI.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    /*------------------ DRAWING ------------------*/
    vector<Ribbon> shapes;
    bool isDrawing;
    int shapeSmoothing;
    int margins[4];
    ofPoint canvasPos, canvasSize;
    void setCanvas();
    
    /*-------------------- GUI --------------------*/
	ofxUISuperCanvas *gui;
	void guiEvent(ofxUIEventArgs &e);
	void setGUI();
    vector<string> modes;
    string selectedMode;
    
    /*-------------------- 3D ---------------------*/
    ofEasyCam cam;
    ofLight light;
    ofMaterial material;
    ofFloatColor lightColor;
    bool useCamera;
    float thickness;
    float zDepth;

    /*----------------- PHYSICS -------------------*/
    float modifierRadius;
    float modifierStrength;
    
    /*------------------- WAVE --------------------*/
    float amplitude;
    int frequencyInSeconds;
    int nModifier;
    
};
