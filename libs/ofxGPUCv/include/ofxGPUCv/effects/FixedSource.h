#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class FixedSource: public Patch {	
	public:
		FixedSource * create() { return new FixedSource(source, name); };
		
		FixedSource(ofBaseDraws * source = NULL, string name = "Fixed Source"){
			this->source = source;
			this->name = name;			
			fragmentShader = STRINGIFY(  uniform sampler2DRect tex0; );
		}
		
		void setup(string name = "", string filename = "", int id = rand()){
			if(name.compare("")){
				this->name = name;
			}
			if(filename.compare("")){
				this->filename = filename;
			}
			if(!this->filename.compare("")){
				this->filename = this->name + ".xml";
			}
			this->id = id;
			
			gui.setup(this->name, this->filename);
			// Reset the gui
			gui.clear();
			
			// no bypass button here!
		}
		
		void setSource(ofBaseDraws * source){
			this->source = source;
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