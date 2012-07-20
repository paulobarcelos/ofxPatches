#include "testApp.h"




//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	/**
	 Always this order:
	 - setup
	 - allocate
	 - registerPatch
	 - loadSettings
	**/
	
	manager.setup(1, "My stack");
	manager.allocate(640, 480);
	OFX_GPU_CV_REGISTER_ALL_EFFECTS(manager);	
	manager.loadSettings();
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	if(cam.isFrameNew()){
		manager.setTexture(cam.getTextureReference());
		manager.update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	manager.draw(0,0);
	manager.drawGUI();
	
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 10,10);
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