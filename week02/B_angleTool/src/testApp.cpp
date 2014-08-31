#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofSetCircleResolution(100);
    ofEnableSmoothing();
    
    //  This is the center position of the diagram
    //
    center.set(250,250);
    ofSetWindowShape(1024, 540);
    
    angle   = 0.0f;
    radius  = 140.0f;
}

//--------------------------------------------------------------
void testApp::update(){
    
    if ( bPlay ){
        //  If it's playing recursively add 
        //
        angle += 1.0/ofGetFrameRate();
        
        //  Just for making it clear angle could be more than the 2PI
        //
        if (angle > PI*2)
            angle = 0.0f;
    }
    
    //  Get the cartesian 
    //
    dotPos.x = cos(angle) * radius;
    dotPos.y = sin(angle) * radius;
    
    //  Store the Y (sin) position
    //
    sinHistory.push_back(dotPos.y);
    if (sinHistory.size() > 400){
        sinHistory.erase(sinHistory.begin());
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    
    ofDrawBitmapString("Press a key or drag with your mouse", 15,15);
    
    ofPushMatrix();
    ofTranslate(center);
    
    //  Draw Cartesian
    //
    float lenghtOfAxis = 200;
    ofSetColor(100);
    
    ofLine(ofPoint(-lenghtOfAxis,0),
           ofPoint(lenghtOfAxis,0));
    ofDrawBitmapString("-X", -lenghtOfAxis - 25, 5);
    ofDrawBitmapString("X", lenghtOfAxis + 5, 5);
    ofLine(ofPoint(0,-lenghtOfAxis),
           ofPoint(0,lenghtOfAxis));
    ofDrawBitmapString("-Y", -11, -lenghtOfAxis - 5);
    ofDrawBitmapString("Y", -3, lenghtOfAxis + 15);

    //  Draw Vector
    //
    ofSetColor(255);
    ofLine(0,0, dotPos.x, dotPos.y);
    
    //  Draw Vector projections on axis
    //
    ofSetColor(255);
    ofLine(0,0,dotPos.x,0); // X
    ofLine(0,0,0,dotPos.y); // Y
    ofSetColor(255,50);
    ofLine(dotPos.x,dotPos.y,dotPos.x,0); // X
    ofLine(dotPos.x,dotPos.y,0,dotPos.y); // Y
    
    //  Draw Dot
    //
    drawDot( dotPos );
    
    //  Draw angle References
    //
    ofPolyline  angleLine;
    angleLine.arc(0, 0, radius*0.3, radius*0.3, 0, ofRadToDeg(angle));
    ofNoFill();
    ofSetColor(255,180);
    angleLine.draw();
    ofDrawBitmapString("a = " + ofToString(angle,2) + " (" + ofToString((int)(ofRadToDeg(angle))) + " deg)", radius*0.3 + 5, 15);
    
    //  Draw sin and cos proyected dots
    //
    ofSetColor(255,100);
    ofLine(-radius, lenghtOfAxis + 30, radius, lenghtOfAxis + 30);
    ofDrawBitmapString("-1", -radius - 15, lenghtOfAxis + 30 + 5);
    ofDrawBitmapString("1", radius + 5, lenghtOfAxis + 30 + 5);
    ofPoint cosPos = ofPoint(dotPos.x,  lenghtOfAxis + 30);
    ofDrawBitmapString("cos(a).r = " + ofToString( cos(angle),2) , cosPos + ofPoint(-3,15));
    drawDot(cosPos);
    ofLine(lenghtOfAxis + 30,-radius, lenghtOfAxis + 30,radius);
    ofDrawBitmapString("-1", lenghtOfAxis + 30 - 12,-radius -5);
    ofDrawBitmapString("1", lenghtOfAxis + 30 - 3, radius + 15 );
    ofPoint sinPos = ofPoint(lenghtOfAxis + 30, dotPos.y);
    ofDrawBitmapString("sin(a).r = " + ofToString( sin(angle),2) , sinPos + ofPoint(15,3));
    drawDot(sinPos);
    
    //  Draw the history of sin throught time
    //
    ofMesh lineMesh;
    lineMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
    
    for (int i = sinHistory.size() -1 ; i > 0 ; i--){
        float alpha = ofMap(i+1, 1,sinHistory.size(), 0.0,1.0);
        
        lineMesh.addColor( ofFloatColor(1.0, alpha) );
        lineMesh.addVertex( ofPoint(lenghtOfAxis + 30 + (sinHistory.size()-i), sinHistory[i]) );
    }
    
    ofSetColor(255);
    lineMesh.draw();
    
    
    ofPopMatrix();
}

void testApp::drawDot(ofPoint _pos){
    ofPushStyle();
    
    ofFill();
    ofSetColor(255, 0,0);
    ofCircle(_pos, 5);
    
    ofPopStyle();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    bPlay = !bPlay;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    ofPoint mouse = ofPoint(x,y) - center;
    
    //  Get the angle of the mouse position
    //
    float angleToMouse = atan2( mouse.y, mouse.x );
        
    /* ATAN2 ( http://processing.org/reference/atan2_.html )
     
     Calculates the angle (in radians) from a specified point to the 
     coordinate origin as measured from the positive x-axis. Values 
     are returned as a float in the range from PI to -PI. The atan2() 
     function is most often used for orienting geometry to the position 
     of the cursor. Note: The y-coordinate of the point is the first 
     parameter, and the x-coordinate is the second parameter, due the 
     the structure of calculating the tangent.
     
     Syntax
        atan2(y, x)
     
     Parameters
        y	float: y-coordinate of the point
        x	float: x-coordinate of the point
     */
    
    if (angleToMouse < 0){
        angle = PI + (PI + angleToMouse);
    } else {
        angle = angleToMouse;
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

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