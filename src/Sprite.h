//
//  Sprite.h
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#pragma once

#include "BaseObject.h"

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
