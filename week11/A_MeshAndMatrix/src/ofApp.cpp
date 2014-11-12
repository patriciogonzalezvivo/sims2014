#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
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
    
    //  We put the vertexes with the colors
    //  rotating their position using a matrix
    //
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
    
    //  We compute the normals
    //
    mesh.clearNormals();
    ofPoint up = ofPoint(0,0,1);
    mesh.addNormal(up);
    mesh.addNormal(up);
    for (int i = 2; i < mesh.getVertices().size(); i+=2) {
        ofPoint a1 = mesh.getVertices()[i-2];
        ofPoint b1 = mesh.getVertices()[i-1];
        ofPoint c1 = mesh.getVertices()[i];
        ofVec3f normal1 = ((b1 - a1).cross(c1 - a1)).normalize();
        mesh.addNormal(normal1);
        
        ofPoint a2 = mesh.getVertices()[i-1];
        ofPoint b2 = mesh.getVertices()[i];
        ofPoint c2 = mesh.getVertices()[i+1];
        ofVec3f normal2 = ((b2 - a2).cross(c2 - a2)).normalize();
        mesh.addNormal(normal2);
    }
    
    for (int i = 2; i < mesh.getVertices().size(); i+=2) {
        mesh.addIndex(i-2);
        mesh.addIndex(i-1);
        mesh.addIndex(i);
        
        mesh.addIndex(i-1);
        mesh.addIndex(i);
        mesh.addIndex(i+1);
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    //  We move the light
    //
    float t = ofGetElapsedTimef();
    light.setPosition(ofVec3f(cos(t*1.2)*400+200*-sin(t*0.5),
                              400*sin(t*0.5),
                              sin(t*1.6)*400)+200*-cos(t*0.5));
    
    //  Camera on
    //
    cam.begin();
    
    light.draw();
    
    //  Lights on
    //
    ofEnableLighting();
    light.enable();

    //  Draw the mes
    //
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
