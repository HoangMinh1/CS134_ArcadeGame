//
//  Enemies.cpp
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#include "Enemies.h"

Enemies::Enemies(int size) {
    groupSize = size;
    lifespan = -1; //ms
    isSpawn = false;
    
    float time = ofGetElapsedTimeMillis();
    for(int i = 0; i < groupSize; i++){
        Sprite sprite;
        sprite.birthtime = time;
        sprite.lifespan = lifespan;
        this->add(sprite);
        isKilled.push_back(true);
    }
}

void Enemies::spawnAt(ofVec3f pos) {
    int space = 50;
    for(int i = 0; i < sprites.size(); i++){
        sprites[i].setPosition(ofVec3f(pos.x + space * i, pos.y, pos.z));
        sprites[i].lifespan = 20000;
    }
    isSpawn = true;
}

void Enemies::setImage(ofImage img){
    haveImage = true;
    for(int i = 0; i < sprites.size(); i++){
        sprites[i].image = img;
        sprites[i].haveImage = true;
        sprites[i].width = img.getWidth();
        sprites[i].height = img.getHeight();
    }
}

void Enemies::setSound(ofSoundPlayer s){
    haveSound = true;
    exSound = s;
}

void Enemies::setLifeSpan(float l){
    lifespan = l;
}


bool Enemies::isDestroyed(){
    //if enemy is destroy
    if (sprites.size() == 0) {
        isSpawn = false;
        return true;
    }
    return false;
}

void Enemies::update(){
    //delete if lifespan of enemies run out
    int speed = 1;
    if (sprites.size() == 0) return;
    for(int i = 0; i < sprites.size(); i++){
        if (sprites[i].lifespan != -1 && sprites[i].age() > sprites[i].lifespan) {
            sprites.erase(sprites.begin() + i);
            isKilled.erase(isKilled.begin() + i);
        }
        //otherwise update it
        else{
            sprites[i].trans.x -= speed;
        }
    }
}

void Viruses::move() {
    if(sprites.size() == 0) return;
    for(int i = 0; i < sprites.size(); i++){
        float u = (cycles * sprites[i].trans.x * PI) / ofGetWidth();
        sprites[i].trans.y += -scale * sin(u);
    }
}

void Octopus::move(){
    for(int i = 0; i < sprites.size(); i++){
        sprites[i].trans.y -= det;
    }
}
