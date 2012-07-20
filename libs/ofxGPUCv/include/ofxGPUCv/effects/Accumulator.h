#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class Accumulator : public Patch {	
	public:
		
		Accumulator * create() { return new Accumulator(); };
	
		Accumulator(){
			name = "Accumulator";
			
			maxPasses = 10;
			
			internalFormat = GL_RGBA;
			
			internalCount = 0;
			
			param1fDefaults[0].name = "Rate";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.01;
			param1fDefaults[0].max = 1.0;
			
			param1iDefaults[0].name = "Frames to skip";
			param1iDefaults[0].value = 0;
			param1iDefaults[0].min = 0;
			param1iDefaults[0].max = 30;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0;
									   uniform int param1i0;
									   uniform sampler2DRect base;
									   uniform int internalCount;
									   uniform float rate;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   
										   vec4 baseColor = texture2DRect(base, st);
										   
										   vec4 currentColor;
										   vec4 mixColor;
										   
										   if(internalCount % (param1i0 + 1) == 0){
											   // in the first pass, we consider tex0 as our current color
											   if(pass == 0){
												   currentColor = texture2DRect(tex0, st);										   
											   }
											   else{
												   // in the following steps, the backbuffer will be the current color
												   currentColor = texture2DRect(backbuffer, st);
											   }
											   gl_FragColor = mix(baseColor, currentColor, rate);
										   }
										   else{
											   gl_FragColor = baseColor;
										   }
									   }
									   );
		}
		
		void accumulateAll(){
			lastBuffer.begin();
			textures[0].draw(0, 0);
			lastBuffer.end();
			
			pingPong.src->begin();
			textures[0].draw(0, 0);
			pingPong.src->end();
			
			pingPong.dst->begin();
			textures[0].draw(0, 0);
			pingPong.dst->end();
		}
		
		bool compileCode(){
			base.allocate(width, height, internalFormat);
			return Patch::compileCode();
		}
		
		void update(){
			if(internalCount == 0) accumulateAll();
			internalCount++;
			Patch::update();
		}
		
		void onRenderPass(int pass){
			if (pass == 0) {
				base.begin();
				lastBuffer.draw(0, 0);
				base.end();
			}
			
			shader.setUniformTexture("base", lastBuffer.getTextureReference(), nTextures + 1 );
			shader.setUniform1f("rate", rate );
			shader.setUniform1i("internalCount", internalCount );
		}
		
		
		void setParam1f(float param, int _paramNum = 0){
			Patch::setParam1f(param);
			if(_paramNum == 0) calculateRate();
		}
		void setPasses(int value){
			Patch::setPasses(value);
			calculateRate();
		}
		
		void calculateRate(){
			rate = sub1u_nrt(param1fs[0], passes);
		}
		
		// This "n root" calculator is DEFNETELY NOT built for speed
		// it's rather brute, but gets the job done with high precision.
		// You should only use is when values changes, and cache the results.
		// Only works for numbers in the range 0.0 - 1.0 
		static double sub1u_nrt(double number, int n){
			if(number == 1.0) return 1.0;
			if(n == 1) return number;
			if(number > 1.0 || number < 0.0) return -1.0;
			double root = 1.0;
			double error = 1.0;
			
			double result;
			int i;
			
			double * precision = new double[16];
			precision[0] = 0.1;
			precision[1] = 0.01;
			precision[2] = 0.001;
			precision[3] = 0.0001;
			precision[4] = 0.00001;
			precision[5] = 0.000001;
			precision[6] = 0.0000001;
			precision[7] = 0.00000001;
			precision[8] = 0.000000001;
			precision[9] = 0.0000000001;
			precision[10] = 0.00000000001;
			precision[11] = 0.000000000001;
			precision[12] = 0.0000000000001;
			precision[13] = 0.00000000000001;
			precision[14] = 0.000000000000001;
			precision[15] = 0.0000000000000001;
			
			int p = 0;
			
			while (error > 0.000000000000001 || error < -0.000000000000001) { // super high precision
				if(error > 0){
					root -= precision[p];
				}
				else {
					root += precision[p];
					p++;
					root -= precision[p];
				}
				
				result = root;
				i = n;
				while (i > 0) {
					i--;
					result *= root;
				}
				error = result - number;
		
			}
			delete precision;
			return root;
			
		};
		
	private:
		double rate;
		ofFbo base;
		int internalCount;
		
	};
}