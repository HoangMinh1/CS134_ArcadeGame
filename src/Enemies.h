//
//  Enemies.h
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#pragma once

#include "SpriteSystem.h"

class Enemies: public SpriteSystem {
public:
    Enemies(int);
    vector<bool> isKilled;
    bool isSpawn;
    int groupSize;
    float lifespan;
    ofImage image;
    ofSoundPlayer exSound;
    bool haveSound;
    bool haveImage;
    
    void spawnAt(ofVec3f); //spawn enemy at that position
    void setImage(ofImage);
    void setSize(int);
    void setSound(ofSoundPlayer);
    void setLifeSpan(float);
    virtual void move() = 0;
    bool isDestroyed();
    void update();
};

class Viruses: public Enemies {
public:
    float cycles;
    float scale;
    Viruses(int size): Enemies(size) {
        cycles = 2;
        scale = 5;
    }
    void move();
};

class Octopus: public Enemies {
    float det;
public:
    Octopus(int size): Enemies(size) {
        det = 2;
    }
    void move();
};
