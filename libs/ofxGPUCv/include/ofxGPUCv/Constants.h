#pragma once

#define OFX_GPU_CV_MAX_PARAMETERS 20
#define OFX_GPU_CV_PATCH_CONNECTOR_SIZE 10

#define OFX_GPU_CV_GUI_SIZE 170,14

#define OFX_GPU_CV_SETTINGS_FOLDER "ofxGPUCv/"

#define OFX_GPU_CV_REGISTER_ALL_EFFECTS(m) \
m.registerPatch<ofxGPUCv::Accumulator>();\
m.registerPatch<ofxGPUCv::ChannelBalancer>();\
m.registerPatch<ofxGPUCv::Invert>();\
m.registerPatch<ofxGPUCv::CustomBW>();\
m.registerPatch<ofxGPUCv::Threshold>();\
m.registerPatch<ofxGPUCv::BandThreshold>();\
m.registerPatch<ofxGPUCv::DifferenceAbsolute>();\
m.registerPatch<ofxGPUCv::DifferenceDarken>();\
m.registerPatch<ofxGPUCv::DifferenceLigthen>();\
m.registerPatch<ofxGPUCv::BlurGaussian>();\
m.registerPatch<ofxGPUCv::BlurMedian>();\
m.registerPatch<ofxGPUCv::Sharpen>();\
m.registerPatch<ofxGPUCv::Erode>();\
m.registerPatch<ofxGPUCv::Dilate>();\
m.registerPatch<ofxGPUCv::EdgeLaplacian>();\
m.registerPatch<ofxGPUCv::EdgePrewitt>();\
m.registerPatch<ofxGPUCv::EdgeSobel>();\
m.registerPatch<ofxGPUCv::HayasakaBlend>();\
m.registerPatch<ofxGPUCv::ColorBlock>();