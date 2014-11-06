#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    light.setDiffuseColor(ofFloatColor(1.,1.,1.));
}

//--------------------------------------------------------------
void ofApp::update(){

    mesh.clear();
    
    float offset = 10;
    float width = 100;
    float height = 100;
    
    float phi = (1.+sqrt(5.))*0.5;
    
    ofMatrix4x4 M;
    M.makeIdentityMatrix();
    
    for (int i = 0 ; i < 100; i++) {
        ofMatrix4x4 R;
        R.makeRotationMatrix(10.0, ofVec3f(1,0,0));
        
        ofMatrix4x4 R2;
        R2.makeRotationMatrix(5.0, ofVec3f(0,0,1));
        
        M *= R;
        M *= R2;
        mesh.addColor(ofFloatColor(1,(float)i/100.,0));
        mesh.addVertex(M*ofPoint(width*0.5,-height*0.5));   // 1,0
        mesh.addColor(ofFloatColor(0,(float)i/100.,1));
        mesh.addVertex(M*ofPoint(-width*0.5,-height*0.5));  // 0,0

        width *= 1.03;
        height += offset;
    }
    
    mesh.clearNormals();
    ofPoint up = ofPoint(0,0,1);
    mesh.addNormal(up);
    mesh.addNormal(up);
    for (int i = 2; i < mesh.getVertices().size(); i+=2) {
        ofPoint a = mesh.getVertices()[i-1];
        ofPoint b = mesh.getVertices()[i];
        ofPoint c = mesh.getVertices()[i+1];
        ofVec3f normal = ((b - a).cross(c - a)).normalize();
        
        mesh.addNormal(normal);
        mesh.addNormal(normal);
    }
    
    float t = ofGetElapsedTimef();
    light.setPosition(ofVec3f(cos(t*1.2)*400+200*-sin(t*0.5),
                              400*sin(t*0.5),
                              sin(t*1.6)*400)+200*-cos(t*0.5));
}



//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    
    cam.begin();
    
    light.draw();
    
    ofEnableLighting();
    light.enable();

    mesh.draw();
    
    light.disable();
    ofDisableLighting();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        mesh.save("mesh.ply");
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
