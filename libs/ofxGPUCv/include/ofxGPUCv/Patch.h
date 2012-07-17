#pragma once

#include "ofMain.h"
#include "ofxGPUCv/ExtendedFXObject.h"

#define OFX_GPUCV_PATCH_CONNECTOR_SIZE 10

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
		
		virtual void setup(Manager * manager, string name = "", string filename = "", int id = rand());
		
		virtual bool compileCode();	
		virtual void update();		
		virtual void setInput(Patch * patch, int index = 0);		
		virtual void drawGUI();
		Patch * getOutput(float x, float y);
		
		virtual void setId(int id);
		virtual int getId();
		
		void onDelete(bool & value);
		void onPreview(bool & value);
		
	protected:
		int id;
		bool preview;
		vector<PatchInput*> inputs;
		PatchOutput* output;
		Manager * manager;
		
		
		
	};
}