#ifndef _TEST_APP
#define _TEST_APP


#include "ofxFFGLApp.h"

class testApp : public ofFFGLApp{
	
	public:
		testApp();
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		

		float numRepeats;

        ofTrueTypeFont myfont;
        ofImage testImage;
        string debugText;
};

#endif
	
