#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class Base5x5KernelEffect : public Patch {	
	public:
		Base5x5KernelEffect * create() { return new Base5x5KernelEffect(); };
		
		Base5x5KernelEffect(){
			name = "Base 5x5 Kernel Effect";
			
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
									   
									   uniform vec2 offset[25];
									   );
		}
		
		void onRenderPass(int pass){
			shader.setUniform2fv("offset", offset, 25);
		}
		
		void setParam1f(float param, int _paramNum = 0){
			Patch::setParam1f(param, _paramNum);
			calculateOffset();
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

