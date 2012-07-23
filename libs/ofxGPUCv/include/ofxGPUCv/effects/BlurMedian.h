#pragma once

#define STRINGIFY(A) #A

#include "ofxGPUCv/effects/Base5x5KernelEffect.h"


namespace ofxGPUCv {
	
	class BlurMedian : public Base5x5KernelEffect {	
	public:
		BlurMedian * create() { return new BlurMedian(); };
		
		BlurMedian(){
			name = "Median Blur";
			
			fragmentShader += STRINGIFY(
										void main(void){											
											
											vec4 color;
											// Sample a grid around and including our texel
											if(pass == 0){											
												for (int i = 0; i < 25; i++){												
													color += texture2DRect(tex0, gl_TexCoord[0].st + offset[i]);
												}
											}else{
												for (int i = 0; i < 25; i++){												
													color += texture2DRect(backbuffer, gl_TexCoord[0].st + offset[i]);
												}
											}
											
											gl_FragColor = color / 25.0;
										}
											
									   );
		}		
	};
	
}

