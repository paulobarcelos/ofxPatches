#pragma once

#define STRINGIFY(A) #A

#include "ofxGPUCv/effects/BaseKernelEffect.h"


namespace ofxGPUCv {
	
	class Base3x3KernelEffect : public BaseKernelEffect {	
	public:
		Base3x3KernelEffect * create() { return new Base3x3KernelEffect(); };
		
		Base3x3KernelEffect(){
			name = "Base 3x3 Kernel Effect";
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect backbuffer;
									   uniform float param1f0;
									   uniform float param1f1;
									   uniform float param1f2;
									   uniform int pass;
									   
									   uniform vec2 offset[9];
									   );
		}
		
		void onShaderPass(int pass){
			shader.setUniform2fv("offset", offset, 9);
		}
		
	private:
		float offset[3 * 3 * 2];
		
		void calculateOffset(){
			float xInc = param1fs[0] * param1fs[1];
			float yInc = param1fs[0] * (param1fs[2] * (width/height));
			
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					offset[(((i*3)+j)*2)+0] = (-2.0f * xInc) + ((float)i * xInc);
					offset[(((i*3)+j)*2)+1] = (-2.0f * yInc) + ((float)j * yInc);
				}
			}
		}
		
	};
	
}

