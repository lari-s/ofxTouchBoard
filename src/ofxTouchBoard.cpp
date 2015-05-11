#include "ofxTouchBoard.h"

void ofxTouchBoard::setup(){
	serial.setup();
	electrodes.resize(ELECTRODES_NB);

	graphHeight = 200;
	graphBarSpace = 10;
	graphBarWidth = 20; 
	jitter = 0.0;
}

void ofxTouchBoard::update(){
	serial.update();

	vector<Electrode> rawData(serial.getNormalizedData());

	if(electrodes.size() == rawData.size()){
		for(int i = 0; i < electrodes.size(); ++i){
			electrodes[i].touch = rawData[i].touch;
			electrodes[i].diff = (1.0 - jitter) * rawData[i].diff + jitter * electrodes[i].diff;
			electrodes[i].bval = (1.0 - jitter) * rawData[i].bval + jitter * electrodes[i].bval;
			electrodes[i].fdat = (1.0 - jitter) * rawData[i].fdat + jitter * electrodes[i].fdat;
			electrodes[i].tths = rawData[i].tths;
			electrodes[i].rths = rawData[i].rths;
		}
	}
	else{
		ofLog() << "electrodes.size() != rawData.size()";
	}
}

void ofxTouchBoard::logData(){
	serial.printData();
}



void ofxTouchBoard::draw(float x, float y){
	for(int i = 0; i < electrodes.size(); ++i){
		Electrode e(electrodes[i]);

		// ofSetColor(ofColor(147, 147, 147, 100));
		// if(e.touch){
			ofSetColor(ofColor(35, 255, 106, 100));
		// }
		// else{
			// ofSetColor(ofColor(147, 147, 147, 100));
		// }
		// Draw filter data graph bar
		drawGraphBar(x, y, i, e.fdat, graphBarWidth/2.0, -graphBarWidth/4.0);	
		// Draw base value graph bar
		ofSetColor(ofColor(35, 106, 255, 100));
		drawGraphBar(x, y, i, e.bval, graphBarWidth/2.0, graphBarWidth/4.0);
		// Draw touch threshold graph bar
		// drawGraphBar(i, e.tths, graphBarWidth);

		// Draw diff graph bar
		// if(e.touch){
		// 	ofSetColor(ofColor(35, 255, 106));
		// }
		// else{
		// 	ofSetColor(ofColor(35, 106, 255));
		// }
		// drawGraphBar(i, e.diff, graphBarWidth);

		// Draw release threshold graph bar
		// ofSetColor(ofColor(147, 147, 147, 100));
		// drawGraphBar(i, e.rths, graphBarWidth);
	}
}

void ofxTouchBoard::drawGraphBar(float x0, float y0, int i, float val, float width, float xOffset){
	float y = y0 - (val * graphHeight)/2.0;
	float x = x0 + graphBarWidth + xOffset + (graphBarWidth + graphBarSpace) * i;
	ofDrawPlane(x, y, width, val * graphHeight);
}

void ofxTouchBoard::printData(float x, float y){
	float charWidth = 11;
	float charHeight = 15;
	float xOffset = x;
	float yOffset = y + charHeight;
	float colWidth = 30;
	float rowHeight = 20;
	ofDrawBitmapString("E", x, yOffset);
	xOffset += 2 * charWidth;
	ofDrawBitmapString("TOUCH", xOffset, yOffset);
	xOffset += 5 * charWidth;
	ofDrawBitmapString("TTHS", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("RTHS", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("FDAT", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("BVAL", xOffset, yOffset);
	xOffset += 4 * charWidth;
	ofDrawBitmapString("DIFF", xOffset, yOffset);
	yOffset += charHeight;

	for(int i = 0; i < electrodes.size(); ++i){
		xOffset = x;
		ofDrawBitmapString(ofToString(i), xOffset, yOffset);
		xOffset += 2 * charWidth;
		ofDrawBitmapString(ofToString(ofxTB::trunc(electrodes[i].touch, 2)), xOffset, yOffset);
		xOffset += 5 * charWidth;
		ofDrawBitmapString(ofToString(ofxTB::trunc(electrodes[i].tths, 2)), xOffset, yOffset);
		xOffset += 4 * charWidth;
		ofDrawBitmapString(ofToString(ofxTB::trunc(electrodes[i].rths, 2)), xOffset, yOffset);
		xOffset += 4 * charWidth;
		ofDrawBitmapString(ofToString(ofxTB::trunc(electrodes[i].fdat, 2)), xOffset, yOffset);
		xOffset += 4 * charWidth;
		ofDrawBitmapString(ofToString(ofxTB::trunc(electrodes[i].bval, 2)), xOffset, yOffset);
		xOffset += 4 * charWidth;
		ofDrawBitmapString(ofToString(ofxTB::trunc(electrodes[i].diff, 2)), xOffset, yOffset);
		yOffset += charHeight;
	}
}





