#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class Base7x7KernelEffect : public Patch {	
	public:
		Base7x7KernelEffect * create() { return new Base7x7KernelEffect(); };
		
		Base7x7KernelEffect(){
			name = "Base 7x7 Kernel Effect";
			
			maxPasses = 100;

			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Size";
			param1fDefaults[0].value = 4.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 100.0;
			
			param1fDefaults[1].name = "x multiplier";
			param1fDefaults[1].value = 1.0;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
			
			param1fDefaults[2].name = "y multiplier";
			param1fDefaults[2].value = 1.0;
			param1fDefaults[2].min = 0.0;
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
		
		void setParam1f(float param, int _paramNum = 0){
			Patch::setParam1f(param, _paramNum);
			calculateOffset();
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

