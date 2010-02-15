#pragma once

#import "GLee.h"

#import <Cocoa/Cocoa.h>
#include "Plugin.h"
#include "ofMain.h"
#include "ofxVectorMath.h"
#include "Filter.h"



@interface HardwareBox : ofPlugin {
	NSThread * thread;
	pthread_mutex_t mutex;
	
	bool inCommandProcess;
	int commandInProcess;
	
	ofSerial * serial;
	
	bool connected, ok;
	int timeout;
	
	int	arduinoState, projector1state, projector2state, xbeestate;
	float xbeeRSSI;
	
	bool xbeeLedOn;
	bool laserOn;
	
	float projTemps[6];
	
	int timeSinceLastProjUpdate;
	
	int startDmxChannel;
	int stopDmxChannel;
	int dmxValues[256];
	
	vector<unsigned char> * serialBuffer;
	
	IBOutlet NSTextField * usbStatus;
	IBOutlet NSTextField * arduinoStatus;
	
	IBOutlet NSTextField * buffersizeStatus;
	IBOutlet NSTextField * projector1Status;
	IBOutlet NSTextField * projector2Status;
	IBOutlet NSTextField * projector1Temperature;
	IBOutlet NSTextField * projector2Temperature;
	IBOutlet NSTextField * xbeeStatus;
	IBOutlet NSLevelIndicator * xbeeSignalStrength;
	IBOutlet NSTextField * xbeeLEDStatus;
	IBOutlet NSTextField * laserStatus;
	
	IBOutlet NSButton * laserButton;
	IBOutlet NSButton * ledButton;
	
	
	
	Filter * trackingFilter[8];
	ofxPoint2f * trackingDestinations[4];
	
	IBOutlet NSSlider * offsetSliderX1;
	IBOutlet NSSlider * offsetSliderX2;
	IBOutlet NSSlider * offsetSliderX3;
	IBOutlet NSSlider * offsetSliderX4;
	
	IBOutlet NSSlider * offsetSliderY1;
	IBOutlet NSSlider * offsetSliderY2;
	IBOutlet NSSlider * offsetSliderY3;
	IBOutlet NSSlider * offsetSliderY4;
	
	IBOutlet NSButton * trackingScreen;
	

	
	NSUserDefaults *userDefaults;

}

-(void) updateSerial:(id)param;
-(IBAction) toggleXBeeLed:(id)sender;
-(IBAction) toggleLaser:(id)sender;
-(IBAction) resetLensshift:(id)sender;
-(IBAction) pos1Lensshift:(id)sender;
-(IBAction) pos2Lensshift:(id)sender;
-(IBAction) turnProjectorOn:(id)sender;
-(IBAction) turnProjectorOff:(id)sender;

-(IBAction) revertScreen:(id)sender;
-(void) setDmxValue:(int)val onChannel:(int)channel;
@end
