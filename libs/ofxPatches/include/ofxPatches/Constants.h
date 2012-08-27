#pragma once

#define OFX_GPU_CV_MAX_PARAMETERS 20
#define OFX_GPU_CV_PATCH_CONNECTOR_SIZE 10

#define OFX_GPU_CV_GUI_SIZE 200,14

#define OFX_GPU_CV_SETTINGS_FOLDER "ofxPatches/"

#define OFX_GPU_CV_REGISTER_ALL_EFFECTS(m) \
m.registerPatch<ofxPatches::Accumulator>();\
m.registerPatch<ofxPatches::OpticalFlow>();\
m.registerPatch<ofxPatches::ChannelBalancer>();\
m.registerPatch<ofxPatches::Invert>();\
m.registerPatch<ofxPatches::CustomBW>();\
m.registerPatch<ofxPatches::HSL>();\
m.registerPatch<ofxPatches::BrightnessContrast>();\
m.registerPatch<ofxPatches::Threshold>();\
m.registerPatch<ofxPatches::BandThreshold>();\
m.registerPatch<ofxPatches::DifferenceAbsolute>();\
m.registerPatch<ofxPatches::DifferenceDarken>();\
m.registerPatch<ofxPatches::DifferenceLigthen>();\
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
m.registerPatch<ofxPatches::TextureTiler>();\
m.registerPatch<ofxPatches::Crop>();\
m.registerPatch<ofxPatches::PerspectiveWarp>();\
m.registerPatch<ofxPatches::SphericalDistortion>();