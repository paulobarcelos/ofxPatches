#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxPatches/Patch.h"
#include "ofxPatches/PatchInput.h"
#include "ofxPatches/PatchOutput.h"
#include "ofxPatches/patches/FixedSource.h"

#include "ofxGui.h"

namespace ofxPatches {

	using namespace ofxPatches;
	
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
		void update();
		
		template <class PatchType>
		int registerPatch();
		void unregisterAllPatches();
		
		Patch * getPatchById(int id);
		int getPatchLabelById(int id);
		
		void addPatch(int label, int id);
		void removePatch(int id);
		
		void setGUIPosition(float x, float y);
		void setPatchesGUIPosition(float x, float y);
		void drawGUI();
		void applyGuiValues(); // useful when loading the settings;
		
		string getBaseFolder();
		
		void saveSettings();
		void loadSettings();
		
		void toggleEditing();
		void enableEditing();
		void disableEditing();
		bool isEditing();
		
	protected:
		string baseFolder;
		
		vector<Patch*> registeredPatches;
		vector<ManagerPatchGUIHandler*> registeredPatchesHandlers;
		vector<Patch*> currentPatches;
		
		ofxPanel patchesGui;
		
		bool editing;
		
		void onSaveSettings(bool & value);
		void onLoadSettings(bool & value);
		void onEdit(bool & value);
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

using namespace ofxPatches;

template <class PatchType>
int Manager::registerPatch(){
	Patch * patch = new PatchType();
	
	ofxButton * patchButton = new ofxButton();
	patchButton->setup(patch->getName(),OFX_PATCHES_GUI_SIZE);
	
	ManagerPatchGUIHandler * handler = new ManagerPatchGUIHandler(this, registeredPatches.size());
	patchButton->addListener(handler, &ManagerPatchGUIHandler::onPatchButton);
	
	registeredPatches.push_back(patch);
	patchesGui.add(patchButton);
	registeredPatchesHandlers.push_back(handler);
	
	return registeredPatches.size() - 1;
};