#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){
	ofSetLogLevel(OF_LOG_WARNING);
	ofSetVerticalSync(true);
	ofSetWindowPosition(0, 0);
	image.loadImage("lena.jpeg");
		/**
	 Always this order:
	 - setup
	 - allocate
	 - registerPatch
	 - loadSettings
	**/
	
	manager.setup(1, "My stack");
	manager.allocate(600, 600);
	OFX_PATCHES_REGISTER_ALL_EFFECTS(manager);	
	manager.loadSettings();
}

//--------------------------------------------------------------
void testApp::update(){
	
    manager.setTexture(image);
	
	manager.update();
}

//--------------------------------------------------------------
void testApp::draw(){
	manager.drawGUI();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}