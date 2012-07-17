#include "ofxGPUCv/Patch.h"
#include "ofxGPUCv/PatchInput.h"
#include "ofxGPUCv/PatchOutput.h"
#include "ofxGPUCv/Manager.h"

using namespace ofxGPUCv;

Patch::Patch(){
	output = new PatchOutput(this);
	manager = NULL;
	preview = true;
	ExtendedFXObject::ExtendedFXObject();
}

Patch::~Patch(){
	if(output) delete output;
}

void Patch::setup(Manager * manager, string name, string filename, int id){
	ExtendedFXObject::setup(name, filename);
	this->manager = manager;
	this->id = id;
	
	// Add the delete button
	ofxButton * deleteButton = new ofxButton();
	deleteButton->setup("Delete");
	deleteButton->addListener(this, &Patch::onDelete);
	gui.add(deleteButton);
	
	// Add the preview button
	ofxToggle * previewToogle = new ofxToggle("Preview", true);
	previewToogle->addListener(this, &Patch::onPreview);
	gui.add(previewToogle);
}

bool Patch::compileCode(){
	if (ExtendedFXObject::compileCode()) {
		inputs.clear();
		
		for (int i = 0; i < nTextures; i++) {
			inputs.push_back(new PatchInput(this, NULL, i));
		}
		return true;
	}
	else {
		return false;
	}
}

void Patch::setInput(Patch * patch, int index){
	if (index >= 0 && index < inputs.size()) {
		inputs[index]->setPatch(patch); 
	}
}

void Patch::update(){
	for (int i = 0; i < inputs.size(); i++) {
		if(inputs[i]->getPatch()) setTexture(inputs[i]->getPatch()->getTextureReference(), i);
		else {
			begin(i);
			ofPushStyle();
			ofSetColor(255);
			ofLine(0, 0, width, height);
			ofLine(0, height, width, 0);
			ofPushStyle();
			ofSetColor(255,0,0);
			ofDrawBitmapString(string("Input " + ofToString(i) + " undefined"), 10, height/2);
			ofPopStyle();
			ofPopStyle();
			end(i);
		}
	}
	
	ExtendedFXObject::update();
}

void Patch::drawGUI(){
	ExtendedFXObject::drawGUI();

	if(preview) draw(gui.getShape().x, gui.getShape().y + gui.getShape().height, gui.getShape().width, gui.getShape().width * height/width); 
	
	if(output) output->draw();	
	for (int i = 0; i < inputs.size(); i++) {
		inputs[i]->draw();	
	}
}

void Patch::setId(int id){
	this->id =  id;
}

int Patch::getId(){
	return  id;
}


void Patch::onDelete(bool & value){
	if(value){
		gui.clear();
		manager->removePatch(id);
	}
}

void Patch::onPreview(bool & value){
	preview = value;
}

