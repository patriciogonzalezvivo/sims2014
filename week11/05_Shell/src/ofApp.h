//
//  Created by Patricio Gonzalez Vivo on 2013
//
//

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
		
    void setup();
    void update();
    void draw();
		
    void keyPressed  (int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
		
	ofPolyline  freqArc( vector<float> &_vector, const ofPoint &_center, float _angleBegin, float _angleEnd, float _minRad , bool _bSmooth = false);
    
    void createSkin( int _width );
    
    ofEasyCam           cam;
    ofMesh              mesh;
    ofLight             coldLight;
    ofLight             warmLight;
    vector< vector<float> >   noise;
    vector<ofPoint>     points;

    ofPoint             offSet;

    int                 bufferSize;
    int                 large;
};

