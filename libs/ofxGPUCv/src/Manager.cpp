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
	
	baseFolder = OFX_GPU_CV_SETTINGS_FOLDER + ofFilePath::removeExt(this->filename) + "/";
	ofDirectory::createDirectory(baseFolder, true, true);
	
	this->filename = baseFolder + this->filename;	
	
	fragmentShader = "";
	for (int i  = 0;  i < nSources; i ++) {
		fragmentShader += string("uniform sampler2DRect tex" + ofToString(i) +"; ");
	}
	
	gui.setup(this->name, this->filename);
	gui.setPosition(ofGetWidth()/2, ofGetHeight()/2);
	gui.clear();
	
	
	// Add th load / save buttons
	ofxButton * saveSettingsButton = new ofxButton();
	saveSettingsButton->setup("Save");
	saveSettingsButton->addListener(this, &Manager::onSaveSettings);
	gui.add(saveSettingsButton);
	
	ofxButton * loadSettingsButton = new ofxButton();
	loadSettingsButton->setup("Load");
	loadSettingsButton->addListener(this, &Manager::onLoadSettings);
	gui.add(loadSettingsButton);
	
	// Add the edit toogle
	ofxToggle * editToogle = new ofxToggle("Edit", true);
	editToogle->addListener(this, &Manager::onEdit);
	gui.add(editToogle);
	
	// Add the preview toogle
	ofxToggle * previewToogle = new ofxToggle("Preview", true);
	previewToogle->addListener((Patch*)this, &Patch::onPreview);
	gui.add(previewToogle);
	
	patchesGui.setup("Patches", baseFolder + "patches_gui.xml");	
	patchesGui.setPosition(100, 100);	
}

