//
//  ofxKinectV2.h
//  kinectExample
//
//  Created by Theodore Watson on 6/23/14.
//
//

#pragma once

#include "ofProtonect.h"
#include "ofMain.h"

class ofxKinectV2 : public ofThread{

    public:
    
        struct KinectDeviceInfo{
            string serial;
            int deviceId;   //if you have the same devices plugged in device 0 will always be the same Kinect
            int freenectId; //don't use this one - this is the index given by freenect2 - but this can change based on order device is plugged in
        };

        ofxKinectV2();
        ~ofxKinectV2(); 
        
        //for some reason these can't be static - so you need to make a tmp object to query them
        vector <KinectDeviceInfo> getDeviceList();
        unsigned int getNumDevices();
    
        bool open(string serial);
        bool open(unsigned int deviceId = 0);
        void update();
        void close();
    
        bool isFrameNew();
    
        ofPixels& getDepthPixels();
        ofPixels& getRgbPixels();
        ofFloatPixels& getRawDepthPixels();
        ofFloatPixels& getIrPixels() { return irPixels; }
        ofPixels& getIrImagePixels();
        ofPixels& getRegisteredPixels() { return registeredPix; }

        ofParameterGroup params;
        ofParameter <float> minDistance;
        ofParameter <float> maxDistance;
        
        // TODO: remove this!
        ofVec3f mapDepthPointToWorldPoint(ofVec2f p) {
            return protonect.getWorldCoord(p);
        }

        ofVec3f imageToWorld(ofVec2f p) {
            lock();
            ofVec3f o = protonect.getWorldCoord(p);
            unlock();
            return o;
        }

    protected:
        void threadedFunction();

        ofPixels rgbPix;
        ofPixels depthPix;
        ofFloatPixels rawDepthPixels;
        ofPixels registeredPix;
        ofFloatPixels irPixels;
        ofPixels irImagePixels;
        
        bool bNewBuffer;
        bool bNewFrame;
        bool bOpened;
    
        ofProtonect protonect; 
    
        ofPixels rgbPixelsBack, rgbPixelsFront;
        ofPixels registeredPixelsBack, registeredPixelsFront;
        ofFloatPixels depthPixelsBack, depthPixelsFront;
        ofFloatPixels irPixelsBack, irPixelsFront;
        int lastFrameNo;

        bool depthPixDirty, irImagePixelsDirty;
};