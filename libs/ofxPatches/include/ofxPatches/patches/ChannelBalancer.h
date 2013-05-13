#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class ChannelBalancer : public Patch {	
	public:
		ChannelBalancer * create() { return new ChannelBalancer(); };
		
		ChannelBalancer(){
			name = "Channel Balancer";
			
			maxPasses = 1;
			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Red";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = -1.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "Green";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = -1.0;
			param1fDefaults[1].max = 1.0;
			
			param1fDefaults[2].name = "Blue";
			param1fDefaults[2].value = 0.0;
			param1fDefaults[2].min = -1.0;
			param1fDefaults[2].max = 1.0;
			
			param1fDefaults[3].name = "Alpha";
			param1fDefaults[3].value = 0.0;
			param1fDefaults[3].min = -1.0;
			param1fDefaults[3].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
                                       uniform sampler2DRect backbuffer;
									   uniform float param1f0;
									   uniform float param1f1;
									   uniform float param1f2;
									   uniform float param1f3;
                                       
                                       uniform int pass;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   
										   vec4 col;
										   if(pass > 0) col = texture2DRect(backbuffer, st);
										   else col = texture2DRect(tex0, st);
										   col.r += param1f0;
										   col.g += param1f1;
										   col.b += param1f2;
										   col.a += param1f3;
										   
										   
										   gl_FragColor = col;
									   }
									   );
		}
	};
	
}