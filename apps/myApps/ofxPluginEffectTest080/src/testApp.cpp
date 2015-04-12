#include "testApp.h"

#include "ofxFFGLPlugin.h"

// adjust the line in project "build phases" -> "run script"
// cp -rf "$TARGET_BUILD_DIR/$PRODUCT_NAME.bundle" /Applications/Resolume\ Arena\ 4.1.1/plugins/vfx
// if your host app is different

testApp::testApp()
{
	// add parameters
	
	numRepeats = 1;
	
	addFloatParameter( "num repeats",	// name of parameter ( as it will appear in host )
						&numRepeats,	// address of the float this parameter will point to
						1,				// minimum value
						20				// maximum value
					  );
}

//--------------------------------------------------------------
void testApp::setup()
{
    // unfortunately while running as a plugin the data path root is
    // referred to the host and not to plugin executable
    // for test purpouse this uses a dir called FFGLDATA in arena's vfx dir
	//ofSetDataPathRoot("../../../plugins/vfx/FFGLdata/");
    ofSetDataPathRoot("../../../plugins/vfx/ofxPluginEffectTest080.bundle/Contents/Resources/data/");
	myfont.loadFont("Arial.ttf", 20);
	
	testImage.loadImage("gatto.gif"); // A small sample picture
    ofBackground(255,255,255);
}

//--------------------------------------------------------------
void testApp::update()
{
}

//--------------------------------------------------------------
void testApp::draw(){
	// input textures from host are stored here
	ofTexture * tex = inputTextures[0];
	
    static float alpha = 0;
    alpha += 0.2;
    
    if( !tex ) {
		return;
    }

	int nrep = numRepeats;

	float w = (float)ofGetWidth() / nrep;
	float h = (float)ofGetHeight() / nrep;
	
    for( int y = 0; y < nrep; y++ ) {
		for( int x = 0; x < nrep; x++ )
		{
			tex->draw(w*x,h*y,w,h);
		}
    }
    
    ofSetColor(255,255,255);
	ofNoFill();
	ofRect(20, 20, ofGetWidth()-40, ofGetHeight()-40);
	ofLine(10,10,100,100);
    
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotate(alpha);
    testImage.draw(-testImage.getWidth()/2, -testImage.getHeight()/2);
    ofPopMatrix();
    
    debugText = "Debug info OF080 with XC502";
    myfont.drawString(debugText, 100, 340);
    ofDrawBitmapString("Something to write", 10, 100);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}


//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}
