#pragma once

#include "ofMain.h"
#include "ofxPatches/Constants.h"
#include "ofxPatches/PatchOutput.h"
#include "ofxPatches/Patch.h"
#include "ofxPatches/Manager.h"

namespace ofxPatches {
	
	class PatchInput {
	public:
		PatchInput(Patch * parent = NULL, Patch * patch = NULL, int inputIndex = -1);
		~PatchInput();
		
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
        void mouseScrolled(ofMouseEventArgs &args){};
        void mouseEntered(ofMouseEventArgs &args){};
        void mouseExited(ofMouseEventArgs &args){};
		
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
