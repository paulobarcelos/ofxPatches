#include "ofxPatches/ExtendedFXObject.h"
using namespace ofxPatches;

ExtendedFXObject::ExtendedFXObject(){
	name = "undefined";
	filename = "";
	allowBypass = true;
	bypass = false;
	maxPasses = 1;
	param1fs = NULL;
	param1is = NULL;
	param1fSliders = NULL;
	param1iSliders = NULL;
	nParam1fs = 0;
	nParam1is = 0;
	useBackbuffer = false;
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
	gui.setSize(OFX_PATCHES_GUI_SIZE);
	// Reset the gui
	gui.clear();
	
	if(maxPasses < 1) maxPasses = 1;
	registerDefaultGui();
}

void ExtendedFXObject::registerDefaultGui(){
	// Add the bypass toogle
	if(allowBypass){
		ofxToggle * bypassToggle = new ofxToggle();
		bypassToggle->setup("Bypass", false, OFX_PATCHES_GUI_SIZE);
		bypassToggle->addListener(this, &ExtendedFXObject::onBypassChange);
		gui.add(bypassToggle);
	}	
	
	// Add passes slider
	if(maxPasses > 1){
		ofxIntSlider * passesSlider = new ofxIntSlider();
		passesSlider->setup("Passes", 1, 1, maxPasses, OFX_PATCHES_GUI_SIZE);
		passesSlider->addListener(this, &ExtendedFXObject::onPassesChange);
		gui.add(passesSlider);
	}
}

void ExtendedFXObject::allocate(int _width, int _height, int _internalFormat){
    internalFormat = _internalFormat;
    allocate(_width, _height);
};
void ExtendedFXObject::allocate(int _width, int _height){
	lastBuffer.allocate(_width, _height, internalFormat);
	lastBuffer.begin();
	ofClear(0,0);
	lastBuffer.end();
	ofxFXObject::allocate(_width, _height);
}

bool ExtendedFXObject::compileCode(){
	// Add the defaults variables into the shader
	/*string defaultVariables = "";
	defaultVariables += "uniform sampler2DRect backbuffer;";
	defaultVariables += "uniform float time;";
	defaultVariables += "uniform vec2 size;";
	defaultVariables += "uniform vec2 resolution;";
	defaultVariables += "uniform vec2 mouse;";
	defaultVariables += "uniform int passes;";
	defaultVariables += "uniform int pass;";
	
	fragmentShader = defaultVariables + fragmentShader;*/
	
	
    int num;
    // See how many float parameters it's need on the injected fragment shader
    num = 0;
    for (int i = 0; i < OFX_PATCHES_MAX_PARAMETERS; i++){
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
		param1fSliders[i].setup(sliderName, param1fDefaults[i].value, param1fDefaults[i].min, param1fDefaults[i].max, OFX_PATCHES_GUI_SIZE);
		param1fSliders[i].addListener(this, &ExtendedFXObject::onParam1fChange);
		gui.add(&(param1fSliders[i]));

	}
	
	// See how many int parameters it's need on the injected fragment shader
    num = 0;
    for (int i = 0; i < OFX_PATCHES_MAX_PARAMETERS; i++){
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
		param1iSliders[i].setup(sliderName, param1iDefaults[i].value, param1iDefaults[i].min, param1iDefaults[i].max, OFX_PATCHES_GUI_SIZE);
		param1iSliders[i].addListener(this, &ExtendedFXObject::onParam1iChange);
		gui.add(&(param1iSliders[i]));

	}
    
    gui.loadFromFile(filename);
	// kick the values in
	applyGuiValues();
	
	return ofxFXObject::compileCode();
}
void ExtendedFXObject::update(){
	if(bypass){
		pingPong.dst->begin();        
        ofClear(0,0);
		textures[0].draw(0, 0);
        pingPong.dst->end();        
        pingPong.swap();
	}
    else {
		for(int i = 0; i < passes; i++) {
			
			pingPong.dst->begin();        
			onRender(i);
			pingPong.dst->end();       
			pingPong.swap();
			
			if(useBackbuffer){
				// store the last render into it's own buffer
				if(i == passes -1){
					lastBuffer.begin();
					pingPong.src->draw(0, 0);
					lastBuffer.end();
				}
			}
		}
	}
    pingPong.swap();
}

void ExtendedFXObject::onRender(int pass){
	ofClear(0,0);
	shader.begin();
	
	if(useBackbuffer){
		// on the first pass, use the last rendered buffer as the backbuffer
		if(pass == 0) shader.setUniformTexture("backbuffer", lastBuffer.getTextureReference(), 0 );
		else shader.setUniformTexture("backbuffer", pingPong.src->getTextureReference(), 0 );
	}
	
	for( int j = 0; j < nParam1fs; j++){
		string paramName = "param1f" + ofToString(j); 
		shader.setUniform1f(paramName.c_str(), param1fs[j]);
	}
	
	for( int j = 0; j < nParam1is; j++){
		string paramName = "param1i" + ofToString(j); 
		shader.setUniform1i(paramName.c_str(), param1is[j]);
	}
	
	for( int j = 0; j < nTextures; j++){
		string texName = "tex" + ofToString(j); 
		shader.setUniformTexture(texName.c_str(), textures[j].getTextureReference(), j+1 );
		string texRes = "size" + ofToString(j); 
		shader.setUniform2f(texRes.c_str() , (float)textures[j].getWidth(), (float)textures[j].getHeight());
	}
	
	shader.setUniform1i("passes", passes );
	shader.setUniform1i("pass", pass );
	shader.setUniform1f("time", ofGetElapsedTimef() );
	shader.setUniform2f("size", (float)width, (float)height);
	shader.setUniform2f("resolution", (float)width, (float)height);
	shader.setUniform2f("mouse", (float)(ofGetMouseX()/width), (float)(ofGetMouseY()/height));
	
	// hook where you can put custom code into the shader pass
	onShaderPass(pass);
	
	renderFrame();        
	shader.end();   
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
void ExtendedFXObject::setPasses(int value){
	if(value < 1) value = 1;
	passes = value;
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
void ExtendedFXObject::onPassesChange(int & value){
	setPasses(value);
}

void ExtendedFXObject::setName(string name){
	this->name = name;
}

string ExtendedFXObject::getName(){
	return name;
}

void ExtendedFXObject::setFilename(string filename){
	this->filename = filename;
}

string ExtendedFXObject::getFilename(){
	return filename;
}

void ExtendedFXObject::setGUIPosition(float x, float y){
	gui.setPosition(x,y);
}
void ExtendedFXObject::drawGUI(){
	gui.draw();
}


void ExtendedFXObject::applyGuiValues(){
	onBypassChange(gui.getToggle("Bypass"));
	float f = 0.0;
	int i = 0;
	onParam1fChange(f);
	onParam1iChange(i);
}


//TODO, try to get this on ofxFX intead, can't see the point of the texture alpha being set to one!
// A simplified way of filling the insides texture
void ExtendedFXObject::setTexture(ofBaseDraws& base, int _texNum){
    if ((_texNum < nTextures) && ( _texNum >= 0)){
        textures[_texNum].begin(); 
        ofClear(0,0);
        ofSetColor(255);
        base.draw(0,0, width, height); 
        textures[_texNum].end();
    }
};

// With begin(int) and end(int) the textures allocated can be filled with data
void ExtendedFXObject::begin(int _texNum ) {
    if ((_texNum < nTextures) && ( _texNum >= 0)){
        ofPushStyle();
        ofPushMatrix();
        textures[_texNum].begin();
        ofClear(0,0);
    }
}
