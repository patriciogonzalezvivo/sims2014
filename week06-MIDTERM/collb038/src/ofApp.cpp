#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    bloomCounter = 0;
    makeFlower();
}

//--------------------------------------------------------------

void ofApp::makeFlower(){

    //colorState = int(ofRandom(3));
    colorState++;
    colorMult = ofRandomuf();

    cout << colorState << endl;

    int totalParticles = 100;

    for (int i = 0; i < totalParticles; i++) {
        Particle newParticle;

        float spikeRot = ofRandom(15,30);
        spikeRots.push_back(spikeRot);
        ofPoint spikeSeed;
        spikeSeed.x = sin(i+ofRandom(19,20));
        spikeSeed.y = cos(i+ofRandom(19,20));

        float spikeScale = ofMap(i,0,totalParticles,2.5,1);

        newParticle.setInit(ofPoint(0,0),spikeSeed.scale(spikeScale));
        particles.push_back(newParticle);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

    minPetalLoc = ofGetWidth();

    for (int i = 0; i < particles.size(); i++) {
        particles[i].addForce(particles[i].getVelocity()*-0.005);
        particles[i].update();

        //if (ofGetFrameNum() > particles[i].breakPoint && particles.size() > 0){
        if (particles[i].getPetalLoc() < minPetalLoc){
               minPetalLoc = particles[i].getPetalLoc();
            }
    }

    if (minPetalLoc > 599) {
        particles.clear();
        bloomCounter++;
        if (bloomCounter >= 90){
            reset();
        }
    }
}

//--------------------------------------------------------------

void ofApp::reset(){
        //minPetalLoc = ofGetWidth();
        makeFlower();
        bloomCounter = 0;

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(ofGetKeyPressed('s')){
        ofBeginSaveScreenAsPDF(ofGetTimestampString()+".pdf");
    }

    ofBackground(213, 205, 169);
	ofSetColor(255);

    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.5,ofGetHeight()*0.5);

    for (auto &it: particles) {

        it.draw(colorState, colorMult);

    }

    ofPopMatrix();

    if(ofGetKeyPressed('s')){
        ofEndSaveScreenAsPDF();
    }

    string frameCount = ofToString(1000+ofGetFrameNum());
    //string fileName;
    string fileName = "Images2/" + frameCount + ".png";
    ofSaveScreen(fileName);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f'){
        ofToggleFullscreen();
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
