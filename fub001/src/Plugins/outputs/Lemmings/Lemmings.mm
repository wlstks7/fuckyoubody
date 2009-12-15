//
//  _ExampleOutput.mm
//  openFrameworks
//
//  Created by Jonas Jongejan on 15/11/09.

#import "PluginIncludes.h"

@implementation Lemmings

-(void) awakeFromNib{
	[super awakeFromNib];
}

-(void) initPlugin{
	lemmingList = [[NSMutableArray array] retain];
	userDefaults = [[NSUserDefaults standardUserDefaults] retain];
}

-(void) update:(CFTimeInterval)timeInterval displayTime:(const CVTimeStamp *)outputTime{
	PersistentBlob * blob;
	
	[numberLemmingsControl setIntValue:[lemmingList count]];
	
	for(blob in [tracker([cameraControl selectedSegment]) persistentBlobs]){
		BOOL lineFound = NO;
	
		Blob * b;
		BOOL anyBlobs = NO;
		for(b in [blob blobs]){
			anyBlobs = YES;
			Lemming * lemming;
			
			CvPoint2D32f * pointArray = new CvPoint2D32f[ [b nPts] ];
			
			for( int i = 0; i < [b nPts]; i++){
				ofxPoint2f p = [GetPlugin(ProjectionSurfaces) convertFromProjection:[b pts][i] surface:[GetPlugin(ProjectionSurfaces) getProjectionSurfaceByName:"Front" surface:"Floor" ]];
				pointArray[i].x = p.x;
				pointArray[i].y = p.y;
			}
			
			CvMat pointMat = cvMat( 1, [b pts].size(), CV_32FC2, pointArray);

			for(lemming in lemmingList){
		
				double dist = cvPointPolygonTest(&pointMat, cvPoint2D32f([lemming position]->x, [lemming position]->y), 0);
				
				if( dist >= 0 ){
					int shortestI = -1;
					float shortestDist;
					for( int i = 0; i < [b nPts] ; i+=5){
						ofxPoint2f p = [GetPlugin(ProjectionSurfaces) convertFromProjection:[b pts][i] surface:[GetPlugin(ProjectionSurfaces) getProjectionSurfaceByName:"Front" surface:"Floor" ]];
						float dist = ((ofxPoint2f*) [lemming position])->distanceSquared(p);
						if(shortestI == -1 || dist < shortestDist){
							shortestI = i;
							shortestDist = dist;
						}
					}
					
					if(shortestI != -1){
						ofxVec2f p = [GetPlugin(ProjectionSurfaces) convertFromProjection:[b pts][shortestI] surface:[GetPlugin(ProjectionSurfaces) getProjectionSurfaceByName:"Front" surface:"Floor" ]];
						[lemming setDestination:new ofxVec2f(p)];
						[lemming setLagFactor:0.33];
					}
				} else {
					[lemming setDestination:new ofxVec2f(*[lemming position] + ofxVec2f(ofRandom(0.0,0.002),ofRandom(0.0,0.004)))];
				}

			}

			free(pointArray);
		}
	}
	
	Lemming * lemming;

	while (lemmingDiff > 0) {
		[lemmingList addObject:[[[Lemming alloc]initWithX:ofRandom(0, 1) Y:ofRandom(0, 1) spawnTime:timeInterval]autorelease]];
		lemmingDiff--;
		NSLog(@"adding a lemming");
	}
	while (lemmingDiff < 0) {
		[[lemmingList lastObject] setDying:YES];
		lemmingDiff++;
		NSLog(@"removing a lemming");
	}
		
	for(lemming in lemmingList){
		if ([lemming dying]) {
			[lemmingList removeObject:lemming];
		}
	}
	
}

-(void) setup{

	lemmingDiff = 400;
	
}

