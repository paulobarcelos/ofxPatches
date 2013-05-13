#pragma once

#include "ofMain.h"
#include "ofxPatches/Patch.h"

#define STRINGIFY(A) #A


namespace ofxPatches {
	
	class BandThreshold : public Patch {	
	public:
		BandThreshold * create() { return new BandThreshold(); };
		
		BandThreshold(){
			name = "Band Threshold";
			
			
			param1fDefaults[0].name = "Low Value";
			param1fDefaults[0].value = 0.3;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "High Value";
			param1fDefaults[1].value = 0.7;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0;
									   uniform float param1f1;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;										   
										   vec4 color = texture2DRect(tex0, st);
										   float r;
										   float g;
										   float b;
										   r = g = b = 0.0;
										   
										   if(color.r >= param1f0 && color.r <= param1f1) r = 1.0;
										   if(color.g >= param1f0 && color.g <= param1f1) g = 1.0;
										   if(color.b >= param1f0 && color.b <= param1f1) b = 1.0;
										   
										   gl_FragColor = vec4(r, g, b, 1.0);
									   }
									   );
		}
	};
	
}