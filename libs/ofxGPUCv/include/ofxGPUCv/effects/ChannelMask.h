#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class ChannelMask : public Patch {	
	public:
		ChannelMask * create() { return new ChannelMask(); };
		
		ChannelMask(){
			name = "Channel Mask";
			
			maxPasses = 1;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect tex1;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;										   
										   vec4 alpha = texture2DRect(tex0, st);
										   vec4 content = texture2DRect(tex1, st);
										   
										   gl_FragColor = content * alpha;
									   }
									   );
		}
	};
	
}