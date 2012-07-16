#pragma once

#include "ofMain.h"
#include "ofxGPUCv/ExtendedFXObject.h"

#define OFX_GPUCV_PATCH_CONNECTOR_SIZE 7

namespace ofxGPUCv {
	
	class PatchInput; // forward declaration, actual header is included in cpp!
	class PatchOutput; // forward declaration, actual header is included in cpp!
	class Manager; // forward declaration, actual header is included in cpp!

	class Patch : public ExtendedFXObject {
		friend class PatchInput;
		friend class PatchOutput;
		friend class Manager;
	public:
		Patch();
		~Patch();
		virtual Patch * create() { return new Patch();};
		
		void setup(Manager * manager, string name = "", string filename = "", int id = rand());
		
		bool compileCode();	
		void update();		
		void setInput(Patch * patch, int index = 0);		
		void drawGUI();
		Patch * getOutput(float x, float y);
		
		void setId(int id);
		int getId();
		
	protected:
		int id;
		vector<PatchInput*> inputs;
		PatchOutput* output;
		Manager * manager;
		
	};
}