#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class Threshold : public Patch {	
	public:
		Threshold * create() { return new Threshold(); };
		
		Threshold(){
			name = "Threshold";
			
			
			param1fDefaults[0].name = "Value";
			param1fDefaults[0].value = 0.5;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;										   
										   vec4 color = texture2DRect(tex0, st);
										   float r = 1. - step(color.r, param1f0);
										   float g = 1. - step(color.g, param1f0);
										   float b = 1. - step(color.b, param1f0);
										   gl_FragColor = vec4(r, g, b, 1.0);
									   }
									   );
		}
	};
	
}