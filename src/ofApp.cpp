#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(30);
	kinect.open();
	kinect.initBodySource();

	appWidth = ofGetWidth();
	appHeight = ofGetHeight();
	video.setup(30);
	video.load("video_walk-720p");

	video2.setup(30);
	video2.load("video_smile-720p");
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();

	//Getting joint positions (skeleton tracking)
	{
		auto bodies = kinect.getBodySource()->getBodies();
		for (auto body : bodies) {
			for (auto joint : body.joints) {
				//now do something with the joints
				if (joint.first == JointType_SpineBase) {
					distance = joint.second.getPosition().z;
					distance = ofMap(distance, 0.5, 5, 1, 0.1);
				}
			}
		}
	}

	//ofLogNotice() << "distance: " << distance;

	if (video.isLoaded()) {
		video.setPosition(distance);
		video.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);

	ofDrawBitmapString("distance: "+ofToString(distance), 120,20);

	if (video.isLoaded()) {
		video.draw(0, 0, appWidth, appHeight);
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
