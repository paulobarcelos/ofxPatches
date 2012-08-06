#pragma once

//Derived from original code from Andrew Benson - andrewb@cycling74.com
//2009

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class OpticalFlow : public Patch {	
	public:
		
		OpticalFlow * create() { return new OpticalFlow(); };
	
		OpticalFlow(){
			name = "Optical Flow";			
			
			param1fDefaults[0].name = "Scale";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 5.0;
			
			param1fDefaults[1].name = "Offset";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 5.0;
			
			param1fDefaults[2].name = "Lambda";
			param1fDefaults[2].value = 0.0;
			param1fDefaults[2].min = 0.0;
			param1fDefaults[2].max = 5.0;
			
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0; //current frame
									   uniform sampler2DRect last; //last frame
									   
									   uniform float param1f0; //scale
									   uniform float param1f1; //offset
									   uniform float param1f2; //lambda
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   vec2 scale = vec2(param1f0, param1f0);
										   vec2 offset = vec2(param1f1, param1f1);
										   float lambda = param1f2;
										   
										   vec4 a = texture2DRect(last, st);
										   vec4 b = texture2DRect(tex0, st);
										   vec2 x1 = vec2(offset.x,0.);
										   vec2 y1 = vec2(0.,offset.y);
										   
										   //get the difference
										   vec4 curdif = b-a;
										   
										   //calculate the gradient
										   vec4 gradx = texture2DRect(tex0, st+x1)-texture2DRect(tex0, st-x1);
										   gradx += texture2DRect(last, st+x1)-texture2DRect(last, st-x1);
										   
										   vec4 grady = texture2DRect(tex0, st+y1)-texture2DRect(tex0, st-y1);
										   grady += texture2DRect(last, st+y1)-texture2DRect(last, st-y1);
										   
										   vec4 gradmag = sqrt((gradx*gradx)+(grady*grady)+vec4(lambda));
										   
										   vec4 vx = curdif*(gradx/gradmag);
										   float vxd = vx.r;//assumes greyscale
										   //format output for flowrepos, out(-x,+x,-y,+y)
										   vec2 xout = vec2(max(vxd,0.),abs(min(vxd,0.)))*scale.x;
										   
										   vec4 vy = curdif*(grady/gradmag);
										   float vyd = vy.r;//assumes greyscale
										   //format output for flowrepos, out(-x,+x,-y,+y)
										   vec2 yout = vec2(max(vyd,0.),abs(min(vyd,0.)))*scale.y;
										   
										   //	gl_FragColor = vec4(yout.xy,yout.xy);
										   
										   gl_FragColor = vec4(xout.xy,yout.xy);
									   }
									   );
		}
		
		bool compileCode(){
			last.allocate(width, height, internalFormat);
			return Patch::compileCode();
		}
		void update(){
			Patch::update();
			last.begin();
			textures[0].draw(0, 0);
			last.end();
		}
		
		void onShaderPass(int pass){
			shader.setUniformTexture("last", last.getTextureReference(), nTextures + 1 );
		}
		
		private:
			ofFbo last;
		
	};
}