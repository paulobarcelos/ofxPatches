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
			
			maxPasses = 100;
			
			internalFormat = GL_RGBA;
			
			param1fDefaults[0].name = "Rate";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 0.1;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect base;
									   uniform float param1f0;
									   uniform float rate;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   
										   vec4 baseColor;
										   vec4 currentColor;
										   vec4 mixColor;
										   
										   // in the first pass, we consider tex0 as our current color
										   if(pass == 0){
											   currentColor = texture2DRect(tex0, st);										   
										   }
										   else{
											   // in the following steps, the backbuffer will be the current color
											   currentColor = texture2DRect(backbuffer, st);
										   }
										  
										   baseColor = texture2DRect(base, st);
										   
										   mixColor = mix(baseColor, currentColor, rate);
										   gl_FragColor = mixColor;
									   }
									   );
		}
		
		bool compileCode(){
			base.allocate(width, height, internalFormat);
			return Patch::compileCode();
		}
		
		void onRenderPass(int pass){
			if (pass == 0) {
				base.begin();
				lastBuffer.draw(0, 0);
				base.end();
			}
			shader.setUniformTexture("base", lastBuffer.getTextureReference(), nTextures + 1 );
			shader.setUniform1f("rate", rate );
		}
		
		void onParam1fChange(float & value){
			Patch::onParam1fChange(value);
			calculateRate();
		}
		void onPassesChange(int & value){
			Patch::onPassesChange(value);
			calculateRate();
		}
		
		void calculateRate(){
			rate = sub1u_nrt(param1fs[0]*param1fs[0], passes);
		}
		
		// This "n root" calculator is DEFNETELY NOT built for speed
		// it's rather brute, but gets the job done with haigh precision.
		// You should only use is when values changes, and cache the results.
		// Only works for numbers in the range 0.0 - 1.0 
		static double sub1u_nrt(double number, int n){
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
			
			while (error > 1.00000e-16 || error < -1.00000e-16) { // super high precision
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
		
				//cout << "root " << root << " result " << result << " error " << error<< endl;
			}
			delete precision;
			return root;
			
		};
		
	private:
		double rate;
		ofFbo base;
		
	};
}