#pragma once

#include "ofMain.h"
#include "Flock.h"
#include "Global.h"
#include "ofxSyphon.h"



class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    ofSerial getSerial();
    
    ofColor c;
    
    char x;
    
    Flock flock;

    int H;
    int S;
    int L;
    
    ofSerial serial;
    
    ofArduino arduino;
    bool bSetupArduino;            // flag variable for setting up arduino once
    
    void musicReact();
    
    ofxSyphonServer server;
    
private:
    
    void setupArduino(const int & version);
    void analogPinChanged(const int & pinNum);
    void updateArduino();
};

