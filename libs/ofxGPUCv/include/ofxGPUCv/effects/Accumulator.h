#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class Accumulator : public Patch {	
	public:
		Accumulator * create() { return new Accumulator(); };
		
		Accumulator(){
			name = "Accumulator";
			
			maxPasses = 10;
			
			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Rate";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect backbuffer;
									   uniform float param1f0;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   
										   vec4 src = texture2DRect(backbuffer, st);
										   vec4 dst = texture2DRect(tex0, st);
										   
										   gl_FragColor = mix(src, dst, param1f0);
									   }
									   );
		}
	};
	
}