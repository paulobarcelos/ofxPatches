#pragma once

#include "ofMain.h"
#include "ofxGPUCv/Constants.h"
#include "ofxGPUCv/Patch.h"
#include "ofxGPUCv/PatchInput.h"
#include "ofxGPUCv/Manager.h"


namespace ofxGPUCv {
	
	class PatchOutput {
	public:
		PatchOutput(Patch * parent = NULL);
		
		void setParent(Patch * parent);		
		
		Patch * getParent();
		
		void draw();
		
		ofRectangle getShape();
		
		Patch * getPatchIfInside(float x, float y);

		Patch * parent;		
	};
}