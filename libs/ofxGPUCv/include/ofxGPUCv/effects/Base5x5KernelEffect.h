#pragma once

#define STRINGIFY(A) #A

#include "ofxGPUCv/effects/BaseKernelEffect.h"


namespace ofxGPUCv {
	
	class Base5x5KernelEffect : public BaseKernelEffect {	
	public:
		Base5x5KernelEffect * create() { return new Base5x5KernelEffect(); };
		
		Base5x5KernelEffect(){
			name = "Base 5x5 Kernel Effect";
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect backbuffer;
									   uniform float param1f0;
									   uniform float param1f1;
									   uniform float param1f2;
									   uniform int pass;
									   
									   uniform vec2 offset[25];
									   );
		}
		
		void onShaderPass(int pass){
			shader.setUniform2fv("offset", offset, 25);
		}
			
	private:
		float offset[5 * 5 * 2];
		
		void calculateOffset(){
			float xInc = param1fs[0] * param1fs[1];
			float yInc = param1fs[0] * (param1fs[2] * (width/height));
			
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					offset[(((i*5)+j)*2)+0] = (-2.0f * xInc) + ((float)i * xInc);
					offset[(((i*5)+j)*2)+1] = (-2.0f * yInc) + ((float)j * yInc);
				}
			}
		}
		
	};
	
}

