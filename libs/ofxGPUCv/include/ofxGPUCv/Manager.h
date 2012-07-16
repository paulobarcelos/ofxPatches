#pragma once

#include "ofMain.h"
#include "ofxGPUCv/ExtendedFXObject.h"

//#ifdef OFX_GPU_CV_USE_GUI
#include "ofxGui.h"
//#endif

namespace ofxGPUCv {

	using namespace ofxGPUCv;
	
	class ManagerPatchGUIHandler; // forward
	
	class Manager : public ofxFXObject {
	public:
		Manager();
		virtual ~Manager();
		
		virtual void setup(string name = "", string filename = "");
		
		template <class PatchType>
		int registerPatch();
		
		void addPatch(int label);
		void removeLastPatch();
		
		//#ifdef OFX_GPU_CV_USE_GUI
		virtual void setGUIPosition(float x, float y);
		virtual void drawGUI();
		//#endif
		
		void update();
		
	protected:
		string name;
		string filename;
		
		vector<ExtendedFXObject*> effects;
		vector<ManagerPatchGUIHandler*> effectsHandlers;
		vector<ExtendedFXObject*> stack;
		
		
		//#ifdef OFX_GPU_CV_USE_GUI
		ofxPanel gui;
		void onRemoveLasetPatchButton(bool & value);
		//ofxFloatSlider * param1fSliders;
		//ofxIntSlider * param1iSliders;
		//void onParam1fChange(float & value);
		//void onParam1iChange(int & value);
		//#endif
		
	};
	
	class ManagerPatchGUIHandler {
	public:
		ManagerPatchGUIHandler(Manager * stack, int effectLabel){
			this->stack = stack;
			this->effectLabel = effectLabel;
		};
		void onPatchButton(bool & value){
			stack->addPatch(effectLabel);
		};
	private:
		Manager * stack;
		int effectLabel;
	};
}

using namespace ofxGPUCv;

template <class PatchType>
int Manager::registerPatch(){
	ExtendedFXObject * effect = new PatchType();
	
	ofxButton * effectButton = new ofxButton();
	effectButton->setup(effect->getName());
	
	ManagerPatchGUIHandler * handler = new ManagerPatchGUIHandler(this, stack.size());
	effectButton->addListener(handler, &ManagerPatchGUIHandler::onPatchButton);
	
	effects.push_back(effect);
	gui.add(effectButton);
	effectsHandlers.push_back(handler);
	
	return effects.size() - 1;
};