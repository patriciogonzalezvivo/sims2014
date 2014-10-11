/*--------------------------------------------------------------
 Ribbon mesh code adapted from:
 oF > examples > 3d > cameraRibbonExample, by James George
--------------------------------------------------------------*/
 
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    /*----------------- OF SETUP ------------------*/
	ofEnableSmoothing();
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofSetWindowShape(1280, 720);
    
    /*------------------ DRAWING ------------------*/
    isDrawing = false;
    shapeSmoothing = 1;
    // Margins: top, right, bottom, left
    margins[0] = 20;
    margins[1] = 20;
    margins[2] = 20;
    margins[3] = 240;
    setCanvas();
    thickness = 10;
    
    /*-------------------- 3D ---------------------*/
    useCamera = false;
    lightColor.set(1.0, 0.0, 0.0);
//    ofSetSmoothLighting(true);
    light.setDiffuseColor(lightColor);
//    light.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    light.setPosition(ofPoint(-ofGetWidth()*0.5, 0.0, 10.0));
    cam.setVFlip(true); // you need this, otherwise the camera starts flipped vertically
                        // I have no idea why
    zDepth = -1;
	material.setShininess( 120 );
    // the light highlight of the material //
	material.setSpecularColor(ofColor(255, 255, 255, 255));
    
    
    /*----------------- PHYSICS -------------------*/
    modifierRadius = 10;
    modifierStrength = 0.25;
    
    /*------------------- WAVE --------------------*/
    amplitude = 50.0f;
    frequencyInSeconds = 10.0f;
    nModifier = 100;
    
    /*-------------------- GUI --------------------*/
    modes.push_back("camera/draw");
    modes.push_back("modify");
    modes.push_back("wave");
    modes.push_back("spring");
    selectedMode = "camera/draw";
    setGUI();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(selectedMode == "spring"){
        for (int i = 0; i < shapes.size(); i++) {
            shapes[i].updateSpring(mouseX, mouseY, modifierRadius, modifierStrength);
        }
    
    }else if(selectedMode == "wave"){
        for (int i = 0; i < shapes.size(); i++) {
            shapes[i].updateWave(amplitude, frequencyInSeconds ,nModifier);
        }
        
    }else if(selectedMode == "modify"){
        for (int i = 0; i < shapes.size(); i++) {
            shapes[i].updateModify(mouseX, mouseY, modifierRadius, modifierStrength);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    ofNoFill();
    ofSetColor(255);
    ofSetLineWidth(1);
    ofRect(canvasPos, canvasSize.x, canvasSize.y);

    if(useCamera){
        cam.begin();
        light.enable();
        ofEnableLighting();
        ofEnableDepthTest();
        material.begin();
        ofPushMatrix();
        ofTranslate(-ofGetWidth()*0.5, -ofGetHeight()*0.5);
    }
    
    for(int i = 0; i < shapes.size(); i++){
        shapes[i].draw(useCamera, thickness, zDepth);
    }
    
    if(selectedMode == "modify" || selectedMode == "spring"){
        ofNoFill();
        ofSetLineWidth(1);
        ofSetColor(255);
        ofCircle(mouseX, mouseY, modifierRadius);
    }
    
    if(useCamera){
        ofPopMatrix();
        material.end();
        ofDisableDepthTest();
        ofDisableLighting();
        light.disable();
        cam.end();
        
        ofDrawBitmapString("Drag: rotate camera\nCTRL+drag: zoom\nALT+drag: pan"
                           , 20, ofGetHeight() - 40);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Activate camera
    if(key == 32){
        
        
    // Erase lines
    }else if(key == 'e'){
        while(shapes.size() > 0){
            int i = shapes.size() - 1;
            shapes.erase(shapes.begin() + i);
        }

    }else if(key == 'g'){
        gui->toggleVisible();        
    
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    if(selectedMode == "camera/draw"){
        // Add new ribbon, only if mouse is within the canvas AND not on 3D mode
        if(!useCamera &&
           x > margins[3] && x < ofGetWidth() - margins[1] &&
           y > margins[0] && y < ofGetHeight() - margins[2]){

            Ribbon newRibbon;
            newRibbon.setup(x, y);
            shapes.push_back(newRibbon);
            isDrawing = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    // Camera is only enabled inside the canvas area
    if(useCamera &&
       selectedMode == "camera/draw" &&
       x > margins[3] && x < ofGetWidth() - margins[1] &&
       y > margins[0] && y < ofGetHeight() - margins[2]){

       cam.enableMouseInput();

    }else{
        cam.disableMouseInput();
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(selectedMode == "camera/draw"){
        
        if(!useCamera &&
           isDrawing &&
           x > margins[3] && x < ofGetWidth() - margins[1] &&
           y > margins[0] && y < ofGetHeight() - margins[2]){
            
            shapes[shapes.size() - 1].addPoint(x, y);

        }else{
            // this stops drawing when the mouse leave the canvas area
            isDrawing = false;
            shapes[shapes.size() - 1].connectSpring();  // make a spring out of the last one!
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if(isDrawing){
        shapes[shapes.size() - 1].connectSpring();
    }
    // Whatever mode we're in (modify, camera, drawing...), releasing the mouse stops drawing
    isDrawing = false;
}

void ofApp::setCanvas(){
    canvasPos.set(margins[3], margins[0]);
    canvasSize.set(ofGetWidth() - margins[1] - margins[3], ofGetHeight() - margins[0] - margins[2]);
}

void ofApp::setGUI(){
    
    gui = new ofxUISuperCanvas("SHAPE");
    ofColor guiColor = ofColor(0, 150, 200, 100);
    gui->setColorFill(255);
    gui->setColorBack(guiColor);
    gui->addSpacer();
    
	gui->addLabel("DRAWING CONTROLS");
    gui->addSlider("SMOOTH", 1, 5, shapeSmoothing);
	gui->addButton("APPLY", false);
	gui->addButton("RESET", false);
    gui->addSpacer();
    
	gui->addLabel("3D CONTROLS");
    gui->addToggle("3D", useCamera);
    gui->addSlider("RIBBON THICKNESS", 2, 50, thickness);
    gui->addSlider("Z DEPTH", -1, -50, zDepth);
	gui->addLabel("LIGHT COLOR");
    gui->addSlider("RED", 0.0, 1.0, lightColor.r);
    gui->addSlider("GREEN", 0.0, 1.0, lightColor.g);
    gui->addSlider("BLUE", 0.0, 1.0, lightColor.b);
    gui->addSpacer();
    
	gui->addLabel("CURSOR MODES");
	gui->addRadio("CURSOR MODE", modes, OFX_UI_ORIENTATION_VERTICAL);
    gui->addSpacer();
    
	gui->addLabel("MODIFIER CONTROLS");
    gui->addSlider("MODIFIER RADIUS", 10, 200, modifierRadius);
    gui->addSlider("MODIFIER STRENGTH", 0.1, 1, modifierStrength);
    gui->addSpacer();

	gui->addLabel("WAVE CONTROLS");
    gui->addSlider("AMPLITUDE", 2, 200, amplitude);
    gui->addSlider("FREQUENCY IN SECONDS", 1, 10, frequencyInSeconds);
    gui->addSlider("N MODIFIER", 0, 200, nModifier);
    gui->addSpacer();
    
    gui->addToggle("FULLSCREEN", false);
    
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&ofApp::guiEvent);
//    gui->loadSettings("guiSettings.xml");
}

void ofApp::guiEvent(ofxUIEventArgs &e){
    
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    // DRAWING ------------------------------------------
    if(name == "SMOOTH"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        shapeSmoothing = round(slider->getScaledValue());
        
    }else if(name == "APPLY"){
        ofxUIButton *button = (ofxUIButton *) e.getButton();
        if(button->getValue()){
            for (int i = 0; i < shapes.size(); i++) {
                shapes[i].applySmoothing(shapeSmoothing);
            }
        }
        
    }else if(name == "RESET"){
        ofxUIButton *button = (ofxUIButton *) e.getButton();
        if(button->getValue()){
            for (int i = 0; i < shapes.size(); i++) {
                shapes[i].resetSmoothing();
            }
        }
        
    // 3D -----------------------------------------------
	}else if(name == "3D"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        useCamera = toggle->getValue();
        cam.reset();
        cam.enableMouseInput();
   
    }else if(name == "RIBBON THICKNESS"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        thickness = slider->getScaledValue();

    }else if(name == "Z DEPTH"){
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		zDepth = slider->getScaledValue();
        
    }else if(name == "RED"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        lightColor.r = slider->getScaledValue();
        light.setDiffuseColor(lightColor);
        
    }else if(name == "GREEN"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        lightColor.g = slider->getScaledValue();
        light.setDiffuseColor(lightColor);
        
    }else if(name == "BLUE"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        lightColor.b = slider->getScaledValue();
        light.setDiffuseColor(lightColor);
        
    // CURSOR -------------------------------------------
    }else if(name == "CURSOR MODE"){
        ofxUIRadio *radio = (ofxUIRadio *) e.widget;
        selectedMode = radio->getActiveName();

    // MODIFIER -----------------------------------------
    }else if(name == "MODIFIER RADIUS"){
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		modifierRadius = slider->getScaledValue();
        
    }else if(name == "MODIFIER STRENGTH"){
		ofxUISlider *slider = (ofxUISlider *) e.widget;
		modifierStrength = slider->getScaledValue();
        
    }else if(e.getName() == "FULLSCREEN"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ofSetFullscreen(toggle->getValue());
        setCanvas();

    // WAVE -----------------------------------------
    }else if(name == "AMPLITUDE"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        amplitude = slider->getScaledValue();
        
    }else if(name == "FREQUENCY IN SECONDS"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        frequencyInSeconds = slider->getScaledValue();
        
    }else if(e.getName() == "N MODIFIER"){
        ofxUISlider *slider = (ofxUISlider *) e.widget;
        nModifier = slider->getScaledValue();
    }
}

void ofApp::exit(){
    gui->saveSettings("guiSettings.xml");
	delete gui;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
