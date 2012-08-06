#include "ofxPatches/Patch.h"
#include "ofxPatches/PatchInput.h"
#include "ofxPatches/PatchOutput.h"
#include "ofxPatches/Manager.h"

using namespace ofxPatches;

Patch::Patch(){
	output = new PatchOutput(this);
	manager = NULL;
	previewScale = 0.25;
	ExtendedFXObject::ExtendedFXObject();
}

Patch::~Patch(){
	if(output) delete output;
}

void Patch::setup(Manager * manager, string name, string filename, int id){
	if(name.compare("")){
		this->name = name;
	}
	if(filename.compare("")){
		this->filename = filename;
	}
	if(!this->filename.compare("")){
		this->filename = this->name + ".xml";
	}
	
	this->manager = manager;
	this->id = id;
	
	if(manager)	this->filename = manager->baseFolder + this->filename;	
	
	ExtendedFXObject::setup();	
}

void Patch::registerDefaultGui(){
	ExtendedFXObject::registerDefaultGui();
	
	// Add the delete button
	ofxButton * deleteButton = new ofxButton();
	deleteButton->setup("Delete", OFX_GPU_CV_GUI_SIZE);
	deleteButton->addListener(this, &Patch::onDelete);
	gui.add(deleteButton);
	
	// Add the preview slider
	ofxFloatSlider * previewSlider = new ofxFloatSlider();
	previewSlider->setup("Preview Scale", 0.25, 0., 1., OFX_GPU_CV_GUI_SIZE);
	previewSlider->addListener(this, &Patch::onPreviewScaleChange);
	gui.add(previewSlider);
}

void Patch::setLabel(int label){
	this->label = label;
}

int Patch::getLabel(){
	return label;
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
			ofSetColor(255,10,10);
			ofRect(0,0,width,height);		
			ofPopStyle();
			end(i);
		}
	}
	
	ExtendedFXObject::update();
}

void Patch::drawGUI(){
	ExtendedFXObject::drawGUI();
	
	ofPushStyle();
	ofEnableAlphaBlending();	
	ofSetColor(255);
	ofDrawBitmapString(ofToString(id), gui.getShape().x, gui.getShape().y - 1);
	ofPopStyle();
	
	if(previewScale > 0){
		draw(gui.getShape().x, gui.getShape().y + gui.getShape().height, width*previewScale, height*previewScale); 
	}
	
	if(output) output->draw();	
	for (int i = 0; i < inputs.size(); i++) {
		inputs[i]->draw();	
	}
}

void Patch::applyGuiValues(){
	ExtendedFXObject::applyGuiValues();
	onPreviewScaleChange(gui.getFloatSlider("Preview Scale"));
}

void Patch::saveSettings(){
	gui.saveToFile(filename);
}

void Patch::loadSettings(){
	gui.loadFromFile(filename);
	applyGuiValues();
}

void Patch::setId(int id){
	this->id =  id;
}

int Patch::getId(){
	return  id;
}

void Patch::selfDelete(){
	gui.clear();
	manager->removePatch(id);
}


void Patch::onDelete(bool & value){
	if(value){
		selfDelete();
	}
}

void Patch::onPreviewScaleChange(float & value){
	previewScale = value;
}

