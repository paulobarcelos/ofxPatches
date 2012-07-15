#pragma once

#include "ofMain.h"
#include "ofxFX.h"

//#ifdef OFX_GPU_CV_USE_GUI
#include "ofxGui.h"
//#endif

#define OFX_GPU_CV_MAX_PARAMETERS 20

namespace ofxGPUCv {
	
	typedef void (*Param1fCallback) (float value);
	typedef void (*Param1iCallback) (int value);
	
	
	struct Param1fDefaults{
		Param1fDefaults(){
			name = "undefined";
			min = max = value = 0.0;
		};
		string name;
		float min, max, value;
	};
	
	struct Param1iDefaults{
		Param1iDefaults(){
			name = "undefined";
			min = max = value = 0;
		};
		string name;
		int min, max, value;
	};

	class ExtendedFXObject : public ofxFXObject {
	public:
		ExtendedFXObject();
		virtual ~ExtendedFXObject();
		
		virtual ExtendedFXObject * create() { return new ExtendedFXObject();};  
		
		virtual void setup(string name = "", string filename = "");
		
		virtual void setParam1f(float param, int _paramNum = 0);
		virtual void setParam1i(int param, int _paramNum = 0);
		
		virtual void setBypass(bool value);
		
		virtual string getName();
		
		//#ifdef OFX_GPU_CV_USE_GUI
		virtual void setGUIPosition(float x, float y);
		virtual void drawGUI();
		//#endif
		
		bool compileCode();
		void update();

	//protected:
		string name;
		string filename;
		bool bypass;
		float * param1fs;
		int * param1is;
		
		int nParam1fs, nParam1is;
		
		Param1fDefaults param1fDefaults[OFX_GPU_CV_MAX_PARAMETERS];
		Param1iDefaults param1iDefaults[OFX_GPU_CV_MAX_PARAMETERS];
		
		//#ifdef OFX_GPU_CV_USE_GUI
		ofxPanel gui;
		ofxFloatSlider * param1fSliders;
		ofxIntSlider * param1iSliders;
		void onParam1fChange(float & value);
		void onParam1iChange(int & value);
		void onBypassChange(bool & value);
		//#endif

	};
}