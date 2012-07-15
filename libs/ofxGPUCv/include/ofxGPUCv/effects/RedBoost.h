#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/ExtendedFXObject.h"


namespace ofxGPUCv {
	
	class RedBoost : public ExtendedFXObject {	
	public:
			RedBoost * create() { return new RedBoost(); };
		
			RedBoost(){
				name = "Red Boost";
				
				passes = 1;
				internalFormat = GL_RGBA;
				
				param1fDefaults[0].name = "Boost";
				param1fDefaults[0].value = 0.5;
				param1fDefaults[0].min = 0.0;
				param1fDefaults[0].max = 1.0;

				fragmentShader = STRINGIFY(
										   uniform sampler2DRect tex0;
										   uniform float param1f0;
										   
										   void main(void){
											   vec2 st = gl_TexCoord[0].st;
								   
											   vec4 col = texture2DRect(tex0, st);
											   col.r += param1f0;
									   
											   gl_FragColor = col;
										   }
										   );
			}
	};

}