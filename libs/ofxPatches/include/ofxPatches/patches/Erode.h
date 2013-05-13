#pragma once

#define STRINGIFY(A) #A

#include "ofxPatches/patches/Base5x5KernelEffect.h"


namespace ofxPatches {
	
	class Erode : public Base5x5KernelEffect {	
	public:
		Erode * create() { return new Erode(); };
		
		Erode(){
			name = "Erode";
			
			fragmentShader += STRINGIFY(
									   vec4 sample[25];										
									   void main(void){											
										   
										   vec4 maxValue = vec4(1.0);
										   
										   // Sample a grid around and including our texel
										   if(pass == 0){											
											   for (int i = 0; i < 25; i++){												
												   sample[i] = texture2DRect(tex0, gl_TexCoord[0].st + offset[i]);
												   // Keep the maximum value		
												   maxValue = min(sample[i], maxValue);
											   }
										   }else{
											   for (int i = 0; i < 25; i++){												
												   sample[i] = texture2DRect(backbuffer, gl_TexCoord[0].st + offset[i]);
												   // Keep the maximum value		
												   maxValue = min(sample[i], maxValue);
											   }
										   }
										   gl_FragColor = maxValue;
									   }
									   );
		}		
	};
	
}

