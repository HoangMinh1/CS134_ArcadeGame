//
//  Emitter.h
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#pragma once

#include "SpriteSystem.h"

class Emitter: public BaseObject {
public:
    Emitter(SpriteSystem *);
    void draw();
    void start();
    void stop();
    void setLifespan(float);
    void setVelocity(ofVec3f);
    void setChildImage(ofImage);
    void setSound(ofSoundPlayer);
    void setImage(ofImage);
    void setRate(float);
    void update();
    SpriteSystem *sys;
    float rate;
    ofVec3f velocity;
    float lifespan;
    bool started;
    float lastSpawned;
    ofImage childImage;
    ofImage image;
    ofSoundPlayer sound;
    bool drawable;
    bool haveChildImage;
    bool haveImage;
    bool haveSound;
    bool isFiring;
    float width, height;
};
