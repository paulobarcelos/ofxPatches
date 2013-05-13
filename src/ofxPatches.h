#pragma once

#include "ofxPatches/Constants.h"

#include "ofxPatches/Patch.h"
#include "ofxPatches/Manager.h"

#include "ofxPatches/patches/FixedSource.h"

#include "ofxPatches/patches/Accumulator.h"
#include "ofxPatches/patches/OpticalFlow.h"

#include "ofxPatches/patches/ChannelBalancer.h"
#include "ofxPatches/patches/Invert.h"
#include "ofxPatches/patches/CustomBW.h"
#include "ofxPatches/patches/BrightnessContrast.h"
#include "ofxPatches/patches/Gamma.h"
#include "ofxPatches/patches/HSL.h"
#include "ofxPatches/patches/RGBtoHSL.h"

#include "ofxPatches/patches/BandThreshold.h"
#include "ofxPatches/patches/Threshold.h"
#include "ofxPatches/patches/BandFilter.h"
#include "ofxPatches/patches/BandPass.h"

#include "ofxPatches/patches/DifferenceAbsolute.h"
#include "ofxPatches/patches/DifferenceDarken.h"
#include "ofxPatches/patches/DifferenceLigthen.h"

#include "ofxPatches/patches/BitwiseAND.h"
#include "ofxPatches/patches/BitwiseOR.h"
#include "ofxPatches/patches/BitwiseXOR.h"

#include "ofxPatches/patches/ChannelCombiner.h"
#include "ofxPatches/patches/ChannelMask.h"
#include "ofxPatches/patches/AlphaMask.h"
#include "ofxPatches/patches/HayasakaBlend.h"
#include "ofxPatches/patches/TextureTiler.h"

#include "ofxPatches/patches/BlurGaussian.h"
#include "ofxPatches/patches/BlurMedian.h"
#include "ofxPatches/patches/Sharpen.h"

#include "ofxPatches/patches/Erode.h"
#include "ofxPatches/patches/Dilate.h"

#include "ofxPatches/patches/EdgeLaplacian.h"
#include "ofxPatches/patches/EdgePrewitt.h"
#include "ofxPatches/patches/EdgeSobel.h"

#include "ofxPatches/patches/ColorBlock.h"
#include "ofxPatches/patches/Paintbrush.h"

#include "ofxPatches/patches/Crop.h"
#include "ofxPatches/patches/PerspectiveWarp.h"
#include "ofxPatches/patches/SphericalDistortion.h"