//
//  SpriteSystem.cpp
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#include "SpriteSystem.h"

void SpriteSystem::add(Sprite s){
    //take advantage of dynamic memory of vector<Sprite>
    sprites.push_back(s);
}

void SpriteSystem::remove(int i){
    //easy delete
    sprites.erase(sprites.begin() + i);
}

void SpriteSystem::update(){
    if (sprites.size() == 0) return;
    vector<Sprite>::iterator s = sprites.begin();
    vector<Sprite>::iterator tmp;
    //why we need to set tmp = erase and s = tmp?
    //review later
    while (s != sprites.end()) {
        if (s->lifespan != -1 && s->age() > s->lifespan) {
            tmp = sprites.erase(s);
            s = tmp;
        }
        else s++;
    }
    for (int i = 0; i < sprites.size(); i++) {
        //sprites[i].trans +=  sprites[i].velocity / ofGetFrameRate();
        sprites[i].update();
    }
}

void SpriteSystem::draw(){
    for(int i = 0; i < sprites.size(); i++)
        sprites[i].draw();
}
