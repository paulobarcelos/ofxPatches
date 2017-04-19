#pragma once

#ifndef OFX_PATCHES_MAX_PARAMETERS
	#define OFX_PATCHES_MAX_PARAMETERS 20
#endif


#ifndef OFX_PATCHES_PATCH_CONNECTOR_SIZE
	#define OFX_PATCHES_PATCH_CONNECTOR_SIZE 10
#endif


#ifndef OFX_PATCHES_GUI_SIZE
	#define OFX_PATCHES_GUI_SIZE 200,12
#endif


#ifndef OFX_PATCHES_SETTINGS_FOLDER
	#define OFX_PATCHES_SETTINGS_FOLDER "ofxPatches/"
#endif

#define OFX_PATCHES_REGISTER_ALL_EFFECTS(m) \
m.registerPatch<ofxPatches::Noise>();\
m.registerPatch<ofxPatches::Delay>();\
m.registerPatch<ofxPatches::Accumulator>();\
m.registerPatch<ofxPatches::OpticalFlow>();\
m.registerPatch<ofxPatches::ChannelBalancer>();\
m.registerPatch<ofxPatches::Invert>();\
m.registerPatch<ofxPatches::CustomBW>();\
m.registerPatch<ofxPatches::HSL>();\
m.registerPatch<ofxPatches::RGBtoHSL>();\
m.registerPatch<ofxPatches::BrightnessContrast>();\
m.registerPatch<ofxPatches::LinearLevels>();\
m.registerPatch<ofxPatches::Gamma>();\
m.registerPatch<ofxPatches::Threshold>();\
m.registerPatch<ofxPatches::BandThreshold>();\
m.registerPatch<ofxPatches::BandFilter>();\
m.registerPatch<ofxPatches::BandPass>();\
m.registerPatch<ofxPatches::DifferenceAbsolute>();\
m.registerPatch<ofxPatches::DifferenceDarken>();\
m.registerPatch<ofxPatches::DifferenceLigthen>();\
m.registerPatch<ofxPatches::BitwiseAND>();\
m.registerPatch<ofxPatches::BitwiseOR>();\
m.registerPatch<ofxPatches::BitwiseXOR>();\
m.registerPatch<ofxPatches::BlurGaussian>();\
m.registerPatch<ofxPatches::BlurMedian>();\
m.registerPatch<ofxPatches::Sharpen>();\
m.registerPatch<ofxPatches::Erode>();\
m.registerPatch<ofxPatches::Dilate>();\
m.registerPatch<ofxPatches::EdgeLaplacian>();\
m.registerPatch<ofxPatches::EdgePrewitt>();\
m.registerPatch<ofxPatches::EdgeSobel>();\
m.registerPatch<ofxPatches::HayasakaBlend>();\
m.registerPatch<ofxPatches::ColorBlock>();\
m.registerPatch<ofxPatches::Paintbrush>();\
m.registerPatch<ofxPatches::AlphaMask>();\
m.registerPatch<ofxPatches::ChannelMask>();\
m.registerPatch<ofxPatches::ChannelCombiner>();\
m.registerPatch<ofxPatches::TextureTiler>();\
m.registerPatch<ofxPatches::Crop>();\
m.registerPatch<ofxPatches::PerspectiveWarp>();\
m.registerPatch<ofxPatches::SphericalDistortion>();
