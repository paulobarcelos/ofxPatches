#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    cam.initGrabber(640, 480);
    video.loadMovie("movie.mov");
    video.play();
    video.setVolume(0);
    
    /**
	 Always this order:
	 - setup
	 - allocate
	 - registerPatch
	 - loadSettings
     **/
	
	manager.setup(2);
	manager.allocate(640, 480);
	OFX_PATCHES_REGISTER_ALL_EFFECTS(manager);
	manager.loadSettings();
}

//--------------------------------------------------------------
void ofApp::update(){
    cam.update();
    video.update();
    if(cam.isFrameNew() || video.isFrameNew()){
        manager.setTexture(cam,0);
        manager.setTexture(video,1);
        manager.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    manager.drawGUI();
}

