#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class Empty: public Patch {	
	public:
		Empty * create() { return new Empty(); };
		
		Empty(){
			source = NULL;
			name = "Empty";			
			fragmentShader = STRINGIFY(  uniform sampler2DRect tex0; );
		}
		
		void setSource(ofBaseDraws & source){
			this->source = &source;
		}
		
		void update(){
			pingPong.dst->begin();        
			ofClear(0);
			if(source) source->draw(0, 0, width, height);  
			pingPong.dst->end();        
			pingPong.swap();
			pingPong.swap();
		}
		
		private:
		
		ofBaseDraws * source;
	};
	
}