#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class Gamma : public Patch {
	public:
		Gamma * create() { return new Gamma(); };
		
		Gamma(){
			name = "Gamma";
			
			maxPasses = 1;
			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Gamma";
			param1fDefaults[0].value = 1.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 8.0;
			
            
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0; // Gamma
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   vec4 color = texture2DRect(tex0, st);
                                           
                                           float gammaCorrection = 1.0 / param1f0;
                                           color.rgb = 1.0 * pow(color.rgb / vec3(1.0), vec3(gammaCorrection));
                                           
										   
                                           gl_FragColor = color;
									   }
									   );
		}
	};
	
}