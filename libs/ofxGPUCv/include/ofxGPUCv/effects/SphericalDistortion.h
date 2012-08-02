#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxGPUCv/Patch.h"


namespace ofxGPUCv {
	
	class SphericalDistortion : public Patch {	
	public:
		SphericalDistortion * create() { return new SphericalDistortion(); };
		
		SphericalDistortion(){
			name = "Spherical Distortion";
			
			param1fDefaults[0].name = "size";
			param1fDefaults[0].value = 1.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 10.0;
			
			param1fDefaults[1].name = "amount";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = -5.0;
			param1fDefaults[1].max = 5.0;
			
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0; //size
									   uniform float param1f1; //amount									   
									   uniform vec2 size;
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   
										   vec2 imageCenter = size / 2.;
										   vec2 P = (st / imageCenter) - 1.; // to normalized image coordinates
										   P /= param1f0;
										   vec2 Pp = P / (1. - param1f1 * dot(P, P));
										   P *= param1f0;
										   st = (Pp + 1.) * imageCenter;  // back to pixel coordinates
										   
										   gl_FragColor = texture2DRect(tex0, st);
									   }
									   );
		}
	};
	
	
	
}