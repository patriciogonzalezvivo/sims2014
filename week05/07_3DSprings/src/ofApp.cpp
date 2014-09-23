#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    light.setDiffuseColor(ofFloatColor(1.0,1.0,1.0));
    light.setPosition(ofPoint(0.0,0.0,0.0));
    
    /*
     
                  4 ---- 5
                 /|     /|
                0 ---- 1 |
                | |    | |
                | 7 ---|-6
                |/     |/
                3 ---- 2
     */
    
    nodes.push_back(new Particle(-30,-30,30));   // 0
    nodes.push_back(new Particle(30,-30,30));    // 1
    nodes.push_back(new Particle(30,30,30));     // 2
    nodes.push_back(new Particle(-30,30,30));    // 3
    
    nodes.push_back(new Particle(-30,-30,-30));  // 4
    nodes.push_back(new Particle(30,-30,-30));   // 5
    nodes.push_back(new Particle(30,30,-30));    // 6
    nodes.push_back(new Particle(-30,30,-30));   // 7
    
    //  FRONT
    joins.push_back(new Spring(nodes[0],nodes[1]));
    joins.push_back(new Spring(nodes[1],nodes[2]));
    joins.push_back(new Spring(nodes[2],nodes[3]));
    joins.push_back(new Spring(nodes[3],nodes[0]));
    
    //  UP
    joins.push_back(new Spring(nodes[4],nodes[5]));
    joins.push_back(new Spring(nodes[5],nodes[1]));
    joins.push_back(new Spring(nodes[0],nodes[4]));
    
    //  BACK
    joins.push_back(new Spring(nodes[4],nodes[7]));
    joins.push_back(new Spring(nodes[7],nodes[6]));
    joins.push_back(new Spring(nodes[6],nodes[5]));
    
    //  DOWN
    joins.push_back(new Spring(nodes[7],nodes[3]));
    joins.push_back(new Spring(nodes[6],nodes[2]));
    
    //  Crossed Springs
    joins.push_back(new Spring(nodes[2],nodes[0])); // front
    joins.push_back(new Spring(nodes[1],nodes[3])); // front
    
    joins.push_back(new Spring(nodes[1],nodes[4])); // up
    joins.push_back(new Spring(nodes[5],nodes[0])); // up
    
    joins.push_back(new Spring(nodes[5],nodes[7])); // back
    joins.push_back(new Spring(nodes[4],nodes[6])); // back
    
    joins.push_back(new Spring(nodes[6],nodes[3])); // Down
    joins.push_back(new Spring(nodes[7],nodes[2])); // Down
    
    joins.push_back(new Spring(nodes[1],nodes[6])); // right
    joins.push_back(new Spring(nodes[5],nodes[2])); // right
    
    joins.push_back(new Spring(nodes[4],nodes[3])); // left
    joins.push_back(new Spring(nodes[0],nodes[7])); // left
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    for (int i = 0; i < joins.size(); i++) {
        joins[i]->update();
    }
    
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->addForce(ofPoint(0,-0.3,0.0));
        nodes[i]->bounceOnBoxWalls(500);
        nodes[i]->update();
    }
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
	
    cam.begin();
    light.enable();
    ofEnableLighting();
    
    ofNoFill();
    ofDrawBox(1000);
    
    for (int i = 0; i < joins.size(); i++) {
        joins[i]->draw();
    }
    
    for (int i = 0; i < nodes.size(); i++) {
        nodes[i]->draw();
    }
    
    
    ofDisableLighting();
    light.disable();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
