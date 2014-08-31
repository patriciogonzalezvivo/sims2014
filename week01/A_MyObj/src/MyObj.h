//
//  MyObj.h
//
//  Created by Patricio Gonzalez Vivo on 8/27/14.
//
//

#pragma once

#include "ofMain.h"

class MyObj {
public:
    
    void setSrc(float _x, float _y);
    void setDst(float _x, float _y);
    
    void updatePct(float _pct); // _pct = [0.0 - 1.0]
    void powUpdatePct(float _pct, float _shaper);
    
    void draw();
    
private:
    ofPoint src, dst;
    ofPoint pos;
    
};