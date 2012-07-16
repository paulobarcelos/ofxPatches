#include "ofxGPUCv/Manager.h"

using namespace ofxGPUCv;

Manager::Manager(){
	name = "undefined";
	filename = "";
}
Manager::~Manager(){
}

void Manager::setup(int nSources, string name, string filename){
	if(name.compare("")){
		this->name = name;
	}
	if(filename.compare("")){
		this->filename = filename;
	}
	if(!this->filename.compare("")){
		this->filename = this->name + ".xml";
	}
	
	fragmentShader = "";
	for (int i  = 0;  i < nSources; i ++) {
		fragmentShader += string("uniform sampler2DRect tex" + ofToString(i) +"; ");
	}
	
	gui.setup(this->name, this->filename);
}

bool Manager::compileCode(){
	gui.clear();
	unregisterAllPatches();
	
	ofxButton * removeLastPatchButton = new ofxButton();
	removeLastPatchButton->setup("Remove Last Patch");
	removeLastPatchButton->addListener(this, &Manager::onRemoveLasetPatchButton);
	gui.add(removeLastPatchButton);
	
	bool compileSuccess =  ofxFXObject::compileCode();
	
	for (int i  = 0; i < nTextures; i ++) {
		Patch * patch = new FixedSource(&(textures[i]), string("Source " + ofToString(i)));
		
		ofxButton * patchButton = new ofxButton();
		patchButton->setup(patch->getName());
		
		ManagerPatchGUIHandler * handler = new ManagerPatchGUIHandler(this, registeredPatches.size());
		patchButton->addListener(handler, &ManagerPatchGUIHandler::onPatchButton);
		
		registeredPatches.push_back(patch);
		gui.add(patchButton);
		registeredPatchesHandlers.push_back(handler);
	}
	
	return compileSuccess;
}

void Manager::unregisterAllPatches(){
	while (registeredPatches.size()) {
		delete registeredPatches[registeredPatches.size()-1];
		registeredPatches.pop_back();
	}
	while (registeredPatchesHandlers.size()) {
		delete registeredPatchesHandlers[registeredPatchesHandlers.size()-1];
		registeredPatchesHandlers.pop_back();
	}
}

Patch * Manager::getPatchById(int id){
	for (int i = 0; i < currentPatches.size(); i++) {
		if(currentPatches[i]->getId() == id){
			return currentPatches[i];
			break;
		}
	}
	return NULL;
}

void Manager::addPatch(int label, int id){
	if (label < 0 || label >= registeredPatches.size()) {
		ofLogWarning("Manager: Trying to add an patch that is not registred.");
		return;
	}
	Patch * patch = registeredPatches[label]->create();
	patch->setup(this, patch->getName(), string(ofToString(id) + ".xml"), id);	
	patch->allocate(width, height, internalFormat);
		
	// set gui position here!
	
	currentPatches.push_back(patch);
}

void Manager::removeLastPatch(){
	if (!currentPatches.size()) return;
	delete currentPatches[currentPatches.size()-1];
	currentPatches.pop_back();
	
	
}

void Manager::update(){
	for	(int i = 0; i < currentPatches.size(); i++){
		currentPatches[i]->update();
	}
}

//#ifdef OFX_GPU_CV_USE_GUI
void Manager::drawGUI(){
	gui.draw();
	
	for (int i = 0; i < currentPatches.size(); i++) {
		currentPatches[i]->drawGUI();
	}
}
void Manager::setGUIPosition(float x, float y){
	gui.setPosition(x, y);
}
void Manager::onRemoveLasetPatchButton(bool & value){
	removeLastPatch();
}
//#endif