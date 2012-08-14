#pragma once

#include "ofxPatches/patches/ColorBlock.h"

#define STRINGIFY(A) #A


namespace ofxPatches {
	
	class Paintbrush : public ColorBlock {	
	public:
		Paintbrush * create() { return new Paintbrush(); };
		
		Paintbrush(){
			name = "Paintbrush";
			
			param1fDefaults[4].name = "Brush Size";
			param1fDefaults[4].value = 50.0;
			param1fDefaults[4].min = 0.0;
			param1fDefaults[4].max = 200.0;
			
			param1fDefaults[5].name = "Brush Softness";
			param1fDefaults[5].value = 0.5;
			param1fDefaults[5].min = 0.0;
			param1fDefaults[5].max = 1.0;
			
			useBackbuffer = true;
			
			fragmentShader = STRINGIFY(
									   
									   uniform float param1f0; //h
									   uniform float param1f1; //s
									   uniform float param1f2; //l
									   uniform float param1f3; //a									   
									   uniform float param1f4; //size
									   uniform float param1f5; //softness
									   
									   uniform vec2 size;
									   
									   uniform vec2 pos;
									   uniform int pressed;
									   
									   uniform float r;
									   uniform float g;
									   uniform float b;
									   
									   uniform sampler2DRect backbuffer;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;										   
										   vec4 baseColor = texture2DRect(backbuffer, st);
										   vec4 brushColor = vec4(r, g, b, param1f3);
										   brushColor.a *= pow( 1.0 - (distance(st, pos * vec2(size.x, size.y)) / param1f4), param1f5);
										   
										   //if(pressed == 1 ) gl_FragColor = mix(baseColor, brushColor, brushColor.a);
										   //else gl_FragColor = baseColor;
										   
										   if(pressed == 1 && distance(st, pos * vec2(size.x, size.y)) < param1f4)
											   gl_FragColor = vec4(mix(baseColor, brushColor, brushColor.a).rgb,  baseColor.a +  brushColor.a);
										   else gl_FragColor = baseColor;
										  
										   /*if(pressed == 1) gl_FragColor = mix(baseColor, brushColor, brushColor.a);
											else gl_FragColor = baseColor;*/
									   }
										   
									   
									   );
		}
		
		
		void allocate(int _width, int _height){
			Patch::allocate(_width, _height);
			diskImage.allocate(_width, _height, OF_IMAGE_COLOR_ALPHA);
			
		}
		
		void saveSettings(){
			Patch::saveSettings();
			pingPong.dst->readToPixels(diskImage.getPixelsRef());
			diskImage.saveImage(manager->getBaseFolder() + ofToString(id) + ".png");
		}
		
		void loadSettings(){
			Patch::loadSettings();
			diskImage.loadImage(manager->getBaseFolder() + ofToString(id) + ".png");
			
			pingPong.dst->begin();        
			diskImage.draw(0, 0);
			pingPong.dst->end();
			
			pingPong.src->begin();        
			diskImage.draw(0, 0);
			pingPong.src->end();
			
			lastBuffer.begin();        
			diskImage.draw(0, 0);
			lastBuffer.end();
		}
		
		void setParam1f(float param, int _paramNum = 0){
			ColorBlock::setParam1f(param, _paramNum);
		}
		
		void onShaderPass(int pass){
			ColorBlock::onShaderPass(pass);
			shader.setUniform2f("pos", 
								((float) ofGetMouseX() - gui.getShape().x)/ (width * previewScale),
								((float) ofGetMouseY() - gui.getShape().y - gui.getShape().height) / (height * previewScale));
			shader.setUniform1i("pressed", (ofGetMousePressed())?1:0);			
			
		}
		
		void registerDefaultGui(){			
			Patch::registerDefaultGui();
			
			// Add the clear button
			ofxButton * clear = new ofxButton();
			clear->setup("Clear", OFX_GPU_CV_GUI_SIZE);
			clear->addListener(this, &Paintbrush::onClearPress);
			gui.add(clear);
		};
		
		void onClearPress(bool & value){
			if(value){
				clear();
			}
		}
		
		void clear(){
			pingPong.dst->begin();        
			ofClear(0,0);
			pingPong.dst->end();
			
			pingPong.src->begin();        
			ofClear(0,0);
			pingPong.src->end();
			
			lastBuffer.begin();        
			ofClear(0,0);
			lastBuffer.end();
		}
		private:
			float size;
			float softness;
			ofImage diskImage;
		
	};
	
}