#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class FixedSource: public Patch {	
	public:
		FixedSource * create() { return new FixedSource(source, name); };
		
		FixedSource(ofBaseDraws * source = NULL, string name = "Fixed Source"){
			this->source = source;
			this->name = name;			
			fragmentShader = STRINGIFY(  uniform sampler2DRect tex0; void main(void){};);
		}
		
		void registerDefaultGui(){			
			// Add the delete button
			ofxButton * deleteButton = new ofxButton();
			deleteButton->setup("Delete", OFX_GPU_CV_GUI_SIZE);
			deleteButton->addListener((Patch*)this, &Patch::onDelete);
			gui.add(deleteButton);
			
			// Add the preview slider
			ofxFloatSlider * previewSlider = new ofxFloatSlider();
			previewSlider->setup("Preview Scale", 0.25, 0., 1., OFX_GPU_CV_GUI_SIZE);
			previewSlider->addListener((Patch*)this, &Patch::onPreviewScaleChange);
			gui.add(previewSlider);
		};
		
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