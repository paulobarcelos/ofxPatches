#pragma once

#define STRINGIFY(A) #A

#include "ofxGPUCv/effects/Base5x5KernelEffect.h"


namespace ofxGPUCv {
	
	class Dilate : public Base5x5KernelEffect {	
	public:
		Dilate * create() { return new Dilate(); };
		
		Dilate(){
			name = "Dilate";
			
			fragmentShader += STRINGIFY(
										vec4 sample[25];										
										void main(void){											
											
											vec4 maxValue = vec4(0.0);
											
											// Sample a grid around and including our texel
											if(pass == 0){											
												for (int i = 0; i < 25; i++){												
													sample[i] = texture2DRect(tex0, gl_TexCoord[0].st + offset[i]);
													// Keep the maximum value		
													maxValue = max(sample[i], maxValue);
												}
											}else{
												for (int i = 0; i < 25; i++){												
													sample[i] = texture2DRect(backbuffer, gl_TexCoord[0].st + offset[i]);
													// Keep the maximum value		
													maxValue = max(sample[i], maxValue);
												}
											}
											gl_FragColor = maxValue;
										}
									   );
		}		
	};
	
}

