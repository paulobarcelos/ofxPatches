#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class Delay : public Patch {	
	public:
		
		Delay * create() { return new Delay(); };
	
		Delay(){
			name = "Delay";
			
			maxPasses = 1;
			
			internalFormat = GL_RGBA;
		
			param1iDefaults[0].name = "Frames";
			param1iDefaults[0].value = 1;
			param1iDefaults[0].min = 1;
			param1iDefaults[0].max = 120;
			
			useBackbuffer = false;
            allowBypass = true;
            
            bufferSize = 0;
            bufferIndex = -1;
            
            
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
                                       uniform int param1i0;
									   void main(void){}
									   );
		}

		
        void loadSettings(){
			Patch::loadSettings();
			setBufferSize(param1is[0]);
		}
        
        void setBufferSize(unsigned int bufferSize) {
            if(this->bufferSize == bufferSize) return;
            bufferIndex = -1;
            this->bufferSize = bufferSize;
            
            while (buffer.size() > 0){
                delete buffer[0];
                buffer.erase(buffer.begin());
            }            
            for (int i = 0; i < bufferSize; i++) {
                ofFbo * frame = new ofFbo();
                frame->allocate(width, height, internalFormat);
                buffer.push_back(frame);
            }
        }
		
		void update(){
			Patch::update();
            if(bypass){
                pingPong.dst->begin();
                ofClear(0,0);
                textures[0].draw(0, 0);
                pingPong.dst->end();
                pingPong.swap();
                return;
            }
            if(!buffer.size()) return;
        
            bufferIndex ++;
            bufferIndex = bufferIndex % buffer.size();
            
            
            buffer[bufferIndex]->begin();
            textures[0].draw(0, 0, width, height);
            buffer[bufferIndex]->end();
            
            
            float last = (float)(buffer.size()-1);
            int internalIndex = bufferIndex - last;
            if(internalIndex < 0) internalIndex += buffer.size();
            
            
            pingPong.dst->begin();
			ofClear(0,0,0,0);
            buffer[internalIndex]->getTexture().draw(0, 0, width, height);
			pingPong.dst->end();
			pingPong.swap();
            
		}
		
		void setParam1i(int param, int _paramNum = 0){
			Patch::setParam1i(param);
			if(_paramNum == 0) setBufferSize(param);
		}

		
	private:
        vector <ofFbo *> buffer;
        int bufferSize;
        int bufferIndex;
	};
}
