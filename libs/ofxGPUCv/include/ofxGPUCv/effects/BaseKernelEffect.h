#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class BaseKernelEffect : public Patch {	
	public:
		BaseKernelEffect * create() { return new BaseKernelEffect(); };
		
		BaseKernelEffect(){
			name = "Base Kernel Effect";
			
			maxPasses = 100;

			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Size";
			param1fDefaults[0].value = 4.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 30.0;
			
			param1fDefaults[1].name = "x multiplier";
			param1fDefaults[1].value = 1.0;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
			
			param1fDefaults[2].name = "y multiplier";
			param1fDefaults[2].value = 1.0;
			param1fDefaults[2].min = 0.0;
			param1fDefaults[2].max = 1.0;
			
		}
		
		void setParam1f(float param, int _paramNum = 0){
			Patch::setParam1f(param, _paramNum);
			calculateOffset();
		}
		
	private:		
		virtual void calculateOffset(){};
		
	};
	
}
