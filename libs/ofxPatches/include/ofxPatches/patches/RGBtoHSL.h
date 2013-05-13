#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class RGBtoHSL : public Patch {
	public:
		RGBtoHSL * create() { return new RGBtoHSL(); };
		
		RGBtoHSL(){
			name = "RGB to HSL";
			
			maxPasses = 1;
			internalFormat = GL_RGBA;
            
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   
									   vec3 RGBToHSL(vec3 color){
										   vec3 hsl;
										   float fmin = min(min(color.r, color.g), color.b);
										   float fmax = max(max(color.r, color.g), color.b);
										   float delta = fmax - fmin;
										   hsl.z = (fmax + fmin) / 2.0;
										   if (delta == 0.0){
											   hsl.x = 0.0;
											   hsl.y = 0.0;
										   } else {
											   if (hsl.z < 0.5)
												   hsl.y = delta / (fmax + fmin);
											   else
												   hsl.y = delta / (2.0 - fmax - fmin);
											   
											   float deltaR = (((fmax - color.r) / 6.0) + (delta / 2.0)) / delta;
											   float deltaG = (((fmax - color.g) / 6.0) + (delta / 2.0)) / delta;
											   float deltaB = (((fmax - color.b) / 6.0) + (delta / 2.0)) / delta;
											   
											   if (color.r == fmax )
												   hsl.x = deltaB - deltaG;
											   else if (color.g == fmax)
												   hsl.x = (1.0 / 3.0) + deltaR - deltaB;
											   else if (color.b == fmax)
												   hsl.x = (2.0 / 3.0) + deltaG - deltaR;
											   
											   if (hsl.x < 0.0)
												   hsl.x += 1.0;
											   else if (hsl.x > 1.0)
												   hsl.x -= 1.0;
										   }
										   return hsl;
									   }
									   
									   void main(void){
										   vec2 st = gl_TexCoord[0].st;
										   vec4 color = texture2DRect(tex0, st);
										   
										   vec3 hsl = RGBToHSL(color.rgb);
										   
										   gl_FragColor = vec4(hsl, color.a);
									   }
									   );
		}
	};
	
}