#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	cam.initGrabber(640, 480);
	
	redBoost.setup();
	redBoost.allocate(640, 480);
	
	stack.setup("My stack");
	stack.allocate(640, 480);
	
	stack.registerEffect<ofxGPUCv::RedBoost>();
	
	
	
}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	if(cam.isFrameNew()){
		//redBoost.setTexture(cam.getTextureReference());
		//redBoost.update();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	//redBoost.draw(0,0);
	stack.drawGUI();
	//redBoost.drawGUI();
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