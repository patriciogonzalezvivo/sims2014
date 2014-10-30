#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();

    ofDisableArbTex();
    ofLoadImage(heightMap, "heightmap.png");
//    video.initGrabber(640, 480);
    ofEnableArbTex();
    
    terrainShader.load("terrain");

    int scale = 15;
    int w = ofGetWidth()/scale;
    int h = ofGetHeight()/scale;
    for (int y = 0; y < h; y++){
        for (int x = 0; x<w; x++){
            
            //  Per pixel we set the position, normal and texCoord
            //
            float offsetX = 0;
            float offsetY = (x%2==1)?0.5:0.0;
            terrain.addVertex(ofPoint((x+offsetX)*scale,(y+offsetY)*scale,0));
            terrain.addNormal(ofPoint(0,0,1));
            terrain.addTexCoord(ofVec2f((float)(x+offsetX)/(float)w,(float)(y+offsetY)/(float)h));
        }
    }
    
    for (int y = 0; y<h-1; y++){
        for (int x=0; x<w-1; x++){
            if(x%2==0){
                terrain.addIndex(x+y*w);				// a
                terrain.addIndex((x+1)+y*w);			// b
                terrain.addIndex(x+(y+1)*w);			// d
                
                terrain.addIndex((x+1)+y*w);			// b
                terrain.addIndex((x+1)+(y+1)*w);		// c
                terrain.addIndex(x+(y+1)*w);			// d
            } else {
                terrain.addIndex((x+1)+y*w);			// b
                terrain.addIndex(x+y*w);				// a
                terrain.addIndex((x+1)+(y+1)*w);		// c
                
                terrain.addIndex(x+y*w);				// a
                terrain.addIndex(x+(y+1)*w);			// d
                terrain.addIndex((x+1)+(y+1)*w);		// c
            }
        }
    }
    
    
    
    bWireframe = true;
}

//--------------------------------------------------------------
void ofApp::update(){
//    video.update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    cam.begin();
    
    ofPushMatrix();

    ofTranslate(-ofGetWidth()*0.5, -ofGetHeight()*0.5);
    
    terrainShader.begin();
    terrainShader.setUniformTexture("heightMap", heightMap,0);
//    terrainShader.setUniformTexture("heightMap", video,0);
    terrainShader.setUniform2f("mouse",mouseX,mouseY);
    terrainShader.setUniform1f("time",ofGetElapsedTimef());     // We can play with this later ;)
    if(bWireframe){
        terrain.drawWireframe();
    } else {
        terrain.draw();
    }
    terrainShader.end();
    
    ofPopMatrix();
    
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'w'){
        bWireframe = !bWireframe;
    } else {
        terrainShader.load("terrain");
    }
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
