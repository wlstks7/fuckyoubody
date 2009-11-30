#ifndef __LIB_DC1394_GRABBER_H
#define __LIB_DC1394_GRABBER_H


#include "ofConstants.h"
#include "ofAppRunner.h"
#include "ofxThread.h"

#include <dc1394/dc1394.h>

#include "Libdc1394GrabberFeatureHelper.h"
#include "ofxVideoGrabberFeature.h"
#include "ofxVideoGrabberSDK.h"


class Libdc1394Grabber : public ofxVideoGrabberSDK, public ofxThread
{
	public:


		Libdc1394Grabber();
		virtual ~Libdc1394Grabber();

		void setDeviceID(int _deviceID);
		void setDeviceGUID(uint64_t _deviceGUID);
		uint64_t getDeviceGUID();
		void listDevices();
		bool init( int _width = 320, int _height = 240, int _format = VID_FORMAT_GREYSCALE, int _targetFormat = VID_FORMAT_BGR , int _frameRate = 30);
		bool initCam( dc1394video_mode_t _videoMode, dc1394framerate_t _frameRateMode, int _width, int _height);
		void close();
		void threadedFunction();
		void captureFrame();
		unsigned char* getPixels();
		bool haveNewFrame();
		bool grabFrame(unsigned char ** _pixels);
		void processCameraImageData( unsigned char* _cameraImageData );


		/* Features */
		void initFeatures();
		void setFeaturesOnePushMode();

		void getAllFeatureValues();
		void getFeatureValues( ofxVideoGrabberFeature* _feature );

		void setFeatureMode( int _val, int _feature );
		bool setFeatureOnOff( bool _val, int _feature);
		void setFeatureAbsoluteValue( float _val, int _feature );
		void setFeatureValue( float _val, int _feature );
        void setFeatureValue( float _val1, float _val2, int _feature );

		int stringToFeature( string _featureName );

        /* Frame pixels */
		int finalImageDataBufferLength;

		unsigned int tmpCount;

		int outputImageWidth;
		int outputImageHeight;

		dc1394color_coding_t sourceFormatLibDC;

		bool grabbedFirstImage;

		bool conversionNeeded;

		dc1394color_filter_t bayerPattern;
		dc1394bayer_method_t bayerMethod;

		dc1394camera_list_t*  list;
	unsigned long int blinkCounter;

	private:

		void setBayerPatternIfNeeded();
		bool bChooseDevice;
		int cameraIndex;
		uint64_t cameraGUID;
        static dc1394_t* d;
		static int useCount; 
		dc1394error_t err;

		dc1394camera_t* camera;
		dc1394video_frame_t* frame;

		dc1394framerate_t framerate;
		dc1394video_mode_t video_mode;

		dc1394featureset_t features;
		dc1394framerates_t framerates;
		dc1394video_modes_t video_modes;

		//dc1394color_filter_t
		dc1394color_coding_t coding;

		dc1394speed_t ISO_SPEED;
	
		dc1394operation_mode_t OPERATION_MODE;

		int YUV_BYTE_ORDER;
	
		uint64_t packet_size;
	
		void initInternalBuffers();
		void cleanupCamera();


};


#endif

