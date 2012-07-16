#include "ofxGPUCv/Manager.h"

using namespace ofxGPUCv;

Manager::Manager(){
	name = "undefined";
	filename = "";
}
Manager::~Manager(){
}

void Manager::setup(string name, string filename){
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
	
	ofxButton * removeLastPatchButton = new ofxButton();
	removeLastPatchButton->setup("Remove Last Patch");
	removeLastPatchButton->addListener(this, &Manager::onRemoveLasetPatchButton);
	gui.add(removeLastPatchButton);
}

void Manager::addPatch(int label){
	if (label < 0 || label >= effects.size()) {
		ofLogWarning("Manager: Trying to add an effect that is not registred.");
		return;
	}
	ExtendedFXObject * effect = effects[label]->create();
	effect->setup(effect->getName(), string(name + "_" + ofToString(stack.size() + ".xml")));
	
	effect->allocate(width, height, internalFormat);
		
	// set gui position here!
	
	stack.push_back(effect);
}

void Manager::removeLastPatch(){
	if (!stack.size()) return;
	delete stack[stack.size()-1];
	stack.pop_back();
	
	
}

void Manager::update(){

}

//#ifdef OFX_GPU_CV_USE_GUI
void Manager::drawGUI(){
	gui.draw();
	
	for (int i = 0; i < stack.size(); i++) {
		stack[i]->drawGUI();
	}
}
void Manager::setGUIPosition(float x, float y){
	gui.setPosition(x, y);
}
void Manager::onRemoveLasetPatchButton(bool & value){
	removeLastPatch();
}
//#endif