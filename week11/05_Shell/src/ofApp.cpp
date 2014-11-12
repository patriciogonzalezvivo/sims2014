//
//  Created by Patricio Gonzalez Vivo on 2013
//
//

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){	 
	ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();

    bufferSize = 512;

    large = 1200;
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    cam.setOrientation(ofVec3f(52.5306, 58.7509, -16.9383));
    
    coldLight.setPosition(ofVec3f(0,-500,-large*100));
    coldLight.rotate(-45, 1.0, 0.0, 0.0);
    coldLight.setDiffuseColor(ofFloatColor(0.07,0.01,0.01));
    coldLight.setDirectional();
    
    warmLight.setPosition(ofVec3f(-100,500,-large));
    warmLight.rotate(45, 1.0, 0.0, 0.0);
    warmLight.setDirectional();
    warmLight.setDiffuseColor(ofFloatColor(0.7,0.7,0.35));
    
    ofToggleFullscreen();
    
    ofSoundStreamSetup(0,2,this, 44100, bufferSize, 4);
}


//--------------------------------------------------------------
void ofApp::update(){

    vector<float> newNoise;
    for (int i = 0; i < 20; i++) {
        newNoise.push_back(ofNoise(((float)i)/18.0+ofGetElapsedTimef()*0.1));
    }
    
    noise.push_back( newNoise );
    while(newNoise.size()>large){
        noise.erase(noise.begin());
    }
    
    //  Align and rotate
    //
    float phi   = (1.0+sqrtf(5.0))/2.0;
    float grow  = (1.0+phi);
    float stepGrow  = grow*0.001;
    float radio     = 1.0;
    offSet          = ofPoint(0,0);
    
    int lineWidth;
    points.clear();
    
    ofMatrix4x4 matrix;
    for (int i = 0; i < noise.size(); i++){
        radio += radio*stepGrow;
        float size = radio*grow;
        offSet = ofPoint(size,size*-0.5);
        
        ofPolyline line = freqArc( noise[i], offSet, PI-0.65, 0.0f+0.65, size );
        line = line.getSmoothed(1);
        lineWidth = line.size();
        
        matrix.rotate(1.0, 1.0 , 0.0, 0.0);
        for (int j = 0; j < lineWidth; j++){
            points.push_back( matrix*line[j] );
        }
    }
    
    //  Make the mesh
    //
    createSkin(lineWidth);
    
    if (noise.size() < 1190){
        cam.setDistance(offSet.x*2.0);
    }

    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
	ofSetColor(255);
    
    cam.begin();
    ofEnableLighting();
    coldLight.enable();
    warmLight.enable();
    
    glEnable(GL_DEPTH_TEST);
    ofPushMatrix();
    ofRotateY((ofGetElapsedTimef()*0.1)*180);
    ofRotateX(sin(ofGetElapsedTimef()*0.1)*90);
    
    ofRotateZ((ofGetElapsedTimef()*0.1)*180);
    
    ofTranslate(0,offSet.x*0.7);
    ofRotate(-90, 0, 0, 1);
    ofSetColor(255,250,240);
    if(ofGetKeyPressed( 'm' )){
        mesh.drawWireframe();
    } else {
        mesh.drawFaces();
    }
    ofPopMatrix();
    glDisable(GL_DEPTH_TEST);
    
    coldLight.disable();
    warmLight.disable();
    ofDisableLighting();
    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
ofPolyline ofApp::freqArc( vector<float> &_vector, const ofPoint &_center, float _angleBegin, float _angleEnd, float _minRad,  bool _bSmooth){
    
    ofPolyline line;
    
    float angle = ofWrapRadians(_angleBegin);
    float step = (ofWrapRadians(_angleEnd) - angle)/((float)_vector.size());
    float scale = 1.0f;
    
    ofPoint start = ofPoint(_center.x + _minRad * cos(angle),
                            _center.y + _minRad * sin(angle));
    ofPoint end = ofPoint(_center.x + _minRad * cos(_angleEnd),
                          _center.y + _minRad * sin(_angleEnd));
    
    line.addVertex( start );
    for (int i = 0; i < _vector.size(); i++){
        
        float value = ofMap(_vector[i]*scale, 0.0, 60.0f, _minRad, _minRad*2);
        ofPoint p = _center;
        p.x += value * cos(angle);
        p.y += value * sin(angle);
        angle += step;
        
        if (_bSmooth){
            line.curveTo( p );
        } else {
            line.addVertex(p);
        }
    }
    line.addVertex( end );
    
    return line;
}


//--------------------------------------------------------------
void addFace(ofMesh& mesh,
             ofVec3f a, ofFloatColor aC,
             ofVec3f b, ofFloatColor bC,
             ofVec3f c, ofFloatColor cC) {
    
	ofVec3f normal = ((b - a).cross(c - a)).normalize() * -1.0;
    
	mesh.addNormal(normal);
    mesh.addColor(aC);
	mesh.addVertex(a);
    
	mesh.addNormal(normal);
    mesh.addColor(bC);
	mesh.addVertex(b);
    
	mesh.addNormal(normal);
	mesh.addColor(cC);
    mesh.addVertex(c);
}

//--------------------------------------------------------------
void addFace(ofMesh& mesh,
             ofVec3f a, ofFloatColor aC,
             ofVec3f b, ofFloatColor bC,
             ofVec3f c, ofFloatColor cC,
             ofVec3f d, ofFloatColor dC) {
    
	addFace(mesh, a, aC, b, bC, c, cC);
	addFace(mesh, a, aC, c, cC, d, dC);
}

//--------------------------------------------------------------
void ofApp::createSkin(int _width){

    int width = _width;
    int height = points.size() / width;
    float scale = 5.0f;
    
    mesh.clear();
    for(int y = 0; y < height - 1; y ++) {
		for(int x = 0; x < width - 1; x ++) {
            
			ofVec3f nw = points[ x + y * width];
            ofFloatColor nwC = ofFloatColor( 0.5 + noise[y][x] * 0.5);
            
			ofVec3f ne = points[ (x+1) + y * width];
            ofFloatColor neC = ofFloatColor( 0.5 + noise[y][x] * 0.5);
            
			ofVec3f sw = points[ x + (y+1) * width];
            ofFloatColor swC = ofFloatColor( 0.5 + noise[y][x] * 0.5);
            
			ofVec3f se = points[ (x+1) + (y+1) * width];
			ofFloatColor seC = ofFloatColor( 0.5 + noise[y][x] * 0.5);
            
			addFace(mesh,
                    nw, nwC,
                    ne, neC,
                    se, seC,
                    sw, swC);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){ 
	if (key == 'f'){
        ofToggleFullscreen();
    } else if ( key == ' '){
        noise.clear();
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