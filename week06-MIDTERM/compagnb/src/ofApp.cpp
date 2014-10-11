#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    gridWidth = 200;
    gridHeight = 200;
    
    // set up the vertices and colors
    //first on the y axis
    for(int y = 0; y < gridWidth; y++){
        //now on the x axis
        for(int x = 0; x < gridHeight; x++){
            myMesh.addVertex(ofPoint((x-gridWidth*0.5)*6, (y-gridHeight*0.5)*6, 0));
            myMesh.addColor(ofColor(0,0,0));
        }
    }
    
    // set up triangles indices
    //first on the y axis
    for(int y = 0; y < gridWidth-1; y++){
        //now on the x axis
        for(int x = 0; x < gridHeight-1; x++){
            i1 = x + gridWidth * y;
			i2 = x+1 + gridWidth * y;
			i3 = x + gridWidth * (y+1);
			i4 = x+1 + gridWidth * (y+1);
            myMesh.addTriangle( i1, i2, i3);
            myMesh.addTriangle( i2, i4, i3);
        }
    }
    setNormals(myMesh);
    myLight.enable();

}

//--------------------------------------------------------------
void ofApp::update(){
    float time = ofGetElapsedTimef();	//Get time
	//Change vertices
	for (int y=0; y<gridHeight; y++) {
		for (int x=0; x<gridWidth; x++) {
			int i = x + gridWidth * y;			//Vertex index
			ofPoint p = myMesh.getVertex( i );
            
			//Get Perlin noise value
			float value = ofNoise( x * 0.05, y * 0.05, time * 0.5 );
            
			//Change z-coordinate of vertex
			p.z = value * 100;
			myMesh.setVertex( i, p );
            
			//Change color of vertex
			myMesh.setColor( i, ofColor( value*255, value * 255, 255 ) );
		}
	}
	setNormals( myMesh );	//Update the normals
    
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofEnableDepthTest();				//Enable z-buffering
    
	//Set a gradient background from white to gray
	ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    
	ofPushMatrix();						//Store the coordinate system
    
	//Move the coordinate center to screen's center
	ofTranslate( ofGetWidth()*0.5, ofGetHeight()*0.5, 0 );
    
	//Calculate the rotation angle
	float time = ofGetElapsedTimef();   //Get time in seconds
	float angle = time * 20;			//Compute angle. We rotate at speed
	//20 degrees per second
	ofRotate( 30, 1, 0, 0 );			//Rotate coordinate system
	ofRotate( angle, 0, 0, 1 );
    
	//Draw mesh
	//Here ofSetColor() does not affects the result of drawing,
	//because the mesh has its own vertices' colors
	myMesh.drawWireframe();
    
	ofPopMatrix();      //Restore the coordinate system
    
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

//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void ofApp::setNormals(ofMesh &mesh){
    
	//The number of the vertices
	int nV = mesh.getNumVertices();
    
	//The number of the triangles
	int nT = mesh.getNumIndices() / 3;
    
	vector<ofPoint> norm( nV ); //Array for the normals
    
	//Scan all the triangles. For each triangle add its
	//normal to norm's vectors of triangle's vertices
	for (int t=0; t<nT; t++) {
        
		//Get indices of the triangle t
		int i1 = mesh.getIndex( 3 * t );
		int i2 = mesh.getIndex( 3 * t + 1 );
		int i3 = mesh.getIndex( 3 * t + 2 );
        
		//Get vertices of the triangle
		const ofPoint &v1 = mesh.getVertex( i1 );
		const ofPoint &v2 = mesh.getVertex( i2 );
		const ofPoint &v3 = mesh.getVertex( i3 );
        
		//Compute the triangle's normal
		ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
		//Accumulate it to norm array for i1, i2, i3
		norm[ i1 ] += dir;
		norm[ i2 ] += dir;
		norm[ i3 ] += dir;
	}
    
	//Normalize the normal's length
	for (int i=0; i<nV; i++) {
		norm[i].normalize();
	}
    
	//Set the normals to mesh
	mesh.clearNormals();
	mesh.addNormals( norm );
}


