#pragma once

//Comment this line in case you don't want to use the built-in GUI
#define OFX_GPU_CV_USE_GUI

#include "ofMain.h"
#include "ofxGPUCv.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	ofVideoGrabber cam;
	ofxGPUCv::RedBoost redBoost;
	ofxGPUCv::Empty input;
	//ofxGPUCv::Manager stack;
	
		
};
