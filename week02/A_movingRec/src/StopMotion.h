//
//  StopMotion.h
//  week1-movingRec
//
//  Created by Patricio Gonzalez Vivo on 9/15/12.
//
//

#ifndef STOPMOTION
#define STOPMOTION

#include "ofMain.h"
#include "ofxXmlSettings.h"

typedef struct{
    unsigned char * pixels;
    unsigned long timeStamp;
    ofPoint point;
} Frame;

class StopMotion : ofRectangle {
public:

    StopMotion();
    
    void    allocate( int _width, int _height );
    
    void    load(string _folder);
    void    save(string _folder = "NONE");
    void    savePoints( string _folder);
    
    int     size();
    void    clear();
    Frame&  operator[](int _nFrame){ if ((_nFrame < buffer.size()) && (_nFrame >= 0) ) return buffer[_nFrame]; };
    void    addFrame( unsigned char * _pixels );
    
    void    prevFrame();
    void    nextFrame();
    
    void    update();
    void    draw(int _x, int _y, int _width = -1, int _height = -1);
    
private:
    vector< Frame > buffer;
    
    ofImage activeFrame;
    
    string  folderName;
    unsigned long startTime;
    int     nFrame;
};

#endif
