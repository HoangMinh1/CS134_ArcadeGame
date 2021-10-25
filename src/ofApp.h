#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class BaseObject {
public:
    BaseObject();
    ofVec3f trans, scale;
    float rot;
    void setPosition(ofVec3f);
    glm::mat4 getMatrix();

};
//end of BaseObject
//--------------------------------------------------------------

class Sprite: public BaseObject {
public:
    Sprite();
    void draw();
    float age();
    void setImage(ofImage);
    void update(); //added for part 2
    ofImage image;
    float width, height;
    float birthtime; // elapsed time in ms
    float lifespan;  //  time in ms
    //float speed;    //   in pixels/sec
    ofVec3f velocity; // in pixels/sec
    string name;
    bool haveImage;
};
//end of Sprite
//--------------------------------------------------------------

//Manage all sprites
class SpriteSystem  {
public:
    void add(Sprite);
    void remove(int);
    void update();
    void draw();
    vector<Sprite> sprites;

};
//end of SpriteSystem
//--------------------------------------------------------------

class Emitter: public BaseObject {
public:
    Emitter(SpriteSystem *);
    void draw();
    void start();
    void stop();
    void setLifespan(float);
    void setVelocity(ofVec3f);
    void setSpeed(int);
    void setChildImage(ofImage);
    void setImage(ofImage);
    void setRate(float);
    void setChildSound(ofSoundPlayer);
    void update();
    SpriteSystem *sys;
    float rate;
    int speed;          // speed of the missle
    ofVec3f heading;    // tell where the missles are heading
    ofVec3f velocity;
    float lifespan;
    bool started;
    float lastSpawned;
    ofImage childImage;
    ofImage image;
    //added sound
    ofSoundPlayer sound;    // sound when firing
    bool drawable;
    bool haveChildImage;    //image of missles
    bool haveImage;         //image of self
    //added Firing
    bool isFiring;
    bool haveSound;
    float width, height;
};
//end of Emitter
//--------------------------------------------------------------
class EnemyEmitter: public Emitter {
public:
    float scale;    //used for moving
    float cycles;   //used for moving
    bool isKilled;
    EnemyEmitter(SpriteSystem *);
    void moveSinPath();
    void moveSquarePath();
    void beDestroyed();
    void update();
};


//end of EnemyEmitter
//--------------------------------------------------------------

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void checkCollision();  //recently added

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
    unsigned int score = 0;
    ofVec3f lastMouse;
    ofImage img;
    ofSoundPlayer firing, explosion;
    //Emitter that represent spaceShip
    Emitter *spaceShip = NULL;
    EnemyEmitter *enemy = NULL;
    
    
    ofxPanel gui;
    ofxFloatSlider rate;
    ofxFloatSlider life;
    ofxToggle enemySpawn;
    //ofxVec3Slider velocity;
    ofxLabel screenSize;
};
