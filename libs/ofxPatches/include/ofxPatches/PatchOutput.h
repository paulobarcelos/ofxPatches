#pragma once

#include "ofMain.h"
#include "ofxPatches/Constants.h"
#include "ofxPatches/Patch.h"
#include "ofxPatches/PatchInput.h"
#include "ofxPatches/Manager.h"

namespace ofxPatches {
	
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