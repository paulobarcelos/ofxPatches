#include "ofxGPUCv/FXStack.h"

using namespace ofxGPUCv;

FXStack::FXStack(){
	name = "undefined";
	filename = "";
}
FXStack::~FXStack(){
}

void FXStack::setup(string name, string filename){
	if(name.compare("")){
		this->name = name;
	}
	if(filename.compare("")){
		this->filename = filename;
	}
	if(!this->filename.compare("")){
		this->filename = this->name + ".xml";
	}
	gui.setup(this->name, this->filename);
	gui.clear();
	
	ofxButton * removeLastEffectButton = new ofxButton();
	removeLastEffectButton->setup("Remove Last Effect");
	removeLastEffectButton->addListener(this, &FXStack::onRemoveLasetEffectButton);
	gui.add(removeLastEffectButton);
}

void FXStack::addEffect(int label){
	if (label < 0 || label >= effects.size()) {
		ofLogWarning("FXStack: Trying to add an effect that is not registred.");
		return;
	}
	ExtendedFXObject * effect = effects[label]->create();
	effect->setup(effect->getName(), string(name + "_" + ofToString(stack.size() + ".xml")));
	
	effect->allocate(width, height, internalFormat);
		
	// set gui position here!
	
	stack.push_back(effect);
}

void FXStack::removeLastEffect(){
	if (!stack.size()) return;
	delete stack[stack.size()-1];
	stack.pop_back();
	
	
}

void FXStack::update(){

}

//#ifdef OFX_GPU_CV_USE_GUI
void FXStack::drawGUI(){
	gui.draw();
	
	for (int i = 0; i < stack.size(); i++) {
		stack[i]->drawGUI();
	}
}
void FXStack::setGUIPosition(float x, float y){
	gui.setPosition(x, y);
}
void FXStack::onRemoveLasetEffectButton(bool & value){
	removeLastEffect();
}
//#endif