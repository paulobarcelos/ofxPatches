#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	//ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	input.setup("Camera");
	input.allocate(640, 480);
	input.setSource(cam);
	
	redBoost.setup();
	redBoost.allocate(640, 480);
	redBoost.setGUIPosition(200, 0);
	redBoost.addInput(&input);
	
	
	
	//stack.setup("My stack");
	//stack.allocate(640, 480);
	
	//stack.registerEffect<ofxGPUCv::RedBoost>();
	
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	if(cam.isFrameNew()){
		
		input.update();
		
		redBoost.update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	input.drawGUI();
	
	redBoost.drawGUI();
	
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