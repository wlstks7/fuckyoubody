#pragma once

#import "GLee.h"

#import <Cocoa/Cocoa.h>
#include "Plugin.h"
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxVectorMath.h"
#include "Filter.h"

@interface Jail : ofPlugin {
	IBOutlet NSSlider * backWall;
	IBOutlet NSSlider * leftWall;
	
	IBOutlet NSSlider * rotation;


}

@end