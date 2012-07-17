#include "ofxGPUCv/Manager.h"

using namespace ofxGPUCv;

Manager::Manager(){
	name = "undefined";
	filename = "";
	output = NULL;
	manager = this;
}
Manager::~Manager(){
}

void Manager::setup(int nSources, string name, string filename){
	nSources ++; // one extra texture to use as output
	
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
	
	// Add the preview button
	ofxToggle * previewToogle = new ofxToggle("Preview", true);
	previewToogle->addListener((Patch*)this, &Patch::onPreview);
	gui.add(previewToogle);
	
	bool compileSuccess =  ofxFXObject::compileCode();
	
	for (int i  = 0; i < nTextures - 1; i ++) {
		Patch * patch = new FixedSource(&(textures[i]), string("Source " + ofToString(i)));
		
		ofxButton * patchButton = new ofxButton();
		patchButton->setup(patch->getName());
		
		ManagerPatchGUIHandler * handler = new ManagerPatchGUIHandler(this, registeredPatches.size());
		patchButton->addListener(handler, &ManagerPatchGUIHandler::onPatchButton);
		
		registeredPatches.push_back(patch);
		gui.add(patchButton);
		registeredPatchesHandlers.push_back(handler);
	}
	
	// The one and only input, that will be used when we want to plug
	// in the last patch in the system
	inputs.clear();	
	inputs.push_back(new PatchInput(this, NULL, 0));
	
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

int Manager::getPatchLabelById(int id){
	for (int i = 0; i < currentPatches.size(); i++) {
		if(currentPatches[i]->getId() == id){
			return i;
			break;
		}
	}
	return -1;
}

void Manager::addPatch(int label, int id){
	if (label < 0 || label >= registeredPatches.size()) {
		ofLogWarning("Manager: Trying to add an patch that is not registred.");
		return;
	}
	Patch * patch = registeredPatches[label]->create();
	patch->setup(this, patch->getName(), string(ofToString(id) + ".xml"), id);	
	patch->allocate(width, height, internalFormat);
		
	patch->setGUIPosition(currentPatches.size()*30, currentPatches.size()*30);
	
	currentPatches.push_back(patch);
}

void Manager::removePatch(int id){
	int label = getPatchLabelById(id);
	if(label == -1) return;
	Patch * patch = currentPatches[label];
	
	// swap with the last!
	Patch * lastPatch = currentPatches[currentPatches.size()-1];
	currentPatches[label] = lastPatch;
	currentPatches[currentPatches.size()-1] = patch;
	
	// delete and remove
	delete currentPatches[currentPatches.size()-1];
	currentPatches.pop_back();
	
	// loop through all the remaining patches and remove the connector
	for (int i = 0; i < currentPatches.size(); i++) {
		for (int j = 0; j < currentPatches[i]->inputs.size(); j++) {
			if(currentPatches[i]->inputs[j]->patch){
				if(currentPatches[i]->inputs[j]->patch->id == id){
					currentPatches[i]->inputs[j]->patch = NULL;
				}
			}
		}
	}
	
	// also check if the patch was connecte to the manager itself
	for (int i = 0; i < inputs.size(); i++) {
		if(inputs[i]->patch){
			if(inputs[i]->patch->id == id){
				inputs[i]->patch = NULL;
			}
		}
	}
}

void Manager::update(){
	for	(int i = 0; i < currentPatches.size(); i++){
		currentPatches[i]->update();
	}
	
	if(inputs[0]->getPatch()) setTexture(inputs[0]->getPatch()->getTextureReference(), nTextures-1);
	else {
		begin(nTextures-1);
		ofPushStyle();
		ofSetColor(255);
		ofLine(0, 0, width, height);
		ofLine(0, height, width, 0);
		ofPushStyle();
		ofSetColor(255,0,0);
		ofDrawBitmapString(string("Input  undefined"), 10, height/2);
		ofPopStyle();
		ofPopStyle();
		end(nTextures-1);
	}
	
	pingPong.dst->begin();        
	ofClear(0);
	textures[nTextures-1].draw(0, 0, width, height);  
	pingPong.dst->end();        
	pingPong.swap();
	pingPong.swap();
	
	
}

//#ifdef OFX_GPU_CV_USE_GUI
void Manager::drawGUI(){
	Patch::drawGUI();
	
	for (int i = 0; i < currentPatches.size(); i++) {
		currentPatches[i]->drawGUI();
	}
}
void Manager::setGUIPosition(float x, float y){
	gui.setPosition(x, y);
}
//#endif