-(void) controlDraw:(CFTimeInterval)timeInterval displayTime:(const CVTimeStamp *)timeStamp{
	
	glPushMatrix();{
		
		ofScale(ofGetWidth(), ofGetHeight(), 1);
		
		ofEnableAlphaBlending();
		ofSetColor(255, 255, 255,127);
		ofFill();
		Lemming * lemming;
		for(lemming in lemmingList){
			[lemming draw:timeInterval displayTime:timeStamp];
		}
		
		ofNoFill();
		PersistentBlob * blob;
		
		for(blob in [tracker([cameraControl selectedSegment]) persistentBlobs]){
			int i=blob->pid%5;
			switch (i) {
				case 0:
					ofSetColor(255, 0, 0,255);
					break;
				case 1:
					ofSetColor(0, 255, 0,255);
					break;
				case 2:
					ofSetColor(0, 0, 255,255);
					break;
				case 3:
					ofSetColor(255, 255, 0,255);
					break;
				case 4:
					ofSetColor(0, 255, 255,255);
					break;
				case 5:
					ofSetColor(255, 0, 255,255);
					break;
					
				default:
					ofSetColor(255, 255, 255,255);
					break;
			}
			Blob * b;
			for(b in [blob blobs]){
				glBegin(GL_LINE_STRIP);
				for(int i=0;i<[b nPts];i++){
					ofxPoint2f p =[GetPlugin(ProjectionSurfaces) convertFromProjection:[b pts][i] surface:[GetPlugin(ProjectionSurfaces) getProjectionSurfaceByName:"Front" surface:"Floor" ]];
					glVertex2f(p.x, p.y);
				}
				glEnd();
			}
		}	
	}glPopMatrix();
}

-(void) draw:(CFTimeInterval)timeInterval displayTime:(const CVTimeStamp *)outputTime{
	ofFill();
	ofEnableAlphaBlending();
	Lemming * lemming;
	
	[GetPlugin(ProjectionSurfaces) apply:"Front" surface:"Floor"];
	
	ofSetColor(0, 127,0,127);
	ofRect(0, 0, 1, 1);

	ofSetColor(255, 255, 255,255);

	for(lemming in lemmingList){
		[lemming draw:(CFTimeInterval)timeInterval displayTime:(const CVTimeStamp *)outputTime];
	}
	
	glPopMatrix();
	
	[GetPlugin(ProjectionSurfaces) apply:"Back" surface:"Floor"];
	
	ofSetColor(0,0,255,255);
	ofRect(0, 0, 1, 1);

	ofSetColor(255, 255, 255,255);

	for(lemming in lemmingList){
		[lemming draw:(CFTimeInterval)timeInterval displayTime:(const CVTimeStamp *)outputTime];
	}


	glPopMatrix();
	
	/*[GetPlugin(ProjectionSurfaces) apply:"Back" surface:"Floor"];
	
	for(lemming in lemmingList){
		[lemming draw:(CFTimeInterval)timeInterval displayTime:(const CVTimeStamp *)outputTime];
	}
	
	glPopMatrix();
	*/
}

-(IBAction) addLemming:(id)sender{
	lemmingDiff++;
}

-(IBAction) removeOldestLemming:(id)sender{
	lemmingDiff--;
}

@end

@implementation Lemming
@synthesize radius, position, spawnTime, lemmingList, dying, lagFactor, destination;

-(id) initWithX:(float)xPosition Y:(float)yPosition spawnTime:(CFTimeInterval)timeInterval{
	
	self = [super init];
	
	position = new ofxVec2f();
	destination = new ofxVec2f();
	radius = 0.01;
	lagFactor = ofRandom(0.005, 0.1);
	
	if (self) {
		
		position->x = 0.25;
		position->y = 0.0;
		
		destination->x = xPosition;
		destination->y = yPosition;
    }
	
	spawnTime = timeInterval;
	
	return self;
}

-(void) draw:(CFTimeInterval)timeInterval displayTime:(const CVTimeStamp *)outputTime{
	*position += (*destination - *position) * lagFactor;
	
	if (position->x < 0.0 || position->x > 1.0 || position->y < 0.0 || position->y > 1.0 ) {
		
		lagFactor = ofRandom(0.005, 0.1);

		position->x = 0.25;
		position->y = 0.0;
		
		destination->x = ofRandom(0, 1.0);
		destination->y = ofRandom(0, 1.0);
		
	}
	ofCircle(position->x, position->y, radius);
}

@end
