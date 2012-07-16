#include "ofxGPUCv/PatchInput.h"

using namespace ofxGPUCv;

PatchInput::PatchInput(Patch * parent, Patch * patch, int inputIndex){
	this->parent = parent;
	this->patch = patch;
	this->inputIndex = inputIndex;
	isConnecting = false;
	ofRegisterMouseEvents(this);
};

void PatchInput::setParent(Patch * parent){
	this->parent = parent;
};		
void PatchInput::setPatch(Patch * patch){
	this->patch = patch;
};		
void PatchInput::setInputIndex(int inputIndex){
	this->inputIndex = inputIndex;
};

Patch * PatchInput::getPatch(){
	return patch;
};
Patch * PatchInput::getParent(){
	return parent;
};
int PatchInput::getInputIndex(){
	return inputIndex;
};

void PatchInput::mouseMoved(ofMouseEventArgs & args){};
void PatchInput::mousePressed(ofMouseEventArgs & args){
	if (getShape().inside(args.x, args.y)) {
		isConnecting = true;
		patch = NULL;
		mouse.set(args.x, args.y);
	}
};
void PatchInput::mouseDragged(ofMouseEventArgs & args){
	if (isConnecting) {
		mouse.set(args.x, args.y);
	}
};
void PatchInput::mouseReleased(ofMouseEventArgs & args){
	if (isConnecting) {
		isConnecting = false;
		if (!parent) return;
		for (int i = 0; i < parent->manager->currentPatches.size(); i++){
			Patch * p = parent->manager->currentPatches[i];
			patch = p->output->getPatchIfInside(args.x, args.y);
			if (patch) return;		
		}
		patch = NULL;
	}
};

void PatchInput::draw(){
	if (!parent) return;
	ofRectangle shape = getShape();
	
	ofPushStyle();
	ofSetColor(255);
	ofRect(shape);
	ofPopStyle();
	
	if(patch){				
		ofRectangle shape2 = patch->output->getShape();
		
		ofPushStyle();
		ofSetColor(255);
		ofLine(shape.getCenter(), shape2.getCenter());
		ofPopStyle();
		
		ofPushStyle();
		ofSetColor(0);
		ofLine(shape.getCenter()+ofPoint(0,1), shape2.getCenter()+ofPoint(0,1));
		ofPopStyle();
	}
	else if(isConnecting){
		ofPushStyle();
		ofSetColor(255);
		ofLine(shape.getCenter(), mouse);
		ofPopStyle();
		
		ofPushStyle();
		ofSetColor(0);
		ofLine(shape.getCenter()+ofPoint(0,1), mouse+ofPoint(0,1));
		ofPopStyle();
	}
};

ofRectangle PatchInput::getShape(){
	if(!parent) return ofRectangle();
	ofRectangle gui = parent->gui.getShape();
	return ofRectangle(gui.x - OFX_GPUCV_PATCH_CONNECTOR_SIZE, gui.y + inputIndex * (OFX_GPUCV_PATCH_CONNECTOR_SIZE + 2), OFX_GPUCV_PATCH_CONNECTOR_SIZE, OFX_GPUCV_PATCH_CONNECTOR_SIZE);
}

Patch * PatchInput::getPatchIfInside(float x, float y){
	if(!patch) return NULL;
	if(getShape().inside(x, y)) return patch;
	else return NULL;
};