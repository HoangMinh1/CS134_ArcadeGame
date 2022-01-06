//
//  Emitter.cpp
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#include "Emitter.h"

Emitter::Emitter(SpriteSystem *spriteSys){
    sys = spriteSys;
    rate = 1; //1 sprite per sec
    lifespan = 3000;
    
    started = false;
    lastSpawned = 0;
    haveChildImage = false;
    haveImage = false;
    //speed = 600;
    //heading = ofVec3f(1, 0, 0); //horizontal vector
    drawable = true;
    isFiring = false;
    //haveSound = false;
    width = 50;
    height = 50;
    
}

void Emitter::draw(){
    if(drawable){
        if(haveImage)
            image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
        else{
            ofSetColor(0, 0, 200);
            ofDrawRectangle(-width/2 + trans.x, -height/2 + trans.y, width, height);
        }
    }
    sys->draw();
}

//initialize started and last spawned
void Emitter::start(){
    started = true;
    lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop(){
    started = false;
}

void Emitter::update(){
    if(!started) return;
    
    float time = ofGetElapsedTimeMillis();
    if((time - lastSpawned) > (1000.0/rate)){
        //create new Sprite for childImage
        if(isFiring){
            Sprite sprite;
            if(haveChildImage) sprite.setImage(childImage);
            if(haveSound) sound.play();
            //initialize value of this sprite as Emitter's value
            sprite.velocity = velocity;
            sprite.lifespan = lifespan;
            sprite.setPosition(trans);
            sprite.birthtime = time;
            sys->add(sprite);
            lastSpawned = time;
        }
    }
    //call sys->update to erase sub-sprite in sys if lifespan exceeds threshold
    sys->update();
    isFiring = false;
}

void Emitter::setLifespan(float l){
    lifespan = l;
}

void Emitter::setVelocity(ofVec3f v){
    velocity = v;
}

void Emitter::setImage(ofImage img){
    image = img;
    haveImage = true;
    
    // update width and height
    width = img.getWidth();
    height = img.getHeight();
}

void Emitter::setSound(ofSoundPlayer s) {
    sound = s;
    haveSound = true;
}

void Emitter::setChildImage(ofImage img){
    childImage = img;
    haveChildImage = true;
}

void Emitter::setRate(float r){
    rate = r;
}
