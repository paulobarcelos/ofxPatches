#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.initGrabber(640, 480);
    
    /**
	 Always this order:
	 - setup
	 - allocate
	 - registerPatch
	 - loadSettings
     **/
	
	manager.setup(1);
	manager.allocate(640, 480);
	OFX_PATCHES_REGISTER_ALL_EFFECTS(manager);
	manager.loadSettings();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    if(cam.isFrameNew()){
        manager.setTexture(cam);
        manager.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    manager.drawGUI();
}

