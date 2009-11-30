#ifndef __A_VIDEO_GRABBER_H
#define __A_VIDEO_GRABBER_H

#include "ofTypes.h"
#include "ofTexture.h"

#include "ofxVideoGrabberFeature.h"
#include "ofxVideoGrabberSettings.h"
#include "ofxVideoGrabberSDK.h"
#include "ofxNOSettings.h"
/* SDKs */
#include "Libdc1394Grabber.h"


class ofxVideoGrabber: public ofBaseVideo
{
	public:

		ofxVideoGrabber();
		virtual ~ofxVideoGrabber();

		bool initGrabber( int _width = 320,
				  int _height = 240,
				  int _format = VID_FORMAT_RGB,
				  int _targetFormat = VID_FORMAT_RGB,
				  int _frameRate = 15,
				  bool _useTexture = true,
				  ofxVideoGrabberSDK* sdk = new Libdc1394Grabber,
				  ofxVideoGrabberSettings* settings = new ofxNOSettings);

		void 			listDevices(); 
		bool            isFrameNew();
		void            grabFrame();
		bool			grabberInited();
		bool			isReady();
        void            close();
		void			videoSettings() {settings->toggleSettingsGUI();};
		unsigned char*  getPixels();
		ofTexture &     getTextureReference();
		//void 			setVerbose(bool bTalkToMe); TODO
		//void			setDeviceID(int _deviceID); TODO
		void            setUseTexture(bool bUse);
		void            draw(float x, float y);
		void            draw(float x, float y, float w, float h);
        void            update();
		float 		    getHeight();
		float 		    getWidth();


        ofxVideoGrabberSDK *        videoGrabber;
        ofxVideoGrabberSettings *   settings;

	float frameRate;
	float fps;
	bool bIsFrameNew;

	protected:

        bool bGrabberInited;
        bool bUseTexture;
        ofTexture tex;
        int width;
        int height;
        unsigned int bpp;
        unsigned char* pixels;
        int targetFormat;
	
	float timeNow;
	float timeThen;

};


#endif
