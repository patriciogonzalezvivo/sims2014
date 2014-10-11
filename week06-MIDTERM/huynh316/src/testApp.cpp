#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofSetVerticalSync(true);
	ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofBackground(50,100,255);
	//background trail
	//ofSetBackgroundAuto(false);
	
	//flock
	flocker.addParticle( 1000 );
    
    ofEnableDepthTest();
    myCam.setDistance(1000);
	//end flock
	
	waterSound.loadSound("audio/droplets.wav");
	
    for( int i=0; i<6; i++ ){
        SpringJoint sj;
        sj.pos = ofVec3f( ofGetWindowWidth() / 2, (ofGetWindowHeight() + 130 - i*195, 0));
        jointList.push_back( sj );
    }
    
    
    Spring spring1, spring2, spring3, spring4, spring5, spring6;
    
	

	spring1.set( &jointList[1], &jointList[2], 0.005, 150.0 );
    spring2.set( &jointList[2], &jointList[3], 0.003, 200.0 );
    spring3.set( &jointList[3], &jointList[4], 0.003, 150.0 );
	spring4.set( &jointList[5], &jointList[4], 0.003, 200.0 );
	spring5.set( &jointList[5], &jointList[1], 0.003, 150.0 );

	
	//lead spring
	spring6.set( &jointList[0], &jointList[1], 0.05, 50.0 );	

    
    springList.push_back( spring1 );
    springList.push_back( spring2 );
    springList.push_back( spring3 );
	springList.push_back( spring4 );
	springList.push_back( spring5 );
	springList.push_back( spring6 );
    
    bDragging = false;
    
//    ofSetFrameRate(60.0);
//    ofSetVerticalSync( true );
//    ofBackground(0);
}

/**
 *  We're working with Hookes law here http://en.wikipedia.org/wiki/Hooke's_law
 *  F = -k * x;
 */

//--------------------------------------------------------------
void testApp::update(){
    
	//flock
	flocker.applyForces(80, 0.4, 0.75);
    flocker.update();
	//end flock
	
	ofSoundUpdate();
	
    if( bDragging ){
        return;
    }
    
    for( int i=0; i<springList.size(); i++ ){
        springList[i].update();
		
		
    }

    
    for( int i=0; i<jointList.size(); i++ ){
        //jointList[i].update();
		//xenos
				if (i==0) {
					jointList[i].xenoToPoint(mouseX,mouseY);
				}else {
					jointList[i].xenoToPoint(jointList[i-1].pos.x, jointList[i-1].pos.y);
				}
		
    }
}

//--------------------------------------------------------------
void testApp::draw(){
		
	//flock
	myCam.begin();
    
    ofPushMatrix();{
       
		ofLight();
		flocker.draw();

		
    }ofPopMatrix();
    
    myCam.end();
	//end flock
			
    for( int i=0; i<springList.size(); i++ ){
        springList[i].draw();

		
    }
    
    for( int i=0; i<jointList.size(); i++ ){
        jointList[i].draw();
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
	if (key == 'w') {	
		
    int rand = floor( ofRandom( jointList.size() ) );
	
    jointList[rand].applyForce( ofVec3f(ofRandom(-10, 10), 0, ofRandom(-10,10)) );
	}
	
	if (key == ' ') {
		ofToggleFullscreen();
	}
	
	if (key == 'a') {
		ofSetBackgroundAuto(false);
	}
	
	if (key == 'd') {
		ofSetBackgroundAuto(true);
	}
	
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	    flocker.addParticle( 50 );
		waterSound.play();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    bDragging = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	
}
