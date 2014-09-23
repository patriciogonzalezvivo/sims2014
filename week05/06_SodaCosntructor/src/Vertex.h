#ifndef VERTEX
#define VERTEX

#include "ofMain.h"

class Vertex : public ofPoint {
public:
    
    Vertex();
    
    void    setTexCoord(ofVec2f _pos){texCoord = _pos;};
    ofVec2f getTexCoord(){return texCoord; };
    
    void    addForce( ofPoint _force );
    
    void    addRepulsionForce(ofPoint p, float radius, float scale);
    void    addAttractionForce(ofPoint p, float radius, float scale);
    void    addRepulsionForce(Vertex &p, float radius, float scale);
    void    addAttractionForce(Vertex &p, float radius, float scale);
    void    addClockwiseForce(Vertex &p, float radius, float scale);
    void    addCounterClockwiseForce(Vertex &p, float radius, float scale);
    
    void    infinitWalls();
    void    bounceOffWalls();
    
    void    update();

    float   damping;
    
    int     nId;
private:
    ofVec2f texCoord;
    ofPoint vel;
    ofPoint acc;
};

#endif // Vertex_H
