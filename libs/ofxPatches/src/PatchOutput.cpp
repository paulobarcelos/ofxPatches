#include "ofxPatches/PatchOutput.h"

using namespace ofxPatches;
	
PatchOutput::PatchOutput(Patch * parent){
	this->parent = parent;
};

void PatchOutput::setParent(Patch * parent){
	this->parent = parent;
};		

Patch * PatchOutput::getParent(){
	return parent;
};

void PatchOutput::draw(){
	if (!parent) return;
	ofRectangle shape = getShape();
	
	ofPushStyle();
	ofSetColor(0);
	ofCircle(shape.getCenter(), shape.width/2);
	ofPopStyle();
};

ofRectangle PatchOutput::getShape(){
	if(!parent) return ofRectangle();
	ofRectangle gui = parent->gui.getShape();
	return ofRectangle(gui.x + gui.width  + 1, gui.y + 2, OFX_GPU_CV_PATCH_CONNECTOR_SIZE, OFX_GPU_CV_PATCH_CONNECTOR_SIZE);
}

Patch * PatchOutput::getPatchIfInside(float x, float y){
	if(!parent) return NULL;
	if(getShape().inside(x, y)) return parent;
	else return NULL;
};