#pragma once

#include "ofMain.h"
#include "ofxGPUCv/PatchOutput.h"
#include "ofxGPUCv/Patch.h"
#include "ofxGPUCv/Manager.h"


#define OFX_GPUCV_PATCH_CONNECTOR_SIZE 7

namespace ofxGPUCv {
	
	class PatchInput {
	public:
		PatchInput(Patch * parent = NULL, Patch * patch = NULL, int inputIndex = -1);
		
		void setParent(Patch * parent);		
		void setPatch(Patch * patch);		
		void setInputIndex(int inputIndex);
		
		Patch * getPatch();
		Patch * getParent();
		int getInputIndex();
		
		void mouseMoved(ofMouseEventArgs & args);
		void mousePressed(ofMouseEventArgs & args);
		void mouseDragged(ofMouseEventArgs & args);
		void mouseReleased(ofMouseEventArgs & args);
		
		void draw();
		
		ofRectangle getShape();
		
		Patch * getPatchIfInside(float x, float y);
	
		Patch * parent;
		Patch * patch;
		int inputIndex;
		bool isConnecting;
		ofPoint mouse;
		
	};
}