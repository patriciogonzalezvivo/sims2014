//
//  StopMotion.cpp
//  week1-movingRec
//
//  Created by Patricio Gonzalez Vivo on 9/15/12.
//
//

#include "StopMotion.h"

StopMotion::StopMotion(){
    folderName = "NONE";
}

void StopMotion::allocate( int _width, int _height ){
    clear();
    
    width = _width;
    height = _height;
    
    activeFrame.allocate(width, height, OF_IMAGE_COLOR);
    
    nFrame = 0;
}

int StopMotion::size(){
    return buffer.size();
}

void StopMotion::clear(){
    //  Erase the pixels array in each frame of the array to prevent memory leaks
    //  that's because they are pointers to stack memory
    //
    for(int i = 0; i < buffer.size(); i++){
        delete [] buffer[i].pixels;
    }
    
    buffer.clear();
}

void StopMotion::load(string _folder){
    //  If was something previusly loaded, save the points position
    //
    if (folderName != "NONE"){
        cout << "Saving previus information at " << folderName << endl;
        savePoints(folderName);
    }
    
    //  Clean the buffer
    //
    clear();
    
    //  Read the directory for the images
    //  We know that they are named in seq
    //
    ofDirectory dir;
    int nFiles = dir.listDir(_folder);
    if ( nFiles > 0) {
        
        folderName = _folder;
        cout << "Loading " << folderName << " folder" << endl;
        
        string xmlFile = _folder + "/points.xml";
        ofxXmlSettings XML;
        if ( XML.loadFile( xmlFile ) ){
            cout << "- "<< ofToDataPath( xmlFile ) << " found and loaded" << endl;
        } else {
            cout << "- "<< ofToDataPath( xmlFile ) << " not found" << endl;
        }
        
        int totalFramesLoaded = 0;
        for(int i=0; i<dir.numFiles(); i++) {
            
            if (dir.getFile(i).getExtension() == "jpg"){
                ofPixels pixelsHolder;
                
                //  Load the image
                //
                if ( ofLoadImage( pixelsHolder, dir.getPath(i) ) ){
                
                    //  If it's the first one remember the width and height
                    //
                    if (i == 0)
                        allocate(pixelsHolder.getWidth(), pixelsHolder.getHeight());
                    
                    //  Increment image counter
                    //
                    totalFramesLoaded++;
                    
                    //  Copy pixels to the frame
                    //
                    int totalPixels = width*height*3;
                    Frame newFrame;
                    newFrame.pixels = new unsigned char[ totalPixels ];
                    memcpy(newFrame.pixels, pixelsHolder.getPixels(), totalPixels * sizeof(unsigned char) );
                    
                    //  Store time
                    //
                    newFrame.timeStamp = ofToInt(dir.getFile(i).getFileName());
                    
                    //  Load Point
                    //
                    XML.pushTag("point",i);
                    newFrame.point.x = XML.getValue("x", width*0.5);
                    newFrame.point.y = XML.getValue("y", height*0.5);
                    XML.popTag();
                    
                    //  Add Frame to the Buffer
                    //
                    buffer.push_back( newFrame );
                }
            }
        }
        
    }
}

void StopMotion::save(string _folder){
    if ( _folder != "NONE" ){
        folderName = _folder;
    }
    
    if ( folderName != "NONE"){
        cout << "Saving " << folderName << endl;
        
        //  Check if the folder exist
        //
        ofDirectory checkFolder;
        if ( checkFolder.listDir(folderName) ){
            
            //  if exist, clean it
            //
            for(int i=0; i < checkFolder.numFiles(); i++) {
                checkFolder.getFile(i).remove();
            }
            
        } else {
            
            //  If not, create one
            //
            checkFolder.createDirectory(folderName);
            
        }
        
        //  Save each one of the frames as a JPG image
        //
        for(int i = 0; i < buffer.size(); i++){
            ofPixels pixelsHolder;
            pixelsHolder.allocate(width, height, 3);
            pixelsHolder.setFromPixels( buffer[i].pixels , width, height, OF_IMAGE_COLOR);
            ostringstream name;
            name << fixed << setfill('0') << setw(8) << buffer[i].timeStamp;
            ofSaveImage(pixelsHolder, folderName+"/" + name.str() + ".jpg");
        }
        
        //  Save the points position or make an empty one.
        //
        savePoints(folderName);
    }
}

