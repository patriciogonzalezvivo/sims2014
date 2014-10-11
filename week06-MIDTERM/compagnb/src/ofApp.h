#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofMesh myMesh;
    ofLight myLight;
    
    void setNormals(ofMesh &mesh);
    
    //grid variables
    int gridWidth;
    int gridHeight;
    
    //
    float time;
    float angle;
    
    int numVert;
    int numTri;
    
    ofPoint dir;
    
    int i1;
    int i2;
    int i3;
	int i4;
};
