//
//  Sprite.cpp
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#include "Sprite.h"


// Sprite constructor
//
Sprite::Sprite(){
   //setup values like in examples
    width = 20;
    height = 5 ;
    birthtime = 0;
    lifespan = -1; //immortal?
    //speed = 10;
    velocity = ofVec3f(0, 0, 0);
    name = "UnamedSprite";
    haveImage = false;
    
}


void Sprite::draw(){
    // draw image centered and add in translation amount
    if (haveImage) {
        image.draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);
    }
    else {
        // in case no image is supplied, draw something.
        //ofSetColor(255, 0, 0);
        ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
    }
}

float Sprite::age() {
    return (ofGetElapsedTimeMillis() - birthtime);
}

void Sprite::setImage(ofImage img) {
    image = img;
    haveImage = true;
    width = image.getWidth();
    height = image.getHeight();
}

void Sprite::update() {
    trans += velocity / ofGetFrameRate();
}
