//
//  VectorField.cpp
//  A_FIELD
//
//  Created by Patricio Gonzalez Vivo on 10/15/14.
//
//

#include "VectorField.h"

VectorField::VectorField(){
    
}

VectorField::~VectorField(){
    
}

void VectorField::setup(int _w, int _h, int  _res){
    width = _w;
    height = _h;
    res = _res;
    
    cols = width / res;
    rows = height / res;

    for(int x = 0; x < cols; x++){
        
        vector<ofPoint> column;
        column.resize(rows);
        table.push_back(column);
        
        for(int y = 0; y < rows; y++){
            table[x][y] = ofPoint(ofRandom(-10,10),ofRandom(-10,10));
        }
    }
}

void VectorField::setNoise(float _time){
    for (int x = 0; x < table.size(); x++) {
        for (int y = 0; y < table[x].size(); y++) {
            float noise = ofMap( ofNoise(x*0.05, y*0.05, _time*0.1), 0, 1, 0, TWO_PI);
            table[x][y] = ofPoint( cos(noise), sin(noise) );
        }
    }
}

void VectorField::addRepulsionForce(ofPoint _pos, float _rad, float _scale){
    for (int x = 0; x < table.size(); x++) {
        for (int y = 0; y < table[x].size(); y++) {
            ofPoint cellPos = ofPoint(x*res, y*res);
            
            ofPoint diff = cellPos-_pos;
            float dist = diff.length();
            
            if(dist < _rad){
                diff *= 1. - dist/_rad;
                
                table[x][y] = diff*_scale;
            }
        }
    }
}



ofPoint VectorField::getForce(ofPoint _pos){
    _pos /= res;
    
    int x = ofClamp(int(_pos.x),0, cols-1);
    int y = ofClamp(int(_pos.y),0, rows-1);
    
    return table[x][y];
}

void VectorField::update(){
    for (int x = 0; x < table.size(); x++) {
        for (int y = 0; y < table[x].size(); y++) {
            table[x][y] *= 0.99;
        }
    }
}

void VectorField::draw(){
    for (int x = 0; x < table.size(); x++) {
        for (int y = 0; y < table[x].size(); y++) {
            ofPushMatrix();
            ofTranslate(x*res, y*res);
            ofPoint vel2color = table[x][y].getNormalized()*0.5+ofPoint(0.5,0.5,0.0);
            ofSetColor(vel2color.x*255, vel2color.y*255, 127);
            ofLine(ofPoint(0,0), table[x][y]);
            ofPopMatrix();
        }
    }
}