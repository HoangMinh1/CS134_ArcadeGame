#include "ofApp.h"
/*
 I implemented move up,down, left, and right using W,S,A,D
 Missing features:
 1.Background
 2.Multiple enemies
 3.Enemy rotation
 4.
 
 */

/*Ideas:
 Use mouse to determine the heading of the bullet
 Then take that vector and multiply with speed attribute to determine how fast the missle
 ...
 */

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
//--------------------------------------------------------------

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
//end of Sprite
//--------------------------------------------------------------

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

//end of SpriteSystem
//--------------------------------------------------------------

Emitter::Emitter(SpriteSystem *spriteSys){
    sys = spriteSys;
    rate = 1; //1 sprite per sec
    lifespan = 3000;
    
    started = false;
    lastSpawned = 0;
    haveChildImage = false;
    haveImage = false;
    speed = 600;
    heading = ofVec3f(1, 0, 0); //horizontal vector
    drawable = true;
    isFiring = false;
    haveSound = false;
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
        if(isFiring) {
        //create new Sprite for childImage
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

void Emitter::setSpeed(int s){
    speed = s;
}

void Emitter::setVelocity(ofVec3f v){
    velocity = v;
}

void Emitter::setImage(ofImage img){
    image = img;
    haveImage = true;
}

void Emitter::setChildImage(ofImage img){
    childImage = img;
    haveChildImage = true;
}

void Emitter::setRate(float r){
    rate = r;
}

void Emitter::setChildSound(ofSoundPlayer s){
    sound = s;
    haveSound = true;
}


//end of Emitter
//--------------------------------------------------------------
//
EnemyEmitter::EnemyEmitter(SpriteSystem *sys):Emitter(sys){
    cycles = 4;
    scale = 200;
}


void EnemyEmitter::moveSinPath(){
    float u = (cycles * trans.x * PI) / ofGetWidth();
    ofVec3f pos = ofVec3f(trans.x, -scale * sin(u) + (ofGetHeight() / 2), 0);
    setPosition(pos);
}

void EnemyEmitter::beDestroyed(){
    //do something if be destroyed
    //for now just play some sound
    sound.play();
}

void EnemyEmitter::update(){
    if(trans.x >= 0){
        moveSinPath();
        trans.x -= 1;
    }
    else
        trans.x = ofGetWindowWidth();  //reset position
}
//end of EnemyEmitter
//--------------------------------------------------------------
//
//
// Program starts here
//
void ofApp::setup(){
    
    gameState = "start";    // set game state
    
    //
    // Setup for spaceShip is here
    //
    spaceShip = new Emitter(new SpriteSystem());    //create an object
    spaceShip->setPosition(ofVec3f(ofGetWindowWidth()/2.0, ofGetWindowHeight()/2.0, 0));    //initialize some values
    spaceShip->drawable = true;
    
    firing.load("sound/laser.mp3");  //load sound
    spaceShip->setChildSound(firing);
    img.load("image/SpaceShip.png");    //load image of space ship
    spaceShip->setImage(img);
    img.load("image/missle.png");   //load image of missles
    spaceShip->setChildImage(img);
    spaceShip->start(); //call start method
    
    
    //
    // Setup for enemy is here
    //
    
    img.load("image/Enemies.png");
    enemy = new EnemyEmitter(new SpriteSystem());
    enemy->setImage(img);
    explosion.load("sound/explosion.mp3");  //set sound of collision
    enemy->setChildSound(explosion);
    
    
    
    //
    // Gui setup is here
    //
    
    gui.setup();    //set up gui
    gui.add(rate.setup("rate", 5, 1, 10));
    gui.add(life.setup("life", 5, .1, 10));
    //gui.add(velocity.setup("velocity", ofVec3f(1000, 0, 0), ofVec3f(-1000, -1000, -1000), ofVec3f(1000, 1000, 1000)));
    gui.add(enemySpawn.setup("Enemy Spawn", false));
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //
    // SpaceShip update is here
    //
    spaceShip->setRate(rate); //set how fast missles launch
    spaceShip->setLifespan(life * 1000);// convert to milliseconds
    spaceShip->setVelocity(spaceShip->speed * (spaceShip->heading + lastMouse)); //missle's direction = speed * (mouse + heading)
    spaceShip->update();
    
    //
    // Enemy update is here
    //
    if(!enemy->isKilled){
        checkCollision();
        enemy->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // Draw if game state = start
    
    if(gameState == "start"){
        ofDrawBitmapString("Press Space to play", ofGetWindowWidth() / 2.0 - 100, ofGetWindowHeight() /2.0);
    }
    
    //
    // Draw if game state = game
    
    else{
        //
        // Draw game features here: score, life, etc
        //
        
        ofDrawBitmapString("Score: " + ofToString(score), ofGetWindowWidth() - 100 , 50);   // draw score
        
        //
        // Draw spaceShip here
        //
        spaceShip->draw();
        
        //
        // Draw enemy here
        //
        if(!enemy->isKilled)
            enemy->draw();
        if(enemy->isKilled && enemySpawn){
            enemy->isKilled = false;
            //bugs, enemy does not appear in random position
            enemy->setPosition(ofVec3f(ofGetWindowWidth(), rand()% ofGetWindowHeight(), 0));
        }
           
        // Draw gui here
        gui.draw();
    }
}

//--------------------------------------------------------------

void ofApp::checkCollision(){
    for(int i = 0; i < spaceShip->sys->sprites.size(); i++){
        Sprite missle = spaceShip->sys->sprites[i];
        glm::vec3 misslePos = glm::vec3(missle.trans);
        glm::vec3 enemyPos = glm::vec3(enemy->trans);
        if(glm::distance2(misslePos, enemyPos) <= 200){
            enemy->isKilled = true;
            enemy->beDestroyed();
            score += 10;
        }
    }
}

//--------------------------------------------------------------
// Control buttons of the game
//
void ofApp::keyPressed(int key){

    int det  = 40; //how fast the object is moving
    switch (key) {
        case ' ':
            if(gameState == "start")
                gameState = "game";
            else{
                spaceShip->isFiring = true; //shooting
            }
            break;
        case 'w':
        case 'W':
            //condition check is for boundary
            if(spaceShip->trans.y > spaceShip->image.getHeight() / 2.0)
                spaceShip->trans.y -= det;
            break;
        case 's':
        case 'S':
            if(spaceShip->trans.y < ofGetWindowHeight() - spaceShip->image.getHeight() / 2.0)
                spaceShip->trans.y += det;
            break;
        case 'a':
        case 'A':
            if(spaceShip->trans.x > spaceShip->image.getWidth() / 2.0)
                spaceShip->trans.x -= det;
            break;
        case 'd':
        case 'D':
            if(spaceShip->trans.x < ofGetWindowWidth() - spaceShip->image.getWidth() / 2.0)
                spaceShip->trans.x += det;
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
