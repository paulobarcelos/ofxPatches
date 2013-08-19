#pragma once

#include "ofMain.h"
#include "ofxPatches.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		ofImage foreground;
		ofImage background;
		ofxPatches::Manager manager;		
};
