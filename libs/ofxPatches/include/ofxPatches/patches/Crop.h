#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class Crop : public Patch {	
	public:
		Crop * create() { return new Crop(); };
		
		Crop(){
			name = "Crop";
			
			param1fDefaults[0].name = "x";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "y";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
			
			param1fDefaults[2].name = "w";
			param1fDefaults[2].value = 1.0;
			param1fDefaults[2].min = 0.0;
			param1fDefaults[2].max = 1.0;
			
			param1fDefaults[3].name = "h";
			param1fDefaults[3].value = 1.0;
			param1fDefaults[3].min = 0.0;
			param1fDefaults[3].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0; //x
									   uniform float param1f1; //y
									   uniform float param1f2; //w
									   uniform float param1f3; //h
									   );
		}
		
		void onRender(int pass){
			textures[0].getTextureReference().drawSubsection(0, 0, width, height, 
															 param1fs[0] * width, 
															 param1fs[1] * height, 
															 param1fs[2] * width,
															 param1fs[3] * height);
		}
	};
	
	
	
}