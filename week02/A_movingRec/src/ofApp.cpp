#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(24);
    ofSetVerticalSync(true);
    ofSetCircleResolution(80);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    ofSetWindowShape(990, 535);
    
    width = 640;
    height = 480;
    
    videoIn.initGrabber(width , height);

    sMotion.allocate(width, height);

    bPlay = true;
    bConvert = false;
    bRecording = false;
    movieCounter = 0;
    
    //  Load data folder
    //
    dataDir.listDir(".");
    
    selectedDir = -1;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
    if ( bConvert ){
        
        //  If it have to convert a movie into stopMotion
        //
        movieIn.update();
        
        if ( movieIn.getIsMovieDone() ){
            sMotion.save( "convertedMovie" );
            movieIn.stop();
            bConvert = false;
        } else {
            if (movieIn.isFrameNew()){
                sMotion.addFrame( movieIn.getPixels() );
            }
        }
        
    } else {
        
        //  Grab info from the video camera
        //
        videoIn.update();
        if (videoIn.isFrameNew()){
            if (bRecording){
                sMotion.addFrame( videoIn.getPixels() );
            }
        }
    }
    
    //  Play StopMotion
    //
    if (bPlay){
        sMotion.nextFrame();
    }
    sMotion.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    ofBackgroundGradient(ofColor(0), ofColor(50), OF_GRADIENT_LINEAR);
    
    //  Header
    //
    ofSetColor(255);
    ofDrawBitmapString("Press 'r' to start recording or drop a MOVIE file on to the app to convert.", 10, 15);
    ofDrawBitmapString("Press 'SPACEBAR' to start and stop. RIGHT and LEFT keys makes it Next and Prev frame. Move the point and save with 's'", 10, 30);
    
    ofPushMatrix();
    ofTranslate(10, 45);
    
    //  Draw StopMotion
    //
    ofSetColor(255);
    videoIn.draw(0, 0, width * 0.5, height * 0.5);
    if (bRecording){
        ofSetColor(255, 0, 0, abs ( sin( ofGetElapsedTimeMillis() * 0.001 ) ) * 255 );
        ofCircle(25, 25, 7);
        ofDrawBitmapString("REC", 35,30);
    }
    
    //  Draw Dir List
    //
    stringstream dirList;
    dirList << "Data: ( UP / DOWN keys ) " << endl;
    dirList << endl;
    for(int i = 0; i < dataDir.numFiles(); i++){
        dirList << dataDir.getFile(i).getFileName();
        if ( selectedDir != -1 ){
            if ( i == selectedDir ){
                dirList << " <--";
            }
        }
        dirList << endl;
    }
    ofSetColor(255);
    ofDrawBitmapString(dirList.str(), 10, height*0.5 + 25 );
    
    ofPopMatrix();
    
    //  Draw StopMotion
    //
    sMotion.draw(width*0.5 + 10 + 10, 45);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if( key == ' '){
        bPlay = !bPlay;
    }
    
    if ( key == OF_KEY_RIGHT){
        sMotion.nextFrame();
    }
    
    if ( key == OF_KEY_LEFT){
        sMotion.prevFrame();
    }
    
    if (key == 'r'){
        bRecording = !bRecording;
        if (!bRecording){
            sMotion.save( "movie" + ofToString(movieCounter++) );
            dataDir.listDir(".");
        } else {
            sMotion.clear();
        }
    }
    
    if (key == 's'){
        sMotion.save();
    }
    
    if ( key == OF_KEY_DOWN){
        selectedDir = (selectedDir+1)%dataDir.numFiles();
        
        if ( dataDir.getFile(selectedDir).isDirectory() ) {
            sMotion.load( dataDir.getFile(selectedDir).getFileName() );
        }
            
    } else if ( key == OF_KEY_UP){
        
        if (selectedDir > 0 ) {
            selectedDir--;
        }
        
        if ( dataDir.getFile(selectedDir).isDirectory() ) {
            sMotion.load( dataDir.getFile(selectedDir).getFileName() );
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    if (movieIn.loadMovie( dragInfo.files[0] )){
        
        sMotion.allocate(movieIn.getWidth(), movieIn.getHeight());
        movieIn.setLoopState(OF_LOOP_NONE);
        movieIn.play();
        
        bConvert = true;
    }
}