#pragma once

#define STRINGIFY(A) #A

#include "ofxPatches/patches/Base3x3KernelEffect.h"


namespace ofxPatches {
	
	class EdgeLaplacian : public Base3x3KernelEffect {	
	public:
		EdgeLaplacian * create() { return new EdgeLaplacian(); };
		
		EdgeLaplacian(){
			name = "Laplacian Edge";
			
			fragmentShader += STRINGIFY(
										vec4 sample[9];	
										void main(void){
											
											if(pass == 0){											
												for (int i = 0; i < 9; i++){												
													sample[i] = texture2DRect(tex0, gl_TexCoord[0].st + offset[i]);
												}
											}else{
												for (int i = 0; i < 9; i++){												
													sample[i] = texture2DRect(backbuffer, gl_TexCoord[0].st + offset[i]);
												}
											}
											//   -1 -1 -1
											//   -1  8 -1
											//   -1 -1 -1
											
											gl_FragColor = (sample[4] * 8.0) - 
															(sample[0] + sample[1] + sample[2] + 
															sample[3] + sample[5] + 
															 sample[6] + sample[7] + sample[8]);
											gl_FragColor.a = 1.0;
										}
									   );
		}		
	};
	
}

