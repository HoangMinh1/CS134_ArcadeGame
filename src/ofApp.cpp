
//
//  CS134 - Game Development
//
//  2D Arcade Game: Ocean Adventure Theme
//  Author: Hoang Nguyen
//

#include "ofApp.h"


// Program starts here
//
void ofApp::setup(){
    
    // set up variables here
    //
    
    // set up game state variable
    //
    gameState = "start";    // set game state
    background.load("image/background.png");
    background2.load("image/background.png");
    
    // set up space ship
    //
    
    spaceShip = new SpaceShip(new SpriteSystem());    //create an object
    spaceShip->setPosition(ofVec3f(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0, 0));    //initialize some values
    
    firing.load("sound/laser.mp3");  //load sound
    spaceShip->setSound(firing);
    img.load("image/SpaceShip.png");    //load image of space ship
    spaceShip->setImage(img);
    spaceShip->drawable = true;
    img.load("image/missle.png");   //load image of missles
    spaceShip->setChildImage(img);
    
    spaceShip->start(); //call start method
    
    
    // set up enemies
    //
    
    virus = new Viruses(10);
    img.load("image/virus.png");  //set up for enemy
    virus->setImage(img);
    explosion.load("sound/explosion1.mp3");  //set sound of collision
    virus->setSound(explosion);
    spawnViruses = true;
    
    octopus = new Octopus(5);
    img.load("image/octopus.png");
    octopus->setImage(img);
    octopus->setSound(explosion);
    spawnOctopuses = true;
    
    
    
    gui.setup();    //set up gui
    gui.add(rate.setup("rate", 4, 1, 10));
    gui.add(life.setup("life", 5, .1, 10));
    //gui.add(velocity.setup("velocity", ofVec3f(1000, 0, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (gameState == "game") {
        //background loop control
        //
        
        if(switchBG){
            //draw BG first, BG2 second
            if(bgPos.x == -1024) bgPos2.x = 1024;
            if(bgPos.x == -2048) switchBG = false;
        }
        else{
            if(bgPos2.x == -1024) bgPos.x = 1024;
            if(bgPos2.x == -2048) switchBG = true;
        }
        bgPos.x -= 1;
        bgPos2.x -= 1;
        
        // game control
        //
        
        spaceShip->setRate(rate);   //set how fast missles launch
        spaceShip->setLifespan(life * 1000);    // convert to milliseconds
        spaceShip->setMissleSpeed(400);
        spaceShip->setVelocity(spaceShip->missleSpeed * (spaceShip->heading + lastMouse)); //missle's direction = speed * (mouse + heading)
      
        spaceShip->update();
        spaceShip->integrate(); //add physics
        spaceShip->checkOutOfBound();
        
        
        if(spawnViruses) {
            virus->spawnAt(ofVec3f(ofGetWindowWidth(), ofGetWindowHeight()/2, 0));
            spawnViruses = false;   //reset condition
        }
        if(spawnOctopuses) {            octopus->spawnAt(ofVec3f(ofGetWindowWidth()/2, ofGetWindowHeight(), 0));
            spawnOctopuses = false; //reset
        }
        
        checkCollision(spaceShip->sys->sprites, virus->sprites);
        checkCollision(spaceShip->sys->sprites, octopus->sprites);
        
        
        if(!virus->isDestroyed() && virus->isSpawn){
            virus->move();
            virus->update();
        }

        if(!octopus->isDestroyed() && octopus->isSpawn){
            octopus->move();
            octopus->update();
        }
         
        // update explosion
        //
        for(int i = 0; i < ex.size(); i++){
            if(ex[i].isDestroyed())
                ex.erase(ex.begin() + i);
            else
                ex[i].update();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if(gameState == "start") {
        ofDrawBitmapString("Press Space to play", ofGetWindowWidth() / 2.0 - 100, ofGetWindowHeight() /2.0);
    }
    //gameState == "game"
    else if(gameState == "game"){
        
        // draw background
        //
        background.draw(bgPos);
        background2.draw(bgPos2);
        
        // draw game state: score, life
        ofDrawBitmapString("Score: " + ofToString(score), ofGetWindowWidth() - 100 , 50);
        
        
        // draw spaceship
        //
        spaceShip->draw();
        
        // draw enemies here
        if(virus->isSpawn)
            virus->draw();
        if(octopus->isSpawn)
            octopus->draw();
        
        
        // draw explosion
        for(int i = 0; i < ex.size(); i++){
            ex[i].draw();
        }
        
        if(!bHide)
            gui.draw();
    }
    else{
        ofDrawBitmapString("Game Over!", ofGetWindowWidth() / 2.0 - 100, ofGetWindowHeight() /2.0);
    }
}

//--------------------------------------------------------------
//fix this later so that it accept two arguments
void ofApp::checkCollision(vector<Sprite> missles, vector<Sprite> &enemies){
    if(missles.size() == 0 || enemies.size() == 0) return;
    int exThres = enemies[0].width/2 + missles[0].width / 2 + 60;
    int shipThres = spaceShip->width/2 + enemies[0].width / 2 + 70;
    glm::vec3 missle, enemy;
    glm::vec3 ship = glm::vec3(spaceShip->trans);
    
    for(int i = 0; i <  missles.size(); i++){
        for(int j = 0; j < enemies.size(); j++){
            missle = glm::vec3(missles[i].trans);
            enemy = glm::vec3(enemies[j].trans);
            if(glm::distance2(missle, enemy) <= exThres){
                //set lifespan of enemy = 0 => death
                enemies[j].lifespan = 0;
                
                //create explosion effect
                Explosion explosion(enemies[j].trans);
                img.load("image/explosion.png");
                explosion.setImage(img);
                explosion.init();
                ex.push_back(explosion);
                
                // play sound
                virus->exSound.play();
                
                // add score
                score += 10;
            }
            if(glm::distance2(enemy, ship) <= shipThres)
                gameState = "end";
        }
    }
}

//--------------------------------------------------------------
// Control buttons of the game
//
void ofApp::keyPressed(int key){

    int force  = 3000; //how strong is the thrust
    switch (key) {
        case ' ':
            if(gameState == "start")
                gameState = "game";
            else
                spaceShip->isFiring = true; //shooting
            break;
        case 'w':
        case 'W':
            //condition check is for boundary
            //if(spaceShip->trans.y > spaceShip->image.getHeight() / 2.0)
                spaceShip->addForce(ofVec3f(0, -force, 0));

            break;
        case 's':
        case 'S':
            //if(spaceShip->trans.y < ofGetWindowHeight() - spaceShip->image.getHeight() / 2.0)
                spaceShip->addForce(ofVec3f(0, force, 0));
            
            break;
        case 'a':
        case 'A':
            //if(spaceShip->trans.x > spaceShip->image.getWidth() / 2.0)
                spaceShip->addForce(ofVec3f(-force, 0, 0));
            
            break;
        case 'd':
        case 'D':
            //if(spaceShip->trans.x < ofGetWindowWidth() - spaceShip->image.getWidth() / 2.0)
                spaceShip->addForce(ofVec3f(force, 0, 0));
            break;
        case 'H':
        case 'h':
            bHide = !bHide;
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
// Move mouse to change the direction of missles
//
void ofApp::mouseMoved(int x, int y ){
    //  The position of mouse only affect the direction of missle
    //  but not the magnitude. Thus, we need to check the condition
    //  in case direction of lastmouse is opposite with heading
    if(x > spaceShip->trans.x) {
        lastMouse = ofVec3f(x, y, 0) - (spaceShip->trans + spaceShip->heading);
        glm::vec3 nor = lastMouse; // convert ofVec3f into glm::vec3
        nor = glm::normalize(nor); // use glm::vec3 to normalize
        lastMouse = nor;    // assign value back
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
