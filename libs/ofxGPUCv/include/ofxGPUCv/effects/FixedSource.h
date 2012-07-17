#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"
#include "ofxGPUCv/PatchInput.h"


namespace ofxGPUCv {
	
	class FixedSource: public Patch {	
	public:
		FixedSource * create() { return new FixedSource(source, name); };
		
		FixedSource(ofBaseDraws * source = NULL, string name = "Fixed Source"){
			this->source = source;
			this->name = name;			
			fragmentShader = STRINGIFY(  uniform sampler2DRect tex0; );
		}
		
		void setup(Manager * manager, string name = "", string filename = "", int id = rand()){

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
			this->manager= manager;
			
			gui.setup(this->name, this->filename);
			// Reset the gui
			gui.clear();
			
			// no bypass button here!
			
			// Add the delete button
			ofxButton * deleteButton = new ofxButton();
			deleteButton->setup("Delete");
			deleteButton->addListener((Patch*)this, &Patch::onDelete);
			gui.add(deleteButton);
			
			// Add the preview button
			ofxToggle * previewToogle = new ofxToggle("Preview", true);
			previewToogle->addListener((Patch*)this, &Patch::onPreview);
			gui.add(previewToogle);
		}
		
		bool compileCode(){
			bool compileSucess = Patch::compileCode();
			
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