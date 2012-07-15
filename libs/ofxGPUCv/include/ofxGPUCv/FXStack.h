#pragma once

#include "ofMain.h"
#include "ofxGPUCv/ExtendedFXObject.h"

//#ifdef OFX_GPU_CV_USE_GUI
#include "ofxGui.h"
//#endif

namespace ofxGPUCv {

	using namespace ofxGPUCv;
	
	class FXStackEffectGUIHandler; // forward
	
	class FXStack : public ofxFXObject {
	public:
		FXStack();
		virtual ~FXStack();
		
		virtual void setup(string name = "", string filename = "");
		
		template <class EffectType>
		int registerEffect();
		
		void addEffect(int label);
		void removeLastEffect();
		
		//#ifdef OFX_GPU_CV_USE_GUI
		virtual void setGUIPosition(float x, float y);
		virtual void drawGUI();
		//#endif
		
		void update();
		
	protected:
		string name;
		string filename;
		
		vector<ExtendedFXObject*> effects;
		vector<FXStackEffectGUIHandler*> effectsHandlers;
		vector<ExtendedFXObject*> stack;
		
		
		//#ifdef OFX_GPU_CV_USE_GUI
		ofxPanel gui;
		void onRemoveLasetEffectButton(bool & value);
		//ofxFloatSlider * param1fSliders;
		//ofxIntSlider * param1iSliders;
		//void onParam1fChange(float & value);
		//void onParam1iChange(int & value);
		//#endif
		
	};
	
	class FXStackEffectGUIHandler {
	public:
		FXStackEffectGUIHandler(FXStack * stack, int effectLabel){
			this->stack = stack;
			this->effectLabel = effectLabel;
		};
		void onEffectButton(bool & value){
			stack->addEffect(effectLabel);
		};
	private:
		FXStack * stack;
		int effectLabel;
	};
}

using namespace ofxGPUCv;

template <class EffectType>
int FXStack::registerEffect(){
	ExtendedFXObject * effect = new EffectType();
	
	ofxButton * effectButton = new ofxButton();
	effectButton->setup(effect->getName());
	
	FXStackEffectGUIHandler * handler = new FXStackEffectGUIHandler(this, stack.size());
	effectButton->addListener(handler, &FXStackEffectGUIHandler::onEffectButton);
	
	effects.push_back(effect);
	gui.add(effectButton);
	effectsHandlers.push_back(handler);
	
	return effects.size() - 1;
};