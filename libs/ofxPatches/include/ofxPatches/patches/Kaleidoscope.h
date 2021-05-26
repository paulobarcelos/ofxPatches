#pragma once

#define STRINGIFY(A) #A

#include "ofMain.h"
#include "ofxPatches/Patch.h"


namespace ofxPatches {
    
    class Kaleidoscope : public Patch {
    public:
        Kaleidoscope * create() { return new Kaleidoscope(); };
        
        Kaleidoscope(){
            name = "Kaleidoscope";
            
            param1fDefaults[0].name = "zoom";
            param1fDefaults[0].value = 1.0;
            param1fDefaults[0].min = 0.0;
            param1fDefaults[0].max = 4.0;
            
            
            fragmentShader = STRINGIFY(
                                       uniform sampler2DRect tex0;

                                       uniform float param1f0; //zoom
                                       uniform float time;
                                       uniform vec2 resolution;
                                       void main(void){
                                           vec2 uv = gl_TexCoord[0].st / resolution;
                                           uv = abs(mix(vec2(-1.0), vec2(1.0), uv));
                                           uv *= param1f0;
                                           uv = mod(uv, vec2(1.0));
                                           uv *= resolution;
                
                                           gl_FragColor = texture2DRect(tex0, uv);
                                       }
                                       );
        }
      };
      
    
    
}
