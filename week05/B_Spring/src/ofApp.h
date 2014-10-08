#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "Particle.h"
#include "Spring.h"

class ofApp : public ofSimpleApp{
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
    void keyReleased (int key);
    
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased();
    
    Particle particles[3];
    Spring  springs[2];
};

#endif
	
