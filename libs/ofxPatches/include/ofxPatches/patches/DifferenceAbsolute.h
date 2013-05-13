#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class DifferenceAbsolute : public Patch {	
	public:
		DifferenceAbsolute * create() { return new DifferenceAbsolute(); };
		
		DifferenceAbsolute(){
			name = "Diff - Absolute";
			
			maxPasses = 1;
			
			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Threshold";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect tex1;
									   uniform float param1f0;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;										   
										   vec4 src = texture2DRect(tex0, st);
										   vec4 dst = texture2DRect(tex1, st);
										   vec4 diff = abs(src - dst);
										   
										   if(diff.r > param1f0
											  || diff.g > param1f0
											  || diff.b > param1f0
											  || diff.a > param1f0)
											   gl_FragColor = vec4(1.0,1.0,1.0,1.0);
										   else gl_FragColor = vec4(0.0,0.0,0.0,1.0);
										   
									   }
									   );
		}
	};
	
}