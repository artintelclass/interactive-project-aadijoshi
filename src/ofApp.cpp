#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    cam.setup(640, 480);
    background.setLearningTime(900);

    ccv.setup("image-net-2012.sqlite3");
    if (!ccv.isLoaded()) return;
    
    // default settings
    oscDestination = OSC_DESTINATION_DEFAULT;
    oscAddressRoot = OSC_ADDRESS_ROOT_DEFAULT;
    oscPort = OSC_PORT_DEFAULT;
    
    osc.setup(oscDestination, oscPort);
    
    //edge.setImageType(OF_IMAGE_GRAYSCALE);
}


void ofApp::sendOsc() {
    msg.clear();
    msg.setAddress(oscAddressRoot);

    ofPixels &tp = edge.getPixels();
    
    for(int x = 0; x < edge.getWidth()*edge.getHeight()*3; x+=100){
        msg.addIntArg(tp[x]);
        msg.addIntArg(tp[x+1]);
        msg.addIntArg(tp[x+2]);
    }
    osc.sendMessage(msg);
}
 

/*
void ofApp::sendOsc() {
    featureEncoding = ccv.encode(edge, ccv.numLayers()-1);
    
    msg.clear();
    msg.setAddress(oscAddressRoot);
    for (int i=0; i<featureEncoding.size(); i++) {
        msg.addFloatArg(featureEncoding[i]);
    }
    osc.sendMessage(msg);
    
}
*/

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        convertColor(cam, gray, CV_RGB2GRAY);
        //background.update(cam, gray);
        Canny(gray, edge, 30, 50, 3);
        background.update(cam, edge);
        Sobel(gray, sobel);
        gray.update();
        sobel.update();
        edge.update();
    }
}

void ofApp::draw() {
    cam.draw(0, 0);
    gray.draw(0,480);
    edge.draw(640, 0);
    sobel.draw(640, 480);
    //sendOsc();
}
