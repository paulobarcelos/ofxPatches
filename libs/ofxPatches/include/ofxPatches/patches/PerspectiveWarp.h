/*
* This patch is inspired (a.k.a. a massive copy and paste)
* in ofxGLWarper by Roy Macdonald. See http://github.com/ofxGLWarper
*/

#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"
#include "ofxHomography.h"


namespace ofxPatches {
    
    class PerspectiveWarp : public Patch {
        public:
        PerspectiveWarp * create() { return new PerspectiveWarp(); };
        
        PerspectiveWarp(){
            name = "Perspective Warp";
            
            corners[0].x = 0.0;
            corners[0].y = 0.0;
            
            corners[1].x = 1.0;
            corners[1].y = 0.0;
            
            corners[2].x = 1.0;
            corners[2].y = 1.0;
            
            corners[3].x = 0.0;
            corners[3].y = 1.0;
            
            active = false;

            whichCorner = -1;
            
            x = y = 0;
                        
            fragmentShader = STRINGIFY(
                                       uniform sampler2DRect tex0;
                                       void main(void){}
                                       );
        }
        bool compileCode(){
            bool success = Patch::compileCode();
            shader.unload();
            return success;
        }
        
        void saveSettings(){
            Patch::saveSettings();
            save(manager->getBaseFolder() + ofToString(id) + "+_warp.xml");
        }
        
        void loadSettings(){
            Patch::loadSettings();
            loadXML(manager->getBaseFolder() + ofToString(id) + "+_warp.xml");
        }
        
        void applyGuiValues(){
            Patch::applyGuiValues();
            bool enableWarping = gui.getToggle("Enable warping");
            onEnableWarping(enableWarping);
        }
        
        void registerDefaultGui(){
            Patch::registerDefaultGui();
            
            ofxToggle * enableWarpingToogle = new ofxToggle();
            enableWarpingToogle->setup("Enable warping", false, OFX_PATCHES_GUI_SIZE);
            enableWarpingToogle->addListener(this, &PerspectiveWarp::onEnableWarping);
            gui.add(enableWarpingToogle);
        }
        
        void onEnableWarping(bool & value){
            if (value == true) {
                activate();
            } else {
                deactivate();
            }
        }
        
        void onRender(int pass){
            ofClear(0, 0, 0, 0);
            begin();
            textures[0].draw(0, 0);
            end();
        }
        
        void drawGUI(){
            
            if(isActive()){
                ofPushMatrix();
                ofTranslate(gui.getShape().x, gui.getShape().y + gui.getShape().height);
                ofScale(previewScale, previewScale);
                
                begin();
                
                ofPushStyle();
                ofSetColor(255, 255, 255, 100);
                textures[0].draw(0, 0);
                ofPopStyle();
                
                ofPushStyle();
                ofSetColor(255, 255, 0);
                ofSetLineWidth(2);
                ofNoFill();
                ofDrawRectangle(-1,-1, width+1,height+1);
                ofPopStyle();
                
                end();
                
                ofPopMatrix();
            }
            
            Patch::drawGUI();
        }
        
        //--------------------------------------------------------------
        void mouseDragged(ofMouseEventArgs &args){
            float scaleX = ((float)args.x - gui.getShape().x)/(width*previewScale);
            float scaleY = ((float)args.y - gui.getShape().y - gui.getShape().height)/(height*previewScale);
            
            if(whichCorner >= 0){
                corners[whichCorner].x = scaleX;
                corners[whichCorner].y = scaleY;
            }
        }
        //--------------------------------------------------------------
        void mousePressed(ofMouseEventArgs &args){
            float smallestDist = 1.0;
            whichCorner = -1;
    
            for(int i = 0; i < 4; i++){
                float distx = corners[i].x - ((float)args.x - gui.getShape().x)/(width*previewScale);
                float disty = corners[i].y - ((float)args.y - gui.getShape().y - gui.getShape().height)/(height*previewScale);
                float dist  = sqrt( distx * distx + disty * disty);
                
                if(dist < smallestDist && dist < 0.1){
                    whichCorner = i;
                    smallestDist = dist;
                }
            }
            
        }
        //--------------------------------------------------------------
        void mouseReleased(ofMouseEventArgs &args){
            whichCorner = -1;
        }
        //--------------------------------------------------------------
        void mouseMoved(ofMouseEventArgs &args){}
    //--------------------------------------------------------------
    void mouseScrolled(ofMouseEventArgs &args){}
    //--------------------------------------------------------------
    void mouseEntered(ofMouseEventArgs &args){}
    //--------------------------------------------------------------
    void mouseExited(ofMouseEventArgs &args){}

