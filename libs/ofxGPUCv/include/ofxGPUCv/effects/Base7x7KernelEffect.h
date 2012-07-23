#pragma once

#define STRINGIFY(A) #A

#include "ofxGPUCv/effects/BaseKernelEffect.h"

namespace ofxGPUCv {
	
	class Base7x7KernelEffect : public BaseKernelEffect {	
	public:
		Base7x7KernelEffect * create() { return new Base7x7KernelEffect(); };
		
		Base7x7KernelEffect(){
			name = "Base 7x7 Kernel Effect";
			
			param1fDefaults[2].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect backbuffer;
									   uniform float param1f0;
									   uniform float param1f1;
									   uniform float param1f2;
									   uniform int pass;
									   
									   uniform vec2 offset[49];
									   );
		}
		
		void onRenderPass(int pass){
			shader.setUniform2fv("offset", offset, 49);
		}
		
	private:
		float offset[7 * 7 * 2];
		
		void calculateOffset(){
			float xInc = param1fs[0] * param1fs[1];
			float yInc = param1fs[0] * (param1fs[2] * (width/height));
			
			for (int i = 0; i < 7; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					offset[(((i*7)+j)*2)+0] = (-2.0f * xInc) + ((float)i * xInc);
					offset[(((i*7)+j)*2)+1] = (-2.0f * yInc) + ((float)j * yInc);
				}
			}
		}
		
	};
	
}

