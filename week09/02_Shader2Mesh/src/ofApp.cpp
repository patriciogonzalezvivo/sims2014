#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    ofDisableArbTex();
    ofLoadImage(heightMap, "heightmap.png");
    normalFbo.allocate(ofGetWidth(), ofGetHeight());
    ofEnableArbTex();
    
    normalShader.load("","normal.frag");
    terrainShader.load("terrain");
    
    int scale = 15;
    int w = ofGetWidth()/scale;
    int h = ofGetHeight()/scale;
    for (int y = 0; y < h; y++){
        for (int x = 0; x<w; x++){
            float offsetX = 0;
            float offsetY = (x%2==1)?0.5:0.0;
            terrain.addVertex(ofPoint((x+offsetX)*scale,(y+offsetY)*scale,0));
            terrain.addNormal(ofPoint(1,0,0));
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

    int width = ofGetWidth();
    int height = ofGetHeight();
    
    //  Compute the normals inside a FBO
    //
    normalFbo.begin();
    ofClear(0);
    ofSetColor(255);
    normalShader.begin();
    normalShader.setUniformTexture("texture", heightMap,0);
    glBegin(GL_QUADS);
    
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    
    glTexCoord2f(1.0, 0);
    glVertex2f(width, 0);
    
    glTexCoord2f(1.0, 1.0);
    glVertex2f(width, height);
    
    glTexCoord2f(0, 1.0);
    glVertex2f(0, height);
    
    glEnd();
    normalShader.end();
    normalFbo.end();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);

    cam.begin();
    ofPushMatrix();
    
    //  Center the mesh;
    //
    ofTranslate(-ofGetWidth()*0.5, -ofGetHeight()*0.5);
    
    //  Draw the mesh applying the shader that will move the points to different height
    //  acording to the texture
    //
    terrainShader.begin();
    terrainShader.setUniformTexture("heightMap", heightMap,0);
    terrainShader.setUniformTexture("normalMap", normalFbo,1);
    terrainShader.setUniform1f("time",ofGetElapsedTimef());
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
