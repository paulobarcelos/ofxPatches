#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class BitwiseAND : public Patch {
	public:
		BitwiseAND * create() { return new BitwiseAND(); };
		
		BitwiseAND(){
			name = "Bitwise AND";
			
			maxPasses = 1;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect tex1;
									   
									   float AND(float a, float b){
										   return (a != 0.0 && b != 0.0) ? 1.0 : 0.0;
									   }
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;	
										   vec4 a = texture2DRect(tex0, st);
										   vec4 b = texture2DRect(tex1, st);
										   
										   vec4 color;
										   color.r = AND(a.r, b.r);
										   color.g = AND(a.g, b.g);
										   color.b = AND(a.b, b.b);
										   color.a = 1.0;
										   
										   gl_FragColor = color;
									   }
									   );
		}
	};
	
}