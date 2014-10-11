//
//  Ribbon.h
//  06_midterm
//
//  Created by Gabriel Gianordoli on 10/5/14.
//
//

#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Spring.h"

class Ribbon{
public:
    void setup(float _x, float _y);

    // spring
    void updateSpring(float _x, float _y, float _modifierRadius, float _modifierStrength);

    // wave
    void updateWave(float _amplitude, int _frequencyInSeconds, int _nModifier);
    
    // modify
    void updateModify(float _x, float _y, float _modifierRadius, float _modifierStrength);
    
    void draw(bool _useCamera, float _thickness, float _zDepth);
    
    void connectSpring();
    
    // Drawing
    void addPoint(float _x, float _y);
    void applySmoothing(int _shapeSmoothing);
    void resetSmoothing();
    
    // ofPolyline is actually ONE line
    // It would be the same as a vector of ofPoint.
    // But it has some special properties, like the smoothing feature
    ofPolyline originalLine;    // this is the original line drawing
    ofPolyline currentLine;     // this is the smoothed line drawing
                                // We always draw the CURRENT line
                                // but we keep the original as an option to reset
    
    // each vertex from our polyLine will respond to physics
    vector<Particle> myParticles;
    
    vector<Spring> springList;
};