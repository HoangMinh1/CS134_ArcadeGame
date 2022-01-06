#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "BaseObject.h"
#include "Sprite.h"
#include "SpriteSystem.h"
#include "Emitter.h"
#include "Enemies.h"
#include "SpaceShip.h"
#include "Explosion.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void checkCollision(vector<Sprite> missles, vector<Sprite> &enemies);  //recently added

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
    //manage gameState: start, game, end
    string gameState;
    
    // manage game features here
    unsigned int score = 0;
    
    
    // background variables
    ofImage background, background2;
    ofVec3f bgPos = ofVec3f(0, 0, 0); //background position
    ofVec3f bgPos2 = ofVec3f(2048, 0, 0);
    bool switchBG = true;   //used for background switching
    
    // game objects
    SpaceShip *spaceShip = NULL;
    Viruses *virus = NULL;
    Octopus *octopus = NULL;
    vector<Explosion> ex;
    
    // variables to control when to spawn object
    bool spawnViruses = false;
    bool spawnOctopuses = false;
    
    
    // miscellanous variables
    ofVec3f lastMouse;
    ofImage img;
    ofSoundPlayer firing, explosion;
    
    
    // gui
    ofxPanel gui;
    ofxFloatSlider rate;
    ofxFloatSlider life;
    //ofxVec3Slider velocity;
    ofxLabel screenSize;
    bool bHide = true;
};
