#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class CustomBW : public Patch {	
	public:
		CustomBW * create() { return new CustomBW(); };
		
		CustomBW(){
			name = "Custom BW";
			

			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Red";
			param1fDefaults[0].value = 0.3;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "Green";
			param1fDefaults[1].value = 0.59;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
			
			param1fDefaults[2].name = "Blue";
			param1fDefaults[2].value = 0.11;
			param1fDefaults[2].min = 0.0;
			param1fDefaults[2].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0;
									   uniform float param1f1;
									   uniform float param1f2;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   
										   vec4 color = texture2DRect(tex0, st);
										   float bw = color.r * param1f0 + color.g * param1f1 + color.b * param1f2;
										   
										   gl_FragColor = vec4(bw, bw, bw, color.a);
									   }
									   );
		}
	};
	
}