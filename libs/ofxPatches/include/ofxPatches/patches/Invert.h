#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class Invert : public Patch {	
	public:
		Invert * create() { return new Invert(); };
		
		Invert(){
			name = "Invert";			
					
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   vec4 one = vec4(1.0);
										   vec4 color = texture2DRect(tex0, st);
										   			   
										   gl_FragColor = vec4((one - color).rgb, color.a);
									   }
									   );
		}
	};
	
}