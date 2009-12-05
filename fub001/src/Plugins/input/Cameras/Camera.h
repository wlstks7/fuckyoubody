#pragma once

#import "GLee.h"

#import <Cocoa/Cocoa.h>

#include "Plugin.h"
#include "ofMain.h"
#include "Libdc1394Grabber.h"
#include "videoplayerWrapper.h"

@interface Camera : NSObject {
	Libdc1394Grabber * videoGrabber;
	BOOL live;

	videoplayerWrapper * videoPlayer;
	NSMutableArray * movies;
	BOOL loadMoviePlease;
	NSString * loadMovieString;
	float millisSinceLastMovieEvent;
	
	ofTexture * tex;
	unsigned char* pixels;
	
	int width, height;
	BOOL camInited ;
	BOOL bIsFrameNew;
	
	IBOutlet NSView * settingsView;
	
	IBOutlet NSTextField * guidTextField;
	IBOutlet PluginUISlider * shutterSlider;
	IBOutlet PluginUISlider * exposureSlider;
	IBOutlet PluginUISlider * gainSlider;
	IBOutlet PluginUISlider * gammaSlider;
	IBOutlet PluginUISlider * brightnessSlider;
	
	IBOutlet NSSegmentedControl * sourceSelector;
	IBOutlet NSPopUpButton * movieSelector;
	IBOutlet NSButton * recordButton;
	
	float mytimeNow, mytimeThen;
	int myframes;
	float myfps,frameRate;
	pthread_mutex_t mutex;

}

@property (assign, readonly) NSView * settingsView;
@property (assign, readonly) float mytimeNow;
@property (assign, readonly) float mytimeThen;
@property (assign, readonly) int width;
@property (assign, readonly) int height;
@property (assign, readonly) BOOL camInited;


-(ofTexture*) getTexture;
-(float) framerate;
-(void) setup:(int)camNumber;
-(void) update;
-(BOOL) loadNibFile;
-(void) aWillTerminate:(NSNotification *)notification;
-(unsigned char*) getPixels;

-(void) updateMovieList;
-(void) loadMovie:(NSString*) name;

-(ofTexture*) fetchVideo;

-(IBAction) setShutter:(id)sender;
-(IBAction) setExposure:(id)sender;
-(IBAction) setGain:(id)sender;
-(IBAction) setGamma:(id)sender;
-(IBAction) setBrightness:(id)sender;
-(IBAction) setSource:(id)sender;
-(IBAction) setMovieFile:(id)sender;
-(IBAction) toggleRecord:(id)sender;

@end