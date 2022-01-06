//
//  SpaceShip.cpp
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#include "SpaceShip.h"


void SpaceShip::setHeading(ofVec3f h){
    heading = h;
}

void SpaceShip::setMissleSpeed(int speed) {
    missleSpeed = speed;
}

void SpaceShip::addForce(ofVec3f force){
    pForce += force;
}

void SpaceShip::checkOutOfBound(){
    
    //up out of bound
    if(trans.y < height / 2.0){
        trans.y = height / 2.0;
        pVelocity = ofVec3f(0, 0, 0);   //reset velocity
    }
    //down out of bound
    if(trans.y > ofGetWindowHeight() - height / 2.0){
        trans.y = ofGetWindowHeight() - height / 2.0;
        pVelocity = ofVec3f(0, 0, 0);
    }
    //left out of bound
    if(trans.x < width / 2.0){
        trans.x = width / 2.0;
        pVelocity = ofVec3f(0, 0, 0);
    }
    //right out of bound
    if(trans.x > ofGetWindowWidth() - width / 2.0){
        trans.x = ofGetWindowWidth() - width / 2.0;
        pVelocity = ofVec3f(0, 0, 0);
    }
        
}


void SpaceShip::integrate() {
    
    float dt = 1.0 / ofGetFrameRate();
    // p = p + v * dt
    trans += pVelocity * dt;
    // a = F/m
    pAccel = pForce/mass;
    // v = v + a * dt
    pVelocity += pAccel * dt;
    // v = v * damping
    pVelocity = pVelocity * damping;
    //zero out force
    pForce = glm::vec3(0, 0 ,0);
    
}



