#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	kinect.open();
	kinect.initBodySource();

	appWidth = ofGetWidth();
	appHeight = ofGetHeight();
	bDebug = true;
	vidIndex = 0;
	currentWalk = 0;
	state = IDLE_CLOSE;
	timeOut = 1 * 1000;

	video[0].setup(30);
	video[0].load("video_walk-720p");

//	video[1].setup(30);
//	video[1].load("video_smile-720p");

	video[2].setup(30, true);
	video[2].load("idle_close-720p");
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();

	bool bBodyFound = false;
	//Getting joint positions (skeleton tracking)
	{
		auto bodies = kinect.getBodySource()->getBodies();

		for (auto body : bodies) 
		{
			for (auto joint : body.joints) {
				//now do something with the joints
				if (joint.first == JointType_SpineBase) {
					raw_distance = joint.second.getPosition().z;
					new_distance = ofMap(raw_distance, 0.6, 4.3, 1, 0,true);
					bBodyFound = true;
					state = WALK;
					vidIndex = currentWalk;
					break;
				}
			}
		}
	}


	if (!bBodyFound) new_distance = 0.0f;

	if (video[vidIndex].isLoaded()) {
		if (vidIndex < 2) {
			distance = 0.95f* distance + 0.05f*new_distance;
			video[vidIndex].setPosition(distance);
		}
		video[vidIndex].update();
	}

	if (distance < 0.001f) {
		curTime = ofGetElapsedTimeMillis();

		if (curTime - prevTime > timeOut) {
			if (state == WALK) {
				state = IDLE_CLOSE;
				vidIndex = 2;
				video[vidIndex].setSpeed(1.0f);
			}
		}
	}
	else {
		curTime = prevTime = ofGetElapsedTimeMillis();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	if (video[vidIndex].isLoaded()) {
		video[vidIndex].draw(0, 0, appWidth, appHeight);
	}

	if (bDebug) {
		ofPushStyle();
		ofSetColor(255, 0, 0);
		ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 20);
		ofDrawBitmapString("distance: " + ofToString(distance) + " raw distance: " + ofToString(raw_distance) + " video index = "+ofToString(vidIndex), 120, 20);
		ofPopStyle();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

}
