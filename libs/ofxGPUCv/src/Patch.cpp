#include "ofxGPUCv/Patch.h"
using namespace ofxGPUCv;

Patch::Patch(){
	output = new PatchOutput(this);
	ExtendedFXObject::ExtendedFXObject();
}

Patch::~Patch(){
	delete output;
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

void Patch::addInput(Patch * patch, int index){
	//if (inputs.size() && index >= 0 && index < inputs.size() - 1) {
		inputs[index]->setPatch(patch); 
	//}
}


/*void Patch::onMouseDragged(ofMouseEventArgs & args){
	ofRectangle r = gui.getShape();
	
	for (int i = 0; i < inputs.size(); i++) {
		ofRectangle inputRectangle = ofRectangle(r.x -7, r.y + i * (7 + 2), 7, 7);
		
	}
}*/

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

	output->draw();	
	for (int i = 0; i < inputs.size(); i++) {
		inputs[i]->draw();	
	}
}

