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
	OFX_GPU_CV_REGISTER_ALL_EFFECTS(manager);	
	manager.loadSettings();
	
	TIME_SAMPLE_SET_FRAMERATE(60);
}

//--------------------------------------------------------------
void testApp::update(){
	
		TIME_SAMPLE_START("update");
    manager.begin();
    image.draw(0, 0, 600, 600);
    manager.end();
		TIME_SAMPLE_STOP("update");
	
}

//--------------------------------------------------------------
void testApp::draw(){
	TIME_SAMPLE_START("gui");
	manager.drawGUI();
	TIME_SAMPLE_STOP("gui");
	
	TIME_SAMPLE_DRAW(10, 10);
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