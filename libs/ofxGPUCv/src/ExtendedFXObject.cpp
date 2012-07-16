#include "ofxGPUCv/ExtendedFXObject.h"
using namespace ofxGPUCv;

ExtendedFXObject::ExtendedFXObject(){
	name = "undefined";
	filename = "";
	bypass = false;
	param1fs = NULL;
	param1is = NULL;
	param1fSliders = NULL;
	param1iSliders = NULL;
}

ExtendedFXObject::~ExtendedFXObject(){
	if (param1fs != NULL ){
		delete [] param1fs;
	}
	if (param1is != NULL ){
		delete [] param1is;
	}
	if (param1fSliders != NULL ){
		delete [] param1fSliders;
	}
	if (param1iSliders != NULL ){
		delete [] param1iSliders;
	}
}

void ExtendedFXObject::setup(string name, string filename){
	if(name.compare("")){
		this->name = name;
	}
	if(filename.compare("")){
		this->filename = filename;
	}
	if(!this->filename.compare("")){
		this->filename = this->name + ".xml";
	}
	gui.setup(this->name, this->filename);
	// Reset the gui
	gui.clear();
	
	// Add the bypass toogle	
	ofxToggle * bypassToggle = new ofxToggle("Bypass", false);
	bypassToggle->addListener(this, &ExtendedFXObject::onBypassChange);
	gui.add(bypassToggle);
}
 
