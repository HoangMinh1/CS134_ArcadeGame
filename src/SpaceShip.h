//
//  SpaceShip.h
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#pragma once

#include "Emitter.h"

class SpaceShip: public Emitter {
public:

    ofVec3f heading = ofVec3f(1, 0, 0);    
    int missleSpeed;          // speed of the missle
    
    //physics elements
    ofVec3f pForce;
    ofVec3f pVelocity;
    ofVec3f pAccel;
    float damping;
    float mass;
    
    SpaceShip(SpriteSystem * sys) : Emitter(sys) {
        pForce = ofVec3f(0, 0, 0);
        pVelocity = ofVec3f(0, 0, 0);
        pAccel = ofVec3f(0, 0, 0);
        damping = 0.99;
        mass = 2;
    };
    void setHeading(ofVec3f);
    void setMissleSpeed(int);
    void addForce(ofVec3f);
    void checkOutOfBound();
    void integrate();
};
