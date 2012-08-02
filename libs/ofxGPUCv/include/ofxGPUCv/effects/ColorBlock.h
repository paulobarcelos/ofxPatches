#pragma once

#define STRINGIFY(A) #A

#include "ofxGPUCv/Patch.h"

namespace ofxGPUCv {
	
	class ColorBlock : public Patch {	
	public:
		ColorBlock * create() { return new ColorBlock(); };
		
		ColorBlock(){
			name = "Color Block";
			
			cout << name << endl;
			
			param1fDefaults[0].name = "Hue";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "Saturation";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
			
			param1fDefaults[2].name = "Luminosity";
			param1fDefaults[2].value = 0.0;
			param1fDefaults[2].min = 0.0;
			param1fDefaults[2].max = 1.0;
			
			param1fDefaults[3].name = "Alpha";
			param1fDefaults[3].value = 1.0;
			param1fDefaults[3].min = 0.0;
			param1fDefaults[3].max = 1.0;
			
			fragmentShader = STRINGIFY(
										uniform float param1f0;
										uniform float param1f1;
										uniform float param1f2;
										uniform float param1f3;
										
										uniform float r;
										uniform float g;
										uniform float b;
										
										void main(void){
											gl_FragColor = vec4(r,g,b,param1f3);
										}
										);
		}
		
		void setParam1f(float param, int _paramNum = 0){
			Patch::setParam1f(param, _paramNum);
			color = HSLToRGB(ofVec3f(param1fs[0], param1fs[1], param1fs[2]));
		}
		
		void onShaderPass(int pass){
			shader.setUniform1f("r", color.x);
			shader.setUniform1f("g", color.y);
			shader.setUniform1f("b", color.z);
		}
		
		ofVec3f RGBToHSL(ofVec3f color){
			ofVec3f hsl;
			float fmin = min(min(color.x, color.y), color.z);
			float fmax = max(max(color.x, color.y), color.z);
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
				
				float deltaR = (((fmax - color.x) / 6.0) + (delta / 2.0)) / delta;
				float deltaG = (((fmax - color.y) / 6.0) + (delta / 2.0)) / delta;
				float deltaB = (((fmax - color.z) / 6.0) + (delta / 2.0)) / delta;
				
				if (color.x == fmax )
					hsl.x = deltaB - deltaG;
				else if (color.y == fmax)
					hsl.x = (1.0 / 3.0) + deltaR - deltaB;
				else if (color.z == fmax)
					hsl.x = (2.0 / 3.0) + deltaG - deltaR;
				
				if (hsl.x < 0.0)
					hsl.x += 1.0;
				else if (hsl.x > 1.0)
					hsl.x -= 1.0;
			}
			return hsl;
		}
		float HueToRGB(float f1, float f2, float hue){
			if (hue < 0.0)
				hue += 1.0;
			else if (hue > 1.0)
				hue -= 1.0;
			
			float res;
			if ((6.0 * hue) < 1.0)
				res = f1 + (f2 - f1) * 6.0 * hue;
			else if ((2.0 * hue) < 1.0)
				res = f2;
			else if ((3.0 * hue) < 2.0)
				res = f1 + (f2 - f1) * ((2.0 / 3.0) - hue) * 6.0;
			else
				res = f1;
			
			return res;
		}
		ofVec3f HSLToRGB(ofVec3f hsl){
			ofVec3f rgb;
			if (hsl.y == 0.0)
				rgb = ofVec3f(hsl.z);
			else {
				float f2;
				
				if (hsl.z < 0.5)
					f2 = hsl.z * (1.0 + hsl.y);
				else
					f2 = (hsl.z + hsl.y) - (hsl.y * hsl.z);
				
				float f1 = 2.0 * hsl.z - f2;
				rgb.x = HueToRGB(f1, f2, hsl.x + (1.0/3.0));
				rgb.y = HueToRGB(f1, f2, hsl.x);
				rgb.z= HueToRGB(f1, f2, hsl.x - (1.0/3.0));
			}
			return rgb;
		}
	private:
		ofVec3f color;
	};
	

	
}