bool Manager::compileCode(){
	unregisterAllPatches();
	
	bool compileSuccess =  ofxFXObject::compileCode();
	
	patchesGui.clear();
	for (int i  = 0; i < nTextures - 1; i ++) {
		Patch * patch = new FixedSource(&(textures[i]), string("Source " + ofToString(i)));
		
		ofxButton * patchButton = new ofxButton();
		patchButton->setup(patch->getName());
		
		ManagerPatchGUIHandler * handler = new ManagerPatchGUIHandler(this, registeredPatches.size());
		patchButton->addListener(handler, &ManagerPatchGUIHandler::onPatchButton);
		
		registeredPatches.push_back(patch);
		patchesGui.add(patchButton);
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
	patch->setLabel(label);
	patch->allocate(width, height, internalFormat);
		
	patch->setGUIPosition(ofGetWidth()/2 - patch->gui.getShape().width / 2 + currentPatches.size() * 30, 
						 ofGetHeight()/2 - patch->gui.getShape().height / 2 + currentPatches.size()*30);
	
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
	
	// remove the settings file
	//ofFile::removeFile(patch->filename);
	
	// delete and remove from the collection
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

void Manager::drawGUI(){
	ExtendedFXObject::drawGUI();
	
	if(preview) draw(gui.getShape().x, gui.getShape().y + gui.getShape().height, gui.getShape().width, gui.getShape().width * height/width); 
	
	if(isEditing){
		if(output) output->draw();	
		for (int i = 0; i < inputs.size(); i++) {
			inputs[i]->draw();	
		}
		
		patchesGui.draw();	
		for (int i = 0; i < currentPatches.size(); i++) {
			currentPatches[i]->drawGUI();
		}
	}
	
}
void Manager::setGUIPosition(float x, float y){
	gui.setPosition(x, y);
}

void Manager::setPatchesGUIPosition(float x, float y){
	patchesGui.setPosition(x, y);
}

void Manager::applyGuiValues(){
	Patch::applyGuiValues();
	onEdit(gui.getToggle("Edit"));
}

void Manager::saveSettings(){
	// make sure dir exists
	ofDirectory::createDirectory(baseFolder, true, true);
	// Save gui
	gui.saveToFile(filename);
	
	// Create the main settings xml
	ofxXmlSettings settings;
	
	// Save the current input
	settings.addTag("inputs");
	if(inputs.size()){
		settings.pushTag("inputs");
		for (int i = 0; i < inputs.size(); i++) {
			if(inputs[i]->getPatch()){
				settings.addTag("id");
				settings.setValue("id", inputs[i]->getPatch()->getId(), i);
			}
			
		}
		settings.popTag();
	}
	
	// Save the current position
	settings.addTag("gui_position");
	settings.pushTag("gui_position");
	
	settings.addTag("x");
	settings.setValue("x", gui.getPosition().x);
	settings.addTag("y");
	settings.setValue("y", gui.getPosition().y);
	
	settings.popTag();
	
	settings.addTag("patches_gui_position");
	settings.pushTag("patches_gui_position");
	
	settings.addTag("x");
	settings.setValue("x", patchesGui.getPosition().x);
	settings.addTag("y");
	settings.setValue("y", patchesGui.getPosition().y);
	
	settings.popTag();	
	
	// Save all the patches 
	settings.addTag("patches");
	settings.pushTag("patches");
	for (int i = 0; i < currentPatches.size(); i++) {
		// Save each individual gui
		currentPatches[i]->gui.saveToFile(currentPatches[i]->filename);
		
		settings.addTag("patch");
		settings.pushTag("patch", i);
		
		settings.addTag("id");
		settings.setValue("id", currentPatches[i]->getId());
		settings.addTag("label");
		settings.setValue("label", currentPatches[i]->getLabel());
		
		settings.addTag("gui_position");
		settings.pushTag("gui_position");
		settings.addTag("x");
		settings.setValue("x", currentPatches[i]->gui.getPosition().x);
		settings.addTag("y");
		settings.setValue("y", currentPatches[i]->gui.getPosition().y);
		settings.popTag();
		
		settings.addTag("inputs");
		settings.pushTag("inputs");			
		for (int j = 0; j < currentPatches[i]->inputs.size(); j++) {
			if(currentPatches[i]->inputs[j]->getPatch()){
				
				settings.addTag("id");
				settings.setValue("id", currentPatches[i]->inputs[j]->getPatch()->getId(), j);
				
			}
		}
		settings.popTag();
		
		settings.popTag();
	}
	settings.popTag();
	
	// Save the file
	settings.saveFile(baseFolder + "_settings.xml");
}

void Manager::loadSettings(){
	// Load the gui
	gui.loadFromFile(filename);
	applyGuiValues();
	
	// Open the xml file (and if it's not there, return early)
	ofxXmlSettings settings;
	if(!settings.loadFile(baseFolder + "_settings.xml")) return;
	
	// Set the position
	setGUIPosition(settings.getValue("gui_position:x", 0.0), settings.getValue("gui_position:y", 0.0));
	setPatchesGUIPosition(settings.getValue("patches_gui_position:x", 0.0), settings.getValue("patches_gui_position:y", 0.0));
	
	// Create each of the patches
	
	while (currentPatches.size()) {
		removePatch(currentPatches[currentPatches.size()-1]->getId());
	}
	
	settings.pushTag("patches");
	for (int i = 0; i < settings.getNumTags("patch"); i++) {
		settings.pushTag("patch", i);
		// create the patch
		addPatch(settings.getValue("label", -1), settings.getValue("id", -1));
		// load the gui
		currentPatches[i]->gui.loadFromFile(currentPatches[i]->filename);
		currentPatches[i]->applyGuiValues();
		// set the position
		currentPatches[i]->setGUIPosition(settings.getValue("gui_position:x", 0.0), settings.getValue("gui_position:y", 0.0));
		// set all the inputs
		settings.pushTag("inputs");
		for (int j = 0; j < settings.getNumTags("id"); j++) {
			currentPatches[i]->setInput(getPatchById(settings.getValue("id", -1, j)), j);
		}
		settings.popTag();
		
		settings.popTag();
	}
	settings.popTag();
	
	// Now that all patches are created, we are safe to add the manager inputs
	settings.pushTag("inputs");
	for (int i = 0; i < settings.getNumTags("id"); i++) {
		setInput(getPatchById(settings.getValue("id", -1, i)), i);
	}
	settings.popTag();
}

void Manager::onSaveSettings(bool & value){
	if(value){
		saveSettings();
	}
}

void Manager::onLoadSettings(bool & value){
	if(value){
		loadSettings();
	}
}

void Manager::onEdit(bool & value){
	if(value){
		enableEditing();
	}
	else{
		disableEditing();
	}
}

void Manager::enableEditing(){
	isEditing = true;
}

void Manager::disableEditing(){
	isEditing = false;
}