void StopMotion::savePoints( string _folder ){
    string xmlFile = _folder + "/points.xml";
    cout << "- Atempting to saving the points info on " << xmlFile << endl;
    
    //  Load point.xml
    //
    ofxXmlSettings XML;
    if (XML.loadFile(xmlFile)){
        cout << "- File found and opened " << endl;
    } else {
        cout << "- File NOT found" << endl;
    }
    
    //  Check if there is enought space
    //
    int totalPoints = XML.getNumTags("point");
    if ( totalPoints < buffer.size() ){
        for(int i = 0; i < buffer.size() - totalPoints ; i++){
            cout << "Adding tag " << i << endl;
            XML.addTag("point");
        }
    }
    
    //  Store the points information into it
    //
    for(int i = 0; i < buffer.size(); i++){
        XML.setValue("point:x", buffer[i].point.x,i);
        XML.setValue("point:y", buffer[i].point.y,i);
    }
    
    //  Save information
    //
    XML.saveFile(xmlFile);
}

void StopMotion::addFrame( unsigned char * _pixels ){
    
    //  If is not frames means it's the first one
    //
    if (buffer.size() == 0){
        startTime = ofGetElapsedTimeMillis()*0.05;
    }
    
    //  For geting a copy of this frame we have to copy every single pixel
    //  So we start by knowing the total amount of pixels
    //
    int totalPixles = width*height*3;
    
    //  Making a new frame with the right amount of pixels on the "pixles" array
    //
    Frame newFrame;
    newFrame.pixels = new unsigned char[totalPixles];
    
    //  For copying each single pixel of the image we can use this C function
    //
    memcpy(newFrame.pixels, _pixels, totalPixles * sizeof(unsigned char) );
    //
    //  Witch is the same to say:
    //
    //    for(int i = 0; i < totalPixles ; i++){
    //        newFrame.pixels[i] = _pixels[i];
    //    }
    
    //  Put a timeStamp on it.
    //  This could be handy if we record in other speed that is not 24 per second
    //
    newFrame.timeStamp = ofGetElapsedTimeMillis()*0.05 - startTime;
    
    //  Add a default Point information at the center of the image
    //
    newFrame.point = ofPoint(width*0.5,height*0.5);
    
    //  Add the Frame into the dinamic array of Frames that we call buffer
    //
    buffer.push_back( newFrame );
}

void StopMotion::prevFrame(){
    nFrame--;
    
    if ( nFrame < 0 )
        nFrame = buffer.size()-1;
}

void StopMotion::nextFrame(){
    if ( buffer.size() != 0 ){
        nFrame = (nFrame+1)%buffer.size();
    }
}

void StopMotion::update(){
    if ( buffer.size() != 0 ){
        
        //  Update pixels
        //
        activeFrame.setFromPixels( buffer[nFrame].pixels, width, height, OF_IMAGE_COLOR );
        
        //  Dragable points
        //
        if ( ofGetMousePressed() && inside(ofGetMouseX(), ofGetMouseY()) ){
            ofPoint mouse = ofPoint(ofGetMouseX()-x, ofGetMouseY()-y);
            
            if ( buffer[nFrame].point.distance(mouse) < 50 ){
                buffer[nFrame].point = mouse;
            }
        }
        
    }
}

void StopMotion::draw(int _x, int _y, int _width, int _height){

    if ( buffer.size() != 0 ){
        x = _x;
        y = _y;
        
        int tmpWidth, tmpHeight;
        
        if ( _width == -1)
            tmpWidth = width;
        else
            tmpWidth = _width;
        
        if ( _height == -1)
            tmpHeight = height;
        else
            tmpHeight = _height;
        
        ofPushStyle();
        ofPushMatrix();
        
        ofTranslate(x, y);
        
        ofSetColor(255);
        activeFrame.draw(0, 0, tmpWidth, tmpHeight);
        
        //  Frame information
        //
        ofSetColor(0, 200);
        ofRect(0,0,150,35);
        ofSetColor(255);
        ofDrawBitmapString( "Frame: " + ofToString( nFrame ) + "/" + ofToString( buffer.size() ), 5, 15 );
        ofDrawBitmapString( "TimeStamp: " + ofToString( buffer[nFrame].timeStamp * 0.02 ) + "s", 5, 30 );
        
        //  Line
        //
        ofNoFill();
        ofSetColor(255);
        if ( buffer.size() > 0){
            ofBeginShape();
            ofVertex(buffer[0].point);
            for (int i = 0; i <= nFrame; i++){
                ofCurveVertex(buffer[i].point);
            }
            ofVertex(buffer[nFrame].point);
            ofEndShape();
        }
        
        //  Point
        //
        ofFill();
        ofSetColor(255, 10);
        ofCircle(buffer[nFrame].point, 20);
        ofSetColor(255,0,0);
        ofCircle(buffer[nFrame].point, 3);
        
        ofPopMatrix();
        ofPopStyle();
    
        //  Mouse pointer
        //
        if ( inside(ofGetMouseX(), ofGetMouseY()) ){
            ofSetColor(255, 100);
            ofLine(ofGetMouseX()-10, ofGetMouseY(), ofGetMouseX()+10, ofGetMouseY());
            ofLine(ofGetMouseX(), ofGetMouseY()-10, ofGetMouseX(), ofGetMouseY()+10);
        }
    }
}
