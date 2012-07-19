#pragma once

#include "ofMain.h"
#include "ofxGPUCv/Constants.h"
#include "ofxGPUCv/ExtendedFXObject.h"

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
		
		virtual void registerDefaultGui();
			
		virtual bool compileCode();	
		virtual void update();		
		virtual void setInput(Patch * patch, int index = 0);		
		virtual void drawGUI();
		virtual void applyGuiValues(); // useful when loading the settings;
		
		Patch * getOutput(float x, float y);
		
		virtual void setId(int id);
		virtual int getId();
		
		virtual void setLabel(int label);
		virtual int getLabel();
		
		void onDelete(bool & value);
		void onPreview(bool & value);
		
	protected:
		int id;
		int label;
		bool preview;
		vector<PatchInput*> inputs;
		PatchOutput* output;
		Manager * manager;
	};
}