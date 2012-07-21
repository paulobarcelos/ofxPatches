#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class DifferenceDarken : public Patch {	
	public:
		DifferenceDarken * create() { return new DifferenceDarken(); };
		
		DifferenceDarken(){
			name = "Diff - Darken";
			
			
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
										   
										   float luminecenceSrc = src.r * 0.3 + src.g * 0.59 + src.b * 0.11;
										   float luminecenceDst = dst.r * 0.3 + dst.g * 0.59 + dst.b * 0.11;
										   
										   float diff = luminecenceDst - luminecenceSrc;
										   
										   if(diff > param1f0) gl_FragColor = vec4(1.0,1.0,1.0,1.0);
										   else gl_FragColor = vec4(0.0,0.0,0.0,1.0);
									   }
									   );
		}
	};
	
}