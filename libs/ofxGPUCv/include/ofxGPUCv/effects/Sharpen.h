#pragma once

#define STRINGIFY(A) #A

#include "ofxGPUCv/effects/Base5x5KernelEffect.h"


namespace ofxGPUCv {
	
	class Sharpen : public Base5x5KernelEffect {	
	public:
		Sharpen * create() { return new Sharpen(); };
		
		Sharpen(){
			name = "Sharpen";
			
			fragmentShader += STRINGIFY(
										vec4 sample[25];
										
										void main(void){											
			
											// Sample a grid around and including our texel
											if(pass == 0){											
												for (int i = 0; i < 25; i++){												
													sample[i] = texture2DRect(tex0, gl_TexCoord[0].st + offset[i]);
												}
											}else{
												for (int i = 0; i < 25; i++){												
													sample[i] = texture2DRect(backbuffer, gl_TexCoord[0].st + offset[i]);
												}
											}
											
											// Sharpen weighting:
											// -1 -1 -1 -1 -1
											// -1 -1 -1 -1 -1
											// -1 -1 25 -1 -1
											// -1 -1 -1 -1 -1
											// -1 -1 -1 -1 -1
											
											gl_FragColor = 25.0 * sample[12];
											
											for (int i = 0; i < 25; i++)
											{
												if (i != 12)
													gl_FragColor -= sample[i];
											}
										}
									   );
		}		
	};
	
}

