#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_WARNING);
	foreground.loadImage("foreground.jpg");
	background.loadImage("background.jpg");
	
	/**
	 Always this order:
	 - setup
	 - allocate
	 - registerPatch
	 - loadSettings
	**/
	
	manager.setup(2, "Patches");
	manager.allocate(720, 480);
	OFX_PATCHES_REGISTER_ALL_EFFECTS(manager);	
	manager.loadSettings();
}

//--------------------------------------------------------------
void testApp::update(){	
    manager.setTexture(foreground, 0);
	manager.setTexture(background, 1);
	manager.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw(){
	manager.drawGUI();
}
