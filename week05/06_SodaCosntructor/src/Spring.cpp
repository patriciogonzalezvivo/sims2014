#include "Spring.h"

//---------------------------------------------------------------------
Spring::Spring(){
	vertexA = NULL;
	vertexB = NULL;
}

//---------------------------------------------------------------------
void Spring::update(){
	if ((vertexA == NULL) || (vertexB == NULL)){
		return;
	}
	
	float mutualDist = (*vertexA - *vertexB).length();
	float springForce = (k * (dist - mutualDist));
	ofPoint frcToAdd = (*vertexA - *vertexB).normalized() * springForce;
	
	vertexA->addForce(frcToAdd);
    frcToAdd *= -1;
	vertexB->addForce(frcToAdd);
}


//---------------------------------------------------------------------
void Spring::draw(){
	
	if ((vertexA == NULL) || (vertexB == NULL)){
		return;
	}
	
	ofLine( *vertexA, *vertexB);
}