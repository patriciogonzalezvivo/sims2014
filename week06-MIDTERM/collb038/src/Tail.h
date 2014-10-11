#pragma once

#ifndef TAIL_H
#define TAIL_H

#include "ofMain.h"


class Tail
{
    public:
        Tail();
        void setInit(ofPoint _pos, ofColor _blueVary, float _tailRad, int _tailCol);
        void update();
        void draw(int _sinOffset, int _tailGrow);
        void addWind(float _windSpeed);
        void addGravity(float _gravity);

        float tailRad;
        int tailCol;
        float leafMag;

        ofPoint pos;
        ofPoint vel;
        ofPoint acc;

        ofPoint getPosition();

        int blueVary;
        int sinOffset;
        ofColor tailColor;


        virtual ~Tail();
    protected:
    private:
};

#endif // TAIL_H
