#pragma once

#include "ofMain.h"
#include "Tail.h"

class Particle : public ofPoint {
public:
    Particle();

    void setInit(ofPoint _pos, ofPoint _vel = ofPoint(0,0));

    float   getRadius();
    ofPoint getPosition();
    ofPoint getVelocity();

    int colorMap;

    void addForce(ofPoint _force);

    bool haveNextNextGaussian = false;
    float nextNextGaussian;

    float ofxGaussian();


    void addGravity();
    void addWindForce();

    float getBreakPoint();
    float getPetalLoc();

    int breakCounter;
    float breakPoint;
    float rotSeed;
    float step;

    //char type;
    bool isLeaf;

    void update();
    void draw(int _colState, float _colMult);

    ofColor tailVary;
    float tailWidth;
    float velMag;

    vector <Tail> tail;

    ofPoint pos;
    ofPoint vel;
    ofPoint acc;

    float radius;
    //float damp;

        //void bounceOnWall();
    //void infiniteWalls();
        /*
    void addRepulsionForce(ofPoint _pos, float _rad, float _scale);
    void addAttractionForce(ofPoint _pos, float _rad, float _scale);
    void addClockwiseForce( ofPoint _pos, float _rad, float _scale);
    void addCounterClockwiseForce( ofPoint _pos, float _rad, float _scale);

    void addFlockingForce(vector<Particle> &_particles, float _neighborhoodRadius, float _alignmentScale = 0.33, float _separationScale = 0.33, float _cohesionScale = 0.33);
    float getHeading();
    */
    //void addWaveForce(float _heading);

    private:
};
