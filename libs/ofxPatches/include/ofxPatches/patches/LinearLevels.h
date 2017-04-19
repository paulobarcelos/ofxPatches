#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class LinearLevels : public Patch {
	public:
		LinearLevels * create() { return new LinearLevels(); };
		
		LinearLevels(){
			name = "Linear Levels";
			
			maxPasses = 1;
			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Minimum";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "Maximum";
			param1fDefaults[1].value = 1.0;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
            
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0; // Minimum
									   uniform float param1f1; // Maximum
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   vec4 color = texture2DRect(tex0, st);
                                           
                                           vec4 minimum = vec4(param1f0);
                                           vec4 maximum = vec4(param1f1);
                                           vec4 diff = vec4(abs(maximum - minimum));
										   
										   gl_FragColor = min((color - minimum) / diff, 1.0);
									   }
									   );
		}
	};
	
}
