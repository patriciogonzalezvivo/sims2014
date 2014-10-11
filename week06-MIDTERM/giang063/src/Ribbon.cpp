//
//  Ribbon.cpp
//  06_midterm
//
//  Created by Gabriel Gianordoli on 10/5/14.
//
//

#include "Ribbon.h"

void Ribbon::setup(float _x, float _y){
    addPoint(_x, _y);
}

void Ribbon::connectSpring(){
    // Connect
    for(int i = 0; i < myParticles.size() - 1; i++){
        ofPoint dist = myParticles[i].pos - myParticles[i + 1].pos;
        float len = dist.length();
        Spring newSpring;
        newSpring.set( &myParticles[i], &myParticles[i + 1], 0.05, len);
        springList.push_back( newSpring );
    }
}

// SPRING ------------------------------------------------------------
void Ribbon::updateSpring(float _x, float _y, float _modifierRadius, float _modifierStrength){
    ofPoint mouse = ofPoint(_x, _y);

    for( int i = 0; i < myParticles.size(); i++ ){
        ofPoint force = mouse - myParticles[i].pos;
        if (force.length() < _modifierRadius) {
            force.normalize();
            myParticles[i].addForce(-force);
        }
        myParticles[i].update();
        currentLine[i] = myParticles[i].pos;
    }
    
    for( int i=0; i<springList.size(); i++ ){
        springList[i].update();
    }
}

// WAVE ------------------------------------------------------------
void Ribbon::updateWave(float _amplitude, int _frequencyInSeconds, int _nModifier){
    
    float amplitude = _amplitude;
    int frequencyInSeconds = _frequencyInSeconds;
    float frameRate = 60.0f;
    int nModifier = _nModifier;
    
    for (int i = 0; i < myParticles.size(); i++) {

        float frequency = (ofGetElapsedTimeMillis() + (i * nModifier) )/(frameRate * frequencyInSeconds);
        float z = sin(frequency) * amplitude;
        
        myParticles[i].pos.z = z;
        currentLine[i] = myParticles[i].pos;
    }
}


// MODIFY ------------------------------------------------------------
void Ribbon::updateModify(float _x, float _y, float _modifierRadius, float _modifierStrength){
    ofPoint mousePos = ofPoint(_x, _y);
    for (int i = 0; i < myParticles.size(); i++) {
        myParticles[i].update(mousePos, _modifierRadius, _modifierStrength);
        currentLine[i] = myParticles[i].pos;
    }
}

//------------------------------------------------------------
void Ribbon::applySmoothing(int _shapeSmoothing){
    // Update line
    currentLine = currentLine.getSmoothed(_shapeSmoothing, 0);
    
    // Erase particles vector
    while(myParticles.size() > 0){
        int i = myParticles.size() - 1;
        myParticles.erase(myParticles.begin() + i);
    }
    
    // Update particles vector
    vector<ofPoint> path = currentLine.getVertices();
    for (ofPoint p : path) {
        Particle newParticle;
        newParticle.setup(p.x, p.y);
        myParticles.push_back(newParticle);
    }
}

//------------------------------------------------------------
void Ribbon::resetSmoothing(){
    currentLine = originalLine;
}

//------------------------------------------------------------
void Ribbon::addPoint(float _x, float _y){
    ofPoint pos = ofPoint(_x, _y);
    originalLine.addVertex(pos);
    currentLine = originalLine;
    
    Particle newParticle;
    newParticle.setup(_x, _y);
    myParticles.push_back(newParticle);
}


//------------------------------------------------------------
void Ribbon::draw(bool _useCamera, float _thickness, float _zDepth){
    
    if(!_useCamera){
        ofNoFill();
        ofSetLineWidth(_thickness);
        ofSetColor(255);
        currentLine.draw();
    
    }else{
        vector<ofPoint> path = currentLine.getVertices();
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        for(unsigned int i = 1; i < path.size(); i++){
            
            //find this point and the next point
            ofVec3f thisPoint = ofPoint(path[i-1].x, path[i-1].y, path[i-1].z + ((i-1) * _zDepth));
            ofVec3f nextPoint = ofPoint(path[i].x, path[i].y, path[i].z + (i * _zDepth));
            
            //get the direction from one to the next.
            //the ribbon should fan out from this direction
            ofVec3f direction = (nextPoint - thisPoint);
            
            //get the distance from one point to the next
            float distance = direction.length();
            
            //get the normalized direction. normalized vectors always have a length of one
            //and are really useful for representing directions as opposed to something with length
            ofVec3f unitDirection = direction.normalized();
            
            //find both directions to the left and to the right
            ofVec3f toTheLeft = unitDirection.getRotated(-90, ofVec3f(0,0,1));
            ofVec3f toTheRight = unitDirection.getRotated(90, ofVec3f(0,0,1));

            
            //use the map function to determine the distance.
            //the longer the distance, the narrower the originalLine.
            //this makes it look a bit like brush strokes
    //		float thickness = ofMap(distance, 0, 60, 20, 2, true);
            float thickness = _thickness;
            
            //calculate the path to the left and to the right
            //by extending the current point in the direction of left/right by the length
            ofVec3f leftPoint = thisPoint+toTheLeft*thickness;
            ofVec3f rightPoint = thisPoint+toTheRight*thickness;
            
            //add these path to the triangle strip
            mesh.addVertex(ofVec3f(leftPoint.x, leftPoint.y, leftPoint.z));
            mesh.addVertex(ofVec3f(rightPoint.x, rightPoint.y, rightPoint.z));
        }
        
        //end the shape
        mesh.draw();
    }
}