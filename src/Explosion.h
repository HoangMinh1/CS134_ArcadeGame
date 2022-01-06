//
//  Explosion.h
//  myGame
//
//  Created by Hoang Nguyen on 11/3/21.
//

#pragma once
#include "Sprite.h"

class Explosion: public BaseObject {
public:
    int groupSize = 10;
    int force = 100;
    ofImage img;
    vector<Sprite> sprites;
    
    void draw() {
        for(int i = 0; i < sprites.size(); i++)
            sprites[i].draw();
    }
    
    void init(){
        for(int i = 0; i < sprites.size(); i++)
            sprites[i].velocity = force * ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0);
    }
    
    void update(){
        float time = ofGetElapsedTimeMillis();
        for(int i = 0; i < sprites.size(); i++){
            if((time - sprites[i].birthtime) > sprites[i].lifespan)
                sprites.erase(sprites.begin() + i);
            else
                sprites[i].update();
        }
    }
    
    void setImage(ofImage img){
        for(int i = 0; i < sprites.size(); i++)
            sprites[i].setImage(img);
    }
    
    Explosion(ofVec3f pos){
        float time = ofGetElapsedTimeMillis();
        for(int i = 0; i < groupSize; i++){
            Sprite sprite;
            sprite.setPosition(pos);
            sprite.birthtime = time;
            sprite.lifespan = 2000;
            sprites.push_back(sprite);
        }
    }
    
    bool isDestroyed(){
        if (sprites.size() == 0) return true;
        return false;
    }
};


