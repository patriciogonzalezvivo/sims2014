//
//  MyObj.cpp
//  00_test
//
//  Created by Patricio Gonzalez Vivo on 8/27/14.
//
//

#include "MyObj.h"

void MyObj::setSrc(float _x, float _y){
    src.set(_x,_y);
}

void MyObj::setDst(float _x, float _y){
    dst.set(_x, _y);
}

void MyObj::updatePct(float _pct){
    pos = dst * _pct + src *(1.0-_pct);
}

void MyObj::powUpdatePct(float _pct, float _shaper){
    
    float powPct = powf(_pct, _shaper);
    pos = dst * powPct + src *(1.0-powPct);
}

void MyObj::draw(){
    
    ofSetColor(255,255,255,200);
    ofLine(src, dst);
    
    ofSetColor(ofColor::red);
    ofCircle(pos, 10);
    
    
}