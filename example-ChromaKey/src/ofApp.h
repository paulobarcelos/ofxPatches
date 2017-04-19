#pragma once

#include "ofMain.h"
#include "ofxPatches.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

        ofVideoGrabber cam;
        ofVideoPlayer video;
        ofxPatches::Manager manager;
};
