#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class AlphaMask : public Patch {	
	public:
		AlphaMask * create() { return new AlphaMask(); };
		
		AlphaMask(){
			name = "Alpha Mask";
			
			maxPasses = 1;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect tex1;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;	
										   float alpha = texture2DRect(tex0, st).r; // assumes mask is BW
										   vec4 color = texture2DRect(tex1, st);
										   
										   gl_FragColor = vec4(color.rgb, alpha);
									   }
									   );
		}
	};
	
}