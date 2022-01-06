//
//  SpriteSystem.h
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#pragma once

#include "Sprite.h"

//Manage all sprites
class SpriteSystem  {
public:
    void add(Sprite);
    void remove(int);
    void update();
    void draw();
    vector<Sprite> sprites;

};
