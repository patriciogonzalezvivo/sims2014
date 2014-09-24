//
//  FlowField.cpp
//  VectorField
//
//  Created by Charlie Whitney on 10/7/13.
//
//

#include "FlowField.h"

FlowField::FlowField() {
    
}

void FlowField::setup( int width, int height, int res ) {
    fieldWidth = width;
    fieldHeight = height;
    resolution = res;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    
    for( int y=0; y<rows; y++){
        vector<ofVec2f> myList;
        flowList.push_back( myList );
        
        for( int x=0; x<cols; x++){
            ofVec2f dir(10,0);
            flowList[y].push_back( dir );
        }
    }
}

void FlowField::setRandom( const float &strength ) {
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            flowList[y][x].set( ofRandom(-1,1) * strength, ofRandom(-1,1) * strength );
        }
    }
}

void FlowField::setPerlin() {
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            float noise = ofMap( ofNoise(x*0.05, y*0.05), 0, 1, 0, TWO_PI);
            flowList[y][x].set( ofVec2f( cos(noise)*20, sin(noise)*20 ) );
        }
    }
}

void FlowField::update() {
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            flowList[y][x] *= 0.99;
            
            if( flowList[y][x].length() < 1.0){
                flowList[y][x].normalize();
            }
            
        }
    }
}

ofVec2f FlowField::getForceAtPosition(ofVec2f pos) {
    float pctX = pos.x / fieldWidth;
    float pctY = pos.y / fieldHeight;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    
    int xVal = ofClamp( pctX * cols, 0, cols-1 );
    int yVal = ofClamp( pctY * rows, 0, rows-1 );
    
    ofVec2f newPos;
    newPos.set( flowList[yVal][xVal] );
    
    return newPos;
}

void FlowField::addRepelForce(float x, float y, float radius, float strength) {
    
    float pctX = x / fieldWidth;
    float pctY = y / fieldWidth;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    
    int xVal = pctX * cols;
    int yVal = pctY * rows;
    
    
    ofVec2f mousePos(x, y);
    
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            ofVec2f np( x*resolution, y*resolution );
            
            if( np.distance(mousePos) < radius ){
                float pct = 1 - (np.distance(mousePos) / radius);
                
                // add strength in the direction it's already moving in
//                flowList[y][x] += flowList[y][x].normalized() * strength;
                
                // add strength away from the mouse
                ofVec2f dir = (np - mousePos);
                flowList[y][x] += dir.normalized() * strength;
            }
        }
    }
}

void FlowField::addAttractForce(float x, float y, float radius, float strength) {
    
    float pctX = x / fieldWidth;
    float pctY = y / fieldWidth;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    
    int xVal = pctX * cols;
    int yVal = pctY * rows;
    
    ofVec2f mousePos(x, y);
    
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            ofVec2f np( x*resolution, y*resolution );
            
            if( np.distance(mousePos) < radius ){
                float pct = 1 - (np.distance(mousePos) / radius);
                
                // add strength against the direction it's already moving in
//                flowList[y][x] -= flowList[y][x].normalized() * strength;
                
                // add strength towards the mouse
                ofVec2f dir = (np - mousePos);
                flowList[y][x] -= dir.normalized() * strength;
            }
        }
    }
}

void FlowField::addCircularForce(float x, float y, float radius, float strength) {
    
    float pctX = x / fieldWidth;
    float pctY = y / fieldWidth;
    
    int cols = fieldWidth / resolution;
    int rows = fieldHeight / resolution;
    
    int xVal = pctX * cols;
    int yVal = pctY * rows;
    
    ofVec2f mousePos(x, y);
    
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            ofVec2f np( x*resolution, y*resolution );
            
            if( np.distance(mousePos) < radius ){
                float pct = 1 - (np.distance(mousePos) / radius);
                
                // add strength towards the mouse
                ofVec2f dir = (np - mousePos);
                flowList[y][x].x -= dir.normalized().y * strength;
                flowList[y][x].y += dir.normalized().x * strength;
            }
        }
    }
}

void FlowField::draw() {
    for( int y=0; y<flowList.size(); y++){
        for( int x=0; x<flowList[y].size(); x++){
            ofVec2f np( x*resolution, y*resolution );
            drawVectorAt( flowList[y][x], np, flowList[y][x].length() );
            
            
            
            ofVec2f tmpPos(x*resolution, y*resolution);
        }
    }
}

void FlowField::drawVectorAt( const ofVec2f &vec, const ofVec2f &pos, const float &strength ) {
    ofVec2f np = pos;
    drawVector( np, np + vec.normalized() * strength, 5, 3 );
}

void FlowField::drawVector( const ofVec3f &start, const ofVec3f &end, float headLength, float headRadius ) {
	const int NUM_SEGMENTS = 32;
	float lineVerts[3*2];
	ofVec3f coneVerts[NUM_SEGMENTS+2];
	glEnableClientState( GL_VERTEX_ARRAY );
	glVertexPointer( 3, GL_FLOAT, 0, lineVerts );
	lineVerts[0] = start.x; lineVerts[1] = start.y; lineVerts[2] = start.z;
	lineVerts[3] = end.x; lineVerts[4] = end.y; lineVerts[5] = end.z;
	glDrawArrays( GL_LINES, 0, 2 );
	
	// Draw the cone
	ofVec3f axis = ( end - start ).normalized();
    ofVec3f temp = ( axis.dot( ofVec3f(0,1,0) ) > 0.999f ) ? axis.crossed( ofVec3f(1,0,0) ) : axis.crossed( ofVec3f(0,1,0) );
	ofVec3f left = ofVec3f(axis.crossed( temp )).normalized();
	ofVec3f up = axis.crossed( left ).normalized();
    
	glVertexPointer( 3, GL_FLOAT, 0, &coneVerts[0].x );
	coneVerts[0] = ofVec3f( end + axis * headLength );
	for( int s = 0; s <= NUM_SEGMENTS; ++s ) {
		float t = (float)s / (float)NUM_SEGMENTS;
		coneVerts[s+1] = ofVec3f( end + left * headRadius * cos( t * 2.0f * 3.14159f )
                                 + up * headRadius * sin( t * 2.0f * 3.14159f ) );
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, NUM_SEGMENTS+2 );
    
	// draw the cap
	glVertexPointer( 3, GL_FLOAT, 0, &coneVerts[0].x );
	coneVerts[0] = end;
	for( int s = 0; s <= NUM_SEGMENTS; ++s ) {
		float t = s / (float)NUM_SEGMENTS;
		coneVerts[s+1] = ofVec3f( end - left * headRadius * (float)cos( t * 2 * 3.14159f )
                                 + up * headRadius * (float)sin( t * 2 * 3.14159f ) );
	}
	glDrawArrays( GL_TRIANGLE_FAN, 0, NUM_SEGMENTS+2 );
    
	glDisableClientState( GL_VERTEX_ARRAY );
}