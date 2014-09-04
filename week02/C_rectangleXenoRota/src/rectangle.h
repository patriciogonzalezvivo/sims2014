#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ofMain.h"

class rectangle : public ofPoint {
public:
	
    rectangle();
	
    void	draw();
    void	xenoToPoint(ofPoint _target);
	
    ofPoint target;
    float   catchUpSpeed;
	float   angle;

};

#endif // RECTANGLE_H
