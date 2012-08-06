#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class TextureTiler : public Patch {	
	public:
		TextureTiler * create() { return new TextureTiler(); };
		
		TextureTiler(){
			name = "Texture Tiler";
			
			maxPasses = 1;
			
			param1iDefaults[0].name = "Used Textures";
			param1iDefaults[0].value = 2;
			param1iDefaults[0].min = 2;
			param1iDefaults[0].max = 6;
			
			param1iDefaults[1].name = "Columns";
			param1iDefaults[1].value = 2;
			param1iDefaults[1].min = 1;
			param1iDefaults[1].max = 6;
			
			param1iDefaults[2].name = "Rows";
			param1iDefaults[2].value = 1;
			param1iDefaults[2].min = 1;
			param1iDefaults[2].max = 6;
			
			param1fDefaults[0].name = "Horiz. Overlap";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = 0.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "Vert. Overlap";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = 0.0;
			param1fDefaults[1].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform sampler2DRect tex1;
									   uniform sampler2DRect tex2;
									   uniform sampler2DRect tex3;
									   uniform sampler2DRect tex4;
									   uniform sampler2DRect tex5;
									   
									   uniform int param1i0; // num used textutres
									   uniform int param1i1; // rows
									   uniform int param1i2; // cols
									   
									   uniform float param1f0; // horizontal overlap
									   uniform float param1f1; // vertical overlap
									   
									   );
		}
		
		void onRender(int pass){
			ofClear(255, 255, 255, 0);
			
			int col = 0;
			int row = 0;
			
			float w = width / (float)param1is[1];
			float h = height / (float)param1is[2];
			
			float wHalf = w / 2.;
			float hHalf = h / 2.;
			
			float wOverlap = param1fs[0] * w;
			float hOverlap = param1fs[1] * h;
			
			float wFinal = w + wOverlap;
			float hFinal = h + hOverlap;
			
			float wFinalHalf = wFinal / 2.;
			float hFinalHalf = hFinal / 2.;
			
	
			for (int i = 0; i < param1is[0]; i++) {
				textures[i].draw(col * w + wHalf - wFinalHalf,
								 row * h + hHalf - hFinalHalf,
								 wFinal,
								 hFinal);				
				col++;
				if(col == param1is[1]){
					col = 0;
					row ++;
				}
			}

		}
	};
	
}