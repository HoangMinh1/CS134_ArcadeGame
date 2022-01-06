#pragma once

#include "ofMain.h"

class BaseObject {
public:
    BaseObject();
    ofVec3f trans, scale;
    float rot;
    void setPosition(ofVec3f);
    glm::mat4 getMatrix();

};