bool ExtendedFXObject::compileCode(){
	

	
	

	
    int num;
    // See how many float parameters it's need on the injected fragment shader
    num = 0;
    for (int i = 0; i < OFX_GPU_CV_MAX_PARAMETERS; i++){
        string searchFor = "param1f" + ofToString(i);
        if ( fragmentShader.find(searchFor)!= -1)
            num++;
        else 
            break;
    }
    
	// Reset the float parameters
	if (param1fs != NULL ){
		delete [] param1fs;
	}
	// And initialate the right amount of parameters
	nParam1fs = num;
	if (nParam1fs > 0){
		param1fs = new float[nParam1fs];
	} else if ( nParam1fs == 0 ){
		param1fs = NULL;
	}
	

	if (nParam1fs > 0){
		param1fSliders = new ofxFloatSlider[nParam1fs];
	} else if ( nParam1fs == 0 ){
		param1fSliders = NULL;
	}

	
	for (int i = 0; i < nParam1fs; i++) {
		param1fs[i] = param1fDefaults[i].value;
		

		string sliderName;
		if(!param1fDefaults[i].name.compare("undefined")){ // Slider was not defined
			sliderName = "param1f" + ofToString(i);
		}
		else{
			sliderName = param1fDefaults[i].name;
			
		}
		param1fSliders[i].setup(sliderName, param1fDefaults[i].value, param1fDefaults[i].min, param1fDefaults[i].max);
		param1fSliders[i].addListener(this, &ExtendedFXObject::onParam1fChange);
		gui.add(&(param1fSliders[i]));

	}
	
	// See how many int parameters it's need on the injected fragment shader
    num = 0;
    for (int i = 0; i < OFX_GPU_CV_MAX_PARAMETERS; i++){
        string searchFor = "param1i" + ofToString(i);
        if ( fragmentShader.find(searchFor)!= -1)
            num++;
        else 
            break;
    }
    
    // Reset the int parameters
	if (param1is != NULL ){
		delete [] param1is;
	}
	// And initialate the right amount of parameters
	nParam1is = num;
	if (nParam1is > 0){
		param1is = new int[nParam1is];
	} else if ( nParam1is == 0 ){
		param1is = NULL;
	}
	

	if (nParam1is > 0){
		param1iSliders = new ofxIntSlider[nParam1is];
	} else if ( nParam1is == 0 ){
		param1iSliders = NULL;
	}

	
	for (int i = 0; i < nParam1is; i++) {
		param1is[i] = param1iDefaults[i].value;
		

		string sliderName;
		if(!param1iDefaults[i].name.compare("undefined")){ // Slider was not defined
			sliderName = "param1i" + ofToString(i);
		}
		else{
			sliderName = param1iDefaults[i].name;
		}
		param1iSliders[i].setup(sliderName, param1iDefaults[i].value, param1iDefaults[i].min, param1iDefaults[i].max);
		param1iSliders[i].addListener(this, &ExtendedFXObject::onParam1iChange);
		gui.add(&(param1iSliders[i]));

	}
    
    gui.loadFromFile(filename);
	// kick the values in
	float f = 0.0;
	int i = 0;	
	onParam1fChange(f);
	onParam1iChange(i);
	onBypassChange(gui.getToggle("Bypass"));

	
	return ofxFXObject::compileCode();
}
void ExtendedFXObject::update(){
	if(bypass){
		pingPong.dst->begin();        
        ofClear(0);
		textures[0].draw(0, 0);  
        pingPong.dst->end();        
        pingPong.swap();
	}
    else {
		// All the following update process has been copied from the ofxFXObject original update,
		// the only new things are the injected float and in parameters
		for(int i = 0; i < passes; i++) {
			
			pingPong.dst->begin();        
			ofClear(0);
			shader.begin();
			shader.setUniformTexture("backbuffer", pingPong.src->getTextureReference(), 0 );
			
			for( int i = 0; i < nParam1fs; i++){
				string paramName = "param1f" + ofToString(i); 
				shader.setUniform1f(paramName.c_str(), param1fs[i]);
			}
			
			for( int i = 0; i < nParam1is; i++){
				string paramName = "param1i" + ofToString(i); 
				shader.setUniform1i(paramName.c_str(), param1is[i]);
			}
			
			for( int i = 0; i < nTextures; i++){
				string texName = "tex" + ofToString(i); 
				shader.setUniformTexture(texName.c_str(), textures[i].getTextureReference(), i+1 );
				string texRes = "size" + ofToString(i); 
				shader.setUniform2f(texRes.c_str() , (float)textures[i].getWidth(), (float)textures[i].getHeight());
			}
			
			shader.setUniform1f("time", ofGetElapsedTimef() );
			shader.setUniform2f("size", (float)width, (float)height);
			shader.setUniform2f("resolution", (float)width, (float)height);
			shader.setUniform2f("mouse", (float)(ofGetMouseX()/width), (float)(ofGetMouseY()/height));
			
			renderFrame();        
			shader.end();        
			pingPong.dst->end();        
			pingPong.swap();
		}
	}
    pingPong.swap();
}

void ExtendedFXObject::setParam1f(float param, int _paramNum){ 
    if ((_paramNum < nParam1fs) && ( _paramNum >= 0)){
        param1fs[_paramNum] = param;
    }
}
void ExtendedFXObject::setParam1i(int param, int _paramNum){ 
    if ((_paramNum < nParam1is) && ( _paramNum >= 0)){
        param1is[_paramNum] = param;
    }
}
void ExtendedFXObject::setBypass(bool value){
	bypass = value;
}

string ExtendedFXObject::getName(){
	return name;
}


void ExtendedFXObject::setGUIPosition(float x, float y){
	gui.setPosition(x,y);
}
void ExtendedFXObject::drawGUI(){
	gui.draw();
	
	draw(gui.getShape().x, gui.getShape().y + gui.getShape().height, gui.getShape().width, gui.getShape().width * height/width); 
}
void ExtendedFXObject::onParam1fChange(float & value){
	for (int i = 0; i < nParam1fs; i++) {
		setParam1f(param1fSliders[i], i);
	}
}
void ExtendedFXObject::onParam1iChange(int & value){
	for (int i = 0; i < nParam1is; i++) {
		setParam1i(param1iSliders[i], i);
	}
}
void ExtendedFXObject::onBypassChange(bool & value){
	setBypass(value);
}
