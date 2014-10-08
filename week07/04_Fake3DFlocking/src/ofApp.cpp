#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gui.setup(); // most of the time you don't need a name
    gui.add(speed.setup( "Speed", 0.999, 0.99, 1 ));
    gui.add(flocking.setup( "Flocking Scale", 0.05, 0.01, 0.1 ));
    gui.add(turbulence.setup( "Turbulence", 0.0001, 0., 0.09 ));
    gui.add(neigbordhood.setup( "Neigbordhood", 300., 1, 1000.1 ));
    gui.add(independence.setup( "Independece", 0.0001, 0., 0.01 ));
    
    
    //  Create 100 Particles
    //
    for (int i = 0; i < 10000; i++) {
        Particle newParticle;
        newParticle.setInit(ofPoint(ofRandom(-10,10),ofRandom(-10,10), 0), ofPoint(ofRandom(-0.1,0.1),ofRandom(-0.1,0.1),0.0));
        particles.push_back(newParticle);
    }
    
    globalOffset.set(0,0,0);
}

//--------------------------------------------------------------
void ofApp::update(){

    for (int i = 0; i < particles.size(); i++) {
        particles[i].applyFlockingForce(&globalOffset,neigbordhood,independence,flocking);
        particles[i].update(speed);
    }
    
    globalOffset += ofPoint(turbulence/neigbordhood, turbulence/neigbordhood, turbulence/neigbordhood);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
	ofSetColor(255);
    
    ofPushMatrix();
    cam.begin();
//    light.enable();
//    ofEnableLighting();
//    glEnable(GL_DEPTH_TEST);
    
    glBegin(GL_POINTS);
    for (int i = 0; i < particles.size(); i++) {
        particles[i].draw();
    }
    glEnd();
    
//    glDisable(GL_DEPTH_TEST);
//    ofDisableLighting();
//    light.disable();
    cam.end();
    ofPopMatrix();
    
    if( bHide ){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 'h' ){
        bHide = !bHide;
    }
    if(key == 's') {
        gui.saveToFile("settings.xml");
    }
    if(key == 'l') {
        gui.loadFromFile("settings.xml");
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
