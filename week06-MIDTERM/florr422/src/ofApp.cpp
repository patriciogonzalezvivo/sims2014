#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    num = 2000;

    for(int i =0; i < num; i++){
        ofPoint p;
        points.push_back(p);
        
        float t;
        theta.push_back(t);
        
        float ph;
        phi.push_back(ph);
        
        int r;
        radius.push_back(r);
        
        float chPh;
        changePhi.push_back(chPh);
        
        float cT;
        changeTheta.push_back(cT);
        
    }

    //put the sphere in the setup function so all the points would not be moving
    for(int i = 0; i < num; i++){

//points for a randomly distributed sphere
        
        theta[i] = ofRandom(0,2*PI);
        phi[i] = ofRandom(0,PI);
        radius[i] = ofRandom(180,220);
        
        points[i] = ofPoint(radius[i]*cos(theta[i])*sin(phi[i]), radius[i]*sin(theta[i])*sin(phi[i]), radius[i]*cos(phi[i]));
    
        changeTheta[i] = ofRandom(0,0.01);
        changePhi[i] = ofRandom(0,0.01);
    
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(29,144,213);

    cam.begin();
    
    for(int i = 0; i < num; i++){
        
        points[i] = ofPoint(radius[i]*cos(theta[i])*sin(phi[i]), radius[i]*sin(theta[i])*sin(phi[i]), radius[i]*cos(phi[i]));

        
        if(radius[i] < 300){
            radius[i] ++;
        }

        theta[i] += changeTheta[i];
        phi[i] += changePhi[i];
    }
    
    for(int i = 0; i< num; i++){
        for(int j = i+1; j < num; j++){
            dist = pow(points[i].x - points[j].x, 2) + pow(points[i].y - points[j].y, 2) + pow(points[i].z - points[j].z, 2);
               // dist = sqrt(dist);
                
            if (dist < 2*mouseX) {
                ofSetColor(255, 50);
                ofSetLineWidth(1.5);
                ofLine(points[i].x, points[i].y, points[i].z, points[j].x, points[j].y, points[j].z);
            }

        }
    }
    cam.end();
    
   // cout<<ofToString("frame"+ofToString(ofGetFrameNum(), 1, 5, '0'))<<endl;
   //ofSaveScreen(ofToString("frame"+ofToString(ofGetFrameNum(), 1, 5, '0')+".png"));
    
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
