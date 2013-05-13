#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class FixedSource: public Patch {	
	public:
		FixedSource * create() { return new FixedSource(source, name); };
		
		FixedSource(){
			FixedSource(NULL, "Fixed Source");
		}
		FixedSource(ofBaseDraws * source = NULL, string name = "Fixed Source"){
			this->source = source;
			this->name = name;
			allowBypass = false;
			fragmentShader = STRINGIFY(  
									   uniform sampler2DRect tex0; 
									   void main(void){}
									   );
		}
				
		bool compileCode(){
			bool compileSucess = Patch::compileCode();
			shader.unload();
			
			// make sure to remove all inputs
			while (inputs.size()) {
				if(inputs[inputs.size()-1]) delete inputs[inputs.size()-1];
				inputs.pop_back();
			}
		}
		
		void setSource(ofBaseDraws * source){
			this->source = source;
		}
		
		void update(){
			pingPong.dst->begin();        
			ofClear(0,0,0,0);
			if(source) source->draw(0, 0, width, height);  
			pingPong.dst->end();        
			pingPong.swap();
			pingPong.swap();
		}
		
		private:
		
		ofBaseDraws * source;
	};
	
}