        private:
        float x, y;
        bool active;
        ofPoint corners[4];
        int whichCorner;
    ofMatrix4x4 myMatrix;
        
        //--------------------------------------------------------------
        bool isActive(){
            return active;
        }
        //--------------------------------------------------------------
        void activate(){
            ofRegisterMouseEvents(this);
            active=true;
        }
        //--------------------------------------------------------------
        void deactivate(){
            ofUnregisterMouseEvents(this);
            active=false;
        }
        //--------------------------------------------------------------
        void processMatrices(){
      ofPoint originalCorners[4];
      ofPoint distortedCorners[4];
      
      //we set the warp coordinates
      //source coordinates as the dimensions of our window
      originalCorners[0].x = x;
      originalCorners[0].y = y;
      originalCorners[1].x = x+width;
      originalCorners[1].y = y;
      originalCorners[2].x = x+width;
      originalCorners[2].y = y+height;
      originalCorners[3].x = x;
      originalCorners[3].y = y+height;
              
      //corners are in 0.0 - 1.0 range
      //so we scale up so that they are at the window's scale
      for(int i = 0; i < 4; i++){
          distortedCorners[i].x = corners[i].x  * (float)width;
          distortedCorners[i].y = corners[i].y * (float)height;
      }
      
      myMatrix = ofxHomography::findHomography(originalCorners, distortedCorners);
        }
        //--------------------------------------------------------------
        void begin(){
            if (active) {
                processMatrices();
            }
      ofPushMatrix();
      ofMultMatrix(myMatrix);
        }
        //--------------------------------------------------------------
        void end(){
      ofPopMatrix();
        }
        //--------------------------------------------------------------
        void save(string saveFile){
            ofxXmlSettings XML;
            XML.clear();
            XML.addTag("corners");
            XML.pushTag("corners");

            for(int i =0; i<4; i++){
                int t = XML.addTag("corner");
                XML.setValue("corner:x",corners[i].x, t);
                XML.setValue("corner:y",corners[i].y, t);
            }
            XML.saveFile(saveFile);
        }
        //--------------------------------------------------------------
        void loadXML(string loadFile){
            ofxXmlSettings XML;
            if( !XML.loadFile(loadFile) ){
                ofLog(OF_LOG_ERROR, "ofxGLWarper : xml file not loaded. Check file path.");
            }

            if(!XML.tagExists("corners")){
                ofLog(OF_LOG_ERROR, "ofxGLWarper : incorrrect xml formating. No \"corners\" tag found");
                return;
            }
            XML.pushTag("corners");
            if (XML.getNumTags("corner")<4 ) {
                ofLog(OF_LOG_ERROR, "ofxGLWarper : incorrrect xml formating. less than 4 \"corner\" tags found");
                return;
            }
            for(int i =0; i<4; i++){
                int t = XML.addTag("corner");
                XML.pushTag("corner", i);
                if (XML.tagExists("x") && XML.tagExists("y")){
                    corners[i].x = XML.getValue("x", double(1.0));
                    corners[i].y = XML.getValue("y", double(1.0));
                }
                XML.popTag();
            }
         
            processMatrices();
            ofLog(OF_LOG_ERROR, "ofxGLWarper : xml file loaded OK!.");
    }
    };
}
