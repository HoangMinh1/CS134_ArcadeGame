//
//  BaseObject.cpp
//  myGame
//
//  Created by Hoang Nguyen on 11/2/21.
//

#include "BaseObject.h"

// Base Object
//
BaseObject::BaseObject(){
    //default values like in example
    trans = ofVec3f(0, 0, 0);
    scale = ofVec3f(1, 1, 1);
    rot = 0;
}

void BaseObject::setPosition(ofVec3f pos) {
    trans = pos;
}

glm::mat4 BaseObject::getMatrix(){
    glm::mat4 t = glm::translate(glm::mat4(1.0), glm::vec3(trans));
    glm::mat4 r = glm::rotate(glm::mat4(1.0), glm::radians(rot), glm::vec3(0, 0, 1));
    //no need scale for now
    //glm::mat4 s = glm::scale(glm::mat4(1.0), scale);
    glm::mat4 T = t * r;
    return T;
}
//end of BaseObject
