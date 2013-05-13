#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class BitwiseXOR : public Patch {
	public:
		BitwiseXOR * create() { return new BitwiseXOR(); };
		
		BitwiseXOR(){
			name = "Bitwise XOR";
			
			maxPasses = 1;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect tex1;
									   
									   float XOR(float a, float b){
										   return (a != b) ? 1.0 : 0.0;
									   }
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;	
										   vec4 a = texture2DRect(tex0, st);
										   vec4 b = texture2DRect(tex1, st);
										   
										   vec4 color;
										   color.r = XOR(a.r, b.r);
										   color.g = XOR(a.g, b.g);
										   color.b = XOR(a.b, b.b);
										   color.a = 1.0;
										   
										   gl_FragColor = color;
									   }
									   );
		}
	};
	
}