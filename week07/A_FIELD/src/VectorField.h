//
//  VectorField.h
//  A_FIELD
//
//  Created by Patricio Gonzalez Vivo on 10/15/14.
//
//

#pragma once

#include "ofMain.h"

class VectorField {
public:
    
    VectorField();
    virtual ~VectorField();
    
    void setup(int _w, int _h, int  _res);
    
    void setNoise(float _time = 1.0);
    
    void addRepulsionForce(ofPoint _pos, float _rad, float _scale);
    
    ofPoint getForce(ofPoint _pos);
    
    void update();
    void draw();
    
    vector< vector<ofPoint> > table;
    
    int width, height, cols, rows, res;
};
