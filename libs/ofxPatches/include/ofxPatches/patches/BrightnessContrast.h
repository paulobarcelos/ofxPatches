#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class BrightnessContrast : public Patch {	
	public:
		BrightnessContrast * create() { return new BrightnessContrast(); };
		
		BrightnessContrast(){
			name = "Brightness / Contrast";
			
			maxPasses = 1;
			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Brightness";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = -1.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "Contrast";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = -1.0;
			param1fDefaults[1].max = 1.0;
						
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0; // Brightness
									   uniform float param1f1; // Contrast
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;										   
										   vec4 color = texture2DRect(tex0, st);
										   
										   float factor = (1.0 * (param1f1 + 1.0)) / (1.0 * (1.0 - param1f1));
										   
										   color = color + vec4(param1f0,param1f0,param1f0, 0.0);
										   
										   color = vec4(factor * (color.rgb - vec3(0.5)) + vec3(0.5), color.a);
										   
										   gl_FragColor = color;
									   }
									   );
		}
	};
	
}