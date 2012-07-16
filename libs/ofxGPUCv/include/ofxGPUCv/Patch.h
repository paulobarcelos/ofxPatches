#pragma once

#include "ofMain.h"
#include "ExtendedFXObject.h"

#define OFX_GPUCV_PATCH_CONNECTOR_SIZE 7

namespace ofxGPUCv {
	
	class PatchInput; // forward declaration!
	class PatchOutput; // forward declaration!

	class Patch : public ExtendedFXObject {
		friend class PatchInput;
		friend class PatchOutput;
	public:
		Patch();
		~Patch();
		bool compileCode();	
		void update();		
		void addInput(Patch * patch, int index = 0);		
		void drawGUI();
		Patch * getOutput(float x, float y);
		
	protected:
		vector<PatchInput*> inputs;
		PatchOutput* output;
		
	};
	
	class PatchOutput {
		friend class PatchInput;
	public:
		PatchOutput(Patch * parent = NULL){
			this->parent = parent;
		};
		
		void setParent(Patch * parent){
			this->parent = parent;
		};		
		
		Patch * getParent(){
			return parent;
		};
		
		void draw(){
			if (!parent) return;
			ofRectangle shape = getShape();
			
			ofPushStyle();
			ofSetColor(255);
			ofRect(shape);
			ofPopStyle();
		};
		
		ofRectangle getShape(){
			if(!parent) return ofRectangle();
			ofRectangle gui = parent->gui.getShape();
			return ofRectangle(gui.x + gui.width, gui.y, OFX_GPUCV_PATCH_CONNECTOR_SIZE, OFX_GPUCV_PATCH_CONNECTOR_SIZE);
		}
		
		Patch * getPatchIfInside(float x, float y){
			if(!parent) return NULL;
			if(getShape().inside(x, y)) return parent;
			else return NULL;
		};
	private:	
		Patch * parent;		
	};
	
	class PatchInput {
		friend class PatchOutput;
	public:
		PatchInput(Patch * parent = NULL, Patch * patch = NULL, int inputIndex = -1){
			this->parent = parent;
			this->patch = patch;
			this->inputIndex = inputIndex;
			isConnecting = false;
			ofRegisterMouseEvents(this);
		};
		
		void setParent(Patch * parent){
			this->parent = parent;
		};		
		void setPatch(Patch * patch){
			this->patch = patch;
		};		
		void setInputIndex(int inputIndex){
			this->inputIndex = inputIndex;
		};
		
		Patch * getPatch(){
			return patch;
		};
		Patch * getParent(){
			return parent;
		};
		int getInputIndex(){
			return inputIndex;
		};
		
		void mouseMoved(ofMouseEventArgs & args){};
		void mousePressed(ofMouseEventArgs & args){
			if (getShape().inside(args.x, args.y)) {
				isConnecting = true;
				patch = NULL;
				mouse.set(args.x, args.y);
			}
		};
		void mouseDragged(ofMouseEventArgs & args){
			if (isConnecting) {
				mouse.set(args.x, args.y);
			}
		};
		void mouseReleased(ofMouseEventArgs & args){
			if (isConnecting) {
				isConnecting = false;
				//patch = NULL;
			}
		};
		
		void draw(){
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
		
		ofRectangle getShape(){
			if(!parent) return ofRectangle();
			ofRectangle gui = parent->gui.getShape();
			return ofRectangle(gui.x - OFX_GPUCV_PATCH_CONNECTOR_SIZE, gui.y + inputIndex * (OFX_GPUCV_PATCH_CONNECTOR_SIZE + 2), OFX_GPUCV_PATCH_CONNECTOR_SIZE, OFX_GPUCV_PATCH_CONNECTOR_SIZE);
		}
		
		Patch * getPatchIfInside(float x, float y){
			if(!patch) return NULL;
			if(getShape().inside(x, y)) return patch;
			else return NULL;
		};
	private:	
		Patch * parent;
		Patch * patch;
		int inputIndex;
		bool isConnecting;
		ofPoint mouse;
		
	};
}