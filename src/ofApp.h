#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOsc.h"
#include "ofxCcv.h"

#define OSC_DESTINATION_DEFAULT "localhost"
#define OSC_ADDRESS_ROOT_DEFAULT "/wek/inputs"
#define OSC_PORT_DEFAULT 6448

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void sendOsc();
    
    ofxOscSender osc;
    ofxOscMessage msg;
    
    ofVideoGrabber cam;
    ofImage gray, edge, sobel;
    ofxCv::RunningBackground background;
    
    ofxCcv ccv;
    vector<float> classifierEncoding;
    vector<float> featureEncoding;
    
    string oscDestination, oscAddressRoot;
    int oscPort;
};
