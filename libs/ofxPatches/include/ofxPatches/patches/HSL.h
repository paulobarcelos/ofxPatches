#pragma once
// from http://www.gamedev.net/topic/465948-hsl-shader-glsl-code/

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
	
	class HSL : public Patch {	
	public:
		HSL * create() { return new HSL(); };
		
		HSL(){
			name = "HSL";
						
			param1fDefaults[0].name = "Hue";
			param1fDefaults[0].value = 0.0;
			param1fDefaults[0].min = -1.0;
			param1fDefaults[0].max = 1.0;
			
			param1fDefaults[1].name = "Saturation";
			param1fDefaults[1].value = 0.0;
			param1fDefaults[1].min = -1.0;
			param1fDefaults[1].max = 1.0;
			
			param1fDefaults[2].name = "Luminecence";
			param1fDefaults[2].value = 0.0;
			param1fDefaults[2].min = -1.0;
			param1fDefaults[2].max = 1.0;
			
			fragmentShader = STRINGIFY(
									   uniform sampler2DRect tex0;
									   uniform float param1f0;
									   uniform float param1f1;
									   uniform float param1f2;
									   
									   float Hue_2_RGB(float v1, float v2, float vH )
									   {
										   float ret;
										   if ( vH < 0.0 )
											   vH += 1.0;
										   if ( vH > 1.0 )
											   vH -= 1.0;
										   if ( ( 6.0 * vH ) < 1.0 )
											   ret = ( v1 + ( v2 - v1 ) * 6.0 * vH );
										   else if ( ( 2.0 * vH ) < 1.0 )
											   ret = ( v2 );
										   else if ( ( 3.0 * vH ) < 2.0 )
											   ret = ( v1 + ( v2 - v1 ) * ( ( 2.0 / 3.0 ) - vH ) * 6.0 );
										   else
											   ret = v1;
										   return ret;
									   }
									   
									   void main (void)
									   {
										   vec2 st = gl_TexCoord[0].st;
										   vec4  color;
										   
										   float AddHue = param1f0;
										   float AddSat = param1f1;
										   float AddLig = param1f2;
										   
										   float Cmax;
										   float Cmin;
										   
										   float D;
										   
										   float H;
										   float S;
										   float L;
										   float R;
										   float G;
										   float B;
										   
										   // get fragment color
										   color = texture2DRect(tex0, st);
										   
										   R = color.r;
										   G = color.g;
										   B = color.b;
										   
										   // convert to HSL
										   
										   Cmax = max (R, max (G, B));
										   Cmin = min (R, min (G, B));
										   
										   // calculate lightness
										   L = (Cmax + Cmin) / 2.0;
										   
										   if (Cmax == Cmin) // it's grey
										   {
											   H = 0.0; // it's actually undefined
											   S = 0.0;
										   }
										   else
										   {
											   D = Cmax - Cmin; // we know D != 0 so we cas safely divide by it
											   
											   
											   
											   // calculate Saturation
											   if (L < 0.5)
											   {
												   S = D / (Cmax + Cmin);
											   }
											   else
											   {
												   S = D / (2.0 - (Cmax + Cmin));
											   }
											   
											   // calculate Hue
											   if (R == Cmax)
											   {
												   H = (G - B) / D;
											   } else {
												   if (G == Cmax)
												   {
													   H = 2.0 + (B - R) /D;
												   }
												   else
												   {
													   H = 4.0 + (R - G) / D;
												   }
											   }
											   
											   H = H / 6.0;
											   
											   
										   }
										   
										   // modify H/S/L values
										   H += AddHue;
										   S += AddSat;
										   L += AddLig;
										   
										   if (H < 0.0)
										   {
											   H = H + 1.0;
										   }
										   
										   // clamp H,S and L to [0..1]
										   
										   H = clamp(H, 0.0, 1.0);
										   S = clamp(S, 0.0, 1.0);
										   L = clamp(L, 0.0, 1.0);
										   
										   // convert back to RGB
										   
										   float var_2;
										   float var_1;
										   
										   if (S == 0.0)
										   {
											   R = L;
											   G = L;
											   B = L;
										   }
										   else
										   {
											   if ( L < 0.5 )
											   {
												   var_2 = L * ( 1.0 + S );
											   }
											   else
											   {
												   var_2 = ( L + S ) - ( S * L );
											   }
											   
											   var_1 = 2.0 * L - var_2;
											   
											   R = Hue_2_RGB( var_1, var_2, H + ( 1.0 / 3.0 ) );
											   G = Hue_2_RGB( var_1, var_2, H );
											   B = Hue_2_RGB( var_1, var_2, H - ( 1.0 / 3.0 ) );
										   }
										   
										   gl_FragColor = vec4(R,G,B, color.a);
										   
									   }
									   );
		}
	};
	
}