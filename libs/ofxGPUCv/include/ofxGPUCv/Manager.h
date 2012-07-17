#pragma once

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"
#include "ofxGPUCv/PatchInput.h"
#include "ofxGPUCv/PatchOutput.h"
#include "ofxGPUCv/effects/FixedSource.h"

#include "ofxGui.h"

namespace ofxGPUCv {

	using namespace ofxGPUCv;
	
	class ManagerPatchGUIHandler; // forward declaration
	
	class Manager : public Patch {
		friend class Patch;
		friend class PatchInput;
		friend class PatchOutput;
	public:
		Manager();
		~Manager();
		
		void setup(int nSources = 1, string name = "", string filename = "");
		
		bool compileCode();
		
		template <class PatchType>
		int registerPatch();
		void unregisterAllPatches();
		
		Patch * getPatchById(int id);
		int getPatchLabelById(int id);
		
		void addPatch(int label, int id);
		void removePatch(int id);
		
		void setGUIPosition(float x, float y);
		void drawGUI();
		
		void update();
		
	protected:
		vector<Patch*> registeredPatches;
		vector<ManagerPatchGUIHandler*> registeredPatchesHandlers;
		vector<Patch*> currentPatches;
	};
	
	class ManagerPatchGUIHandler {
	public:
		ManagerPatchGUIHandler(Manager * manager, int patchLabel){
			this->manager = manager;
			this->patchLabel = patchLabel;
		};
		void onPatchButton(bool & value){
			if(value)manager->addPatch(patchLabel, rand());
		};
	private:
		Manager * manager;
		int patchLabel;
	};
}

using namespace ofxGPUCv;

template <class PatchType>
int Manager::registerPatch(){
	Patch * patch = new PatchType();
	
	ofxButton * patchButton = new ofxButton();
	patchButton->setup(patch->getName());
	
	ManagerPatchGUIHandler * handler = new ManagerPatchGUIHandler(this, registeredPatches.size());
	patchButton->addListener(handler, &ManagerPatchGUIHandler::onPatchButton);
	
	registeredPatches.push_back(patch);
	gui.add(patchButton);
	registeredPatchesHandlers.push_back(handler);
	
	return registeredPatches.size() - 1;
};