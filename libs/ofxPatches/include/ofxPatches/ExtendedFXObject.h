#pragma once

#include "ofMain.h"
#include "ofxFX.h"
#include "ofxGui.h"

#include "ofxPatches/Constants.h"

namespace ofxPatches {
	
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
		
		virtual void setup(string name = "", string filename = "");
		
		virtual void allocate(int _width, int _height, int _internalFormat);
		virtual void allocate(int _width, int _height);
		
		virtual void setParam1f(float param, int _paramNum = 0);
		virtual void setParam1i(int param, int _paramNum = 0);
		
		virtual void setBypass(bool value);
		virtual void setPasses(int value);
		
		virtual string getName();
		
		virtual void registerDefaultGui();
		
		virtual void setGUIPosition(float x, float y);
		virtual void drawGUI();
		virtual void applyGuiValues(); // useful when loading the settings;
		
		virtual GLuint getFbo(){return pingPong.dst->getFbo();};
		virtual ofFbo & getFboReference(){return *(pingPong.dst);};
		
		// They are not virtual in ofxFXObject
		virtual void draw(ofRectangle &_rect){ draw(_rect.x,_rect.y,_rect.width,_rect.height);};
		virtual void draw(int _x = -1, int _y = -1, float _width = -1, float _height = -1){
			ofxFXObject::draw(_x, _y, _width, _height);
		}
		
		// TODO, try to get this changes into ofxFX
		void setTexture(ofBaseDraws& base, int _texNum = 0);
		void begin(int _texNum = 0);
		

		bool compileCode();
		void update();

	protected:
		string name;
		string filename;
		bool useBackbuffer;
		bool bypass;
		bool allowBypass;
		int maxPasses;
		float * param1fs;
		int * param1is;
		
		int nParam1fs, nParam1is;
		
		ofFbo lastBuffer; // Acts as a buffer "buffer", so we can provide the last rendered buffer from the
						  // last update as the backbuffer of the first pass of the current update
		
		Param1fDefaults param1fDefaults[OFX_PATCHES_MAX_PARAMETERS];
		Param1iDefaults param1iDefaults[OFX_PATCHES_MAX_PARAMETERS];

		ofxPanel gui;
		ofxFloatSlider * param1fSliders;
		ofxIntSlider * param1iSliders;
		virtual void onParam1fChange(float & value);
		virtual void onParam1iChange(int & value);
		virtual void onBypassChange(bool & value);
		virtual void onPassesChange(int & value);
		
		// main render routine, overwrite if you want to control the render yourserlf
		virtual void onRender(int pass);
		
		// this will run just before the frame is rendered, making
		// it a good place to inject custom variables into the shader
		virtual void onShaderPass(int pass){};
	};
}