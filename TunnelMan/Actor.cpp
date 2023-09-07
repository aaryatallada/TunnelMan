#include "Actor.h"
#include "StudentWorld.h"
#include <algorithm>

// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp
GameObject::GameObject(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : GraphObject(imageID, startX, startY, dir, size, depth), m_StudentWorld(nullptr)
{
    
    GraphObject::setVisible(true);  //IDK IF THIS IS RIGHT, MIGHT HAVE TO CALL AFTER WE CREATE.     EDIT: works for now
}

    //destructor
GameObject::~GameObject(){
    
}



    //dosomething
void GameObject::doSomething(){
    //do something idk
}

StudentWorld* GameObject::getWorld(){
    return m_StudentWorld; // Return nullptr if there's no valid StudentWorld pointer
}

void GameObject::setWorld(StudentWorld* world) {
    m_StudentWorld = world;
}






//EARTH CLASS FUNCTIONS

    //constructor
Earth::Earth(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth):GameObject(TID_EARTH, startX, startY, dir, size, depth)
//IDEA IS: somewhere we create new earth objects for every valid startX and startY
{

}


    //destructor IDK WHAT TO DO
Earth::~Earth(){

}

    //doSomething
void Earth::doSomething(){
    
}

//TUNNELMAN CLASS FUNCTIONS

    //constructor
TunnelMan::TunnelMan(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth) : GameObject(TID_PLAYER, 30, 60, right, size, depth)
{
    
}


    //destructor IDK WHAT TO DO MAYBE deinitialize tunnel man (set coord out of bounds?)
TunnelMan::~TunnelMan(){
    
}
int TunnelMan::getNugget(){
    return m_nugget;
}

//void TunnelMan::increaseScore(int score){
//    m_score += score;
//}

void TunnelMan::addNugget(){
    m_nugget++;
}

void TunnelMan::annoyed(int howmuch){
    m_hitPoints -= howmuch;
    die();
}

void TunnelMan::die(){
    if (m_hitPoints <= 0){
        m_lostLife = true;
        
    }
}
//int TunnelMan::getScore(){
//    return m_score;
//}

    //dosomething
void TunnelMan::doSomething(){
    bool blockR = false;//set false later if boulder in the way
    bool blockL = false;
    bool blockU = false;
    bool blockD = false;
    blockR = (getWorld()->isBoulderAt(getX()+4, getY()) ||(getWorld()->isBoulderAt(getX()+4, getY()+1)) || (getWorld()->isBoulderAt(getX()+4, getY() + 2)) || (getWorld()->isBoulderAt(getX()+4, getY() + 3)) || (getWorld()->isBoulderAt(getX()+4, getY() - 1)) || (getWorld()->isBoulderAt(getX()+4, getY() - 2)) || (getWorld()->isBoulderAt(getX()+4, getY() - 3)));
    blockL = (getWorld()->isBoulderAt(getX()-4, getY()) ||(getWorld()->isBoulderAt(getX()-4, getY()+1)) || (getWorld()->isBoulderAt(getX()-4, getY() + 2)) || (getWorld()->isBoulderAt(getX()-4, getY() + 3)) || (getWorld()->isBoulderAt(getX()-4, getY() - 1)) || (getWorld()->isBoulderAt(getX()-4, getY() - 2)) || (getWorld()->isBoulderAt(getX()-4, getY() - 3)));
    blockU = (getWorld()->isBoulderAt(getX(), getY()+4) ||(getWorld()->isBoulderAt(getX()+1, getY()+4)) || (getWorld()->isBoulderAt(getX()+2, getY() + 4)) || (getWorld()->isBoulderAt(getX()+3, getY() + 4)) || (getWorld()->isBoulderAt(getX()-1, getY() + 4)) || (getWorld()->isBoulderAt(getX()-2, getY() + 4)) || (getWorld()->isBoulderAt(getX()-3, getY() + 4)));
    blockD = (getWorld()->isBoulderAt(getX(), getY()-4) ||(getWorld()->isBoulderAt(getX()+1, getY()-4)) || (getWorld()->isBoulderAt(getX()+2, getY() - 4)) || (getWorld()->isBoulderAt(getX()+3, getY() - 4)) || (getWorld()->isBoulderAt(getX()-1, getY() - 4)) || (getWorld()->isBoulderAt(getX()-2, getY() - 4)) || (getWorld()->isBoulderAt(getX()-3, getY() - 4)));
    int ch;
    if (getWorld()->getKey(ch) == true)
    {
    // user hit a key this tick!
    switch (ch)
    {
    case KEY_PRESS_LEFT:
            if(getX()>0 && !blockL)
                moveTo(getX()-1, getY());
            setDirection(left);
//    ... move player to the left ...;
    break;
    case KEY_PRESS_RIGHT:
            if(getX()<60 && !blockR)
                moveTo(getX()+1, getY());
            setDirection(right);
//    ... move player to the right ...;
    break;
    case KEY_PRESS_UP:
            if(getY()<60 && !blockU)
                moveTo(getX(), getY()+1);
            setDirection(up);
    break;
    case KEY_PRESS_DOWN:
            if(getY()>0 && !blockD)
                moveTo(getX(), getY()-1);
            setDirection(down);
    break;
    case KEY_PRESS_ESCAPE:
            getWorld()->getTunnelMan()->annoyed(10);
    break;
    case KEY_PRESS_SPACE:
            if(m_squirt > 0){
                shoot();
                m_squirt--;
            }
    break;
    case 'z':
    case 'Z':
            if(m_sonar > 0){
                m_sonar--;
                getWorld()->illuminate(getX(), getY());
                getWorld()->playSound(SOUND_SONAR);
            }
    break;
    case KEY_PRESS_TAB:
            getWorld()->dropNug(getX(), getY());
    break;
            
//    case KEY_PRESS_SPACE:
//    ... add a Squirt in front of the player...;
//    break;

    }

    }
}

int TunnelMan::getHealth(){
    return m_hitPoints;
}


//GOODIES CLASS FUNCTIONS



Goodies::Goodies(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth)
    : GameObject(imageID, startX, startY, dir, size, depth) {
        m_state = true;
    // constructor implementation
}

Goodies::~Goodies() {
    // destructor implementation
}

void Goodies::doSomething() {
    // doSomething implementation
}
bool Goodies::getState(){
    //do nothing for baseclass
    return m_state;
}

std::string Goodies::getStability(){
    return "";
}

void Goodies::setState(bool alive){
    m_state = alive;
}

std::string Goodies::getVal(){
    return "";
}

void Goodies::setWaiting(bool wait){
    
}

bool Goodies::isWaiting(){
    return true;
}

void Goodies::setTicks(int howmuch){
    m_waitTicks += howmuch;
}

int Goodies::getTicks(){
    return m_waitTicks;
}


Nugget::Nugget(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth)
    : Goodies(imageID, startX, startY, dir, size, depth) {
        GraphObject::setVisible(false);
        setState(true);
        setWorld(getWorld());
        m_waitTicks = 100;
    // constructor implementation
}

Nugget::~Nugget() {
    // destructor implementation
}

void Nugget::doSomething() {
    // doSomething implementation
    if (!m_state) {//not alive
        return;
    }
    if(m_waiting == true && m_waitTicks == 0){
        setVisible(false);
        setState(false);
        setWaiting(false);
    }
    else if(m_waiting == true)
        setTicks(-1);
    
    TunnelMan* tunnelMan = getWorld()->getTunnelMan();
    if (!isVisible()) {
        double distance = sqrt(pow(tunnelMan->getX() - getX(), 2) + pow(tunnelMan->getY() - getY(), 2));
        if (distance <= 4.0) {
            setVisible(true);
            return;
        }
    } else if (isVisible() && isWaiting() == false) {
        double distance = sqrt(pow(tunnelMan->getX() - getX(), 2) + pow(tunnelMan->getY() - getY(), 2));
        if (distance <= 3.0) {
            setState(false); // Set the state to dead
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->increaseScore(10); // Increase player's score
            tunnelMan->addNugget(); // Update the TunnelMan's inventory
            return;
        }
    }
    // doSomething implementation
}

std::string Nugget::getVal(){
    return m_val;
}

int TunnelMan::getSquirt(){
    return m_squirt;
}

bool TunnelMan::getLostLife(){
    return m_lostLife;
}

void TunnelMan::addSonar(){
    m_sonar++;
}

void TunnelMan::setLostLife(bool life){
    m_lostLife = life;
}

void TunnelMan::removeNugget(){
    m_nugget--;
}

void TunnelMan::shoot() {
    switch (getDirection())
    {
    case left:
        if(!getWorld()->hasEarth(getX()-4,getY())&& !getWorld()->isBoulderAt(getX()-4, getY()))
            getWorld()->addGoodie(new Squirt(getX() - 4, getY(), getDirection()));
        break;
    case right:
        if (!getWorld()->hasEarth(getX() + 4, getY()) && !getWorld()->isBoulderAt(getX()+4, getY()))
            getWorld()->addGoodie(new Squirt(getX() + 4, getY(), getDirection()));
        break;
    case down:
        if (!getWorld()->hasEarth(getX() , getY()-4) && !getWorld()->isBoulderAt(getX(), getY()-4))
            getWorld()->addGoodie(new Squirt(getX(), getY() - 4, getDirection()));
        break;
    case up:
        if (!getWorld()->hasEarth(getX(), getY() + 4) && !getWorld()->isBoulderAt(getX(), getY()+4 ))
        getWorld()->addGoodie(new Squirt(getX(), getY() + 4, getDirection()));
        break;
    case none:return;
    }
    getWorld()->playSound(SOUND_PLAYER_SQUIRT);
}


void TunnelMan::setSonar(int howmuch){
    m_sonar += howmuch;
}

int TunnelMan::getSonar(){
    return m_sonar;
}

void TunnelMan::addWater(){
    m_squirt += 5;
}



void Nugget::setState(bool alive) {
    // setState implementation
    m_state = alive;
}

bool Nugget::getState() {
    // getState implementation
    return m_state;
}
std::string Nugget::getStability(){
    return "";
}

void Nugget::setTicks(int howmuch){
    m_waitTicks += howmuch;
}

int Nugget::getTicks(){
    return m_waitTicks;
}

bool Nugget::isWaiting(){
    return m_waiting;
}

void Nugget::setWaiting(bool wait){
    m_waiting = wait;
}

//BOULDER FUNCTIONS
Boulder::Boulder(int startX, int startY)
    : Goodies(TID_BOULDER, startX, startY, down, 1.0, 1) {
//        m_alive = true;
        m_state = "stable";
        m_waitingTicks = 0;
    // Other initialization specific to Boulder
}

Boulder::~Boulder(){
    //destructor
}

std::string Boulder::getVal(){
    return m_val;
}

void Boulder::doSomething(){
    if (getStability() == "dead") {
         return; // If not alive, return immediately
     }
    if (collisionWithTunnelMan()) {
        // Decrement player's life count
        getWorld()->getTunnelMan()->annoyed(100);
        //getWorld()->getTunnelMan()->decLives();
        
        
        // Set the Boulder's state to dead so it will be removed from the game
        setStability("dead");
    }
     if (getStability() == "stable") {
         // Check for Earth below the Boulder
         if (getWorld()->hasEarth(getX(), getY() - 1) ||
             getWorld()->hasEarth(getX() + 1, getY() - 1) ||
             getWorld()->hasEarth(getX() + 2, getY() - 1) ||
             getWorld()->hasEarth(getX() + 3, getY() - 1)) {
             return; // There's Earth below, do nothing
         } else {
             setStability("waiting"); // Transition to waiting state
             changeTicks(30); // Set waiting counter
         }
     } else if (getStability() == "waiting") {
         changeTicks(-1);
         if (getTicks() == 0) {
             setStability("falling"); // Transition to falling state
             getWorld()->playSound(SOUND_FALLING_ROCK);
         }
     } else if (getStability() == "falling") {
         // Check for conditions to stop falling
         if (getY() <= 0 || // Hit the bottom
             getWorld()->isBoulderAt(getX(), getY() - 1) || // Hit another Boulder
             getWorld()->hasEarth(getX(), getY() - 1) ||
             getWorld()->hasEarth(getX() + 1, getY() - 1) ||
             getWorld()->hasEarth(getX() + 2, getY() - 1) ||
             getWorld()->hasEarth(getX() + 3, getY() - 1)) {
             setStability("dead"); // Set state to dead
             return;
         }
         moveTo(getX(), getY() - 1); // Move down
     }
 }


//bool Boulder::isAlive(){
//    return m_alive;
//}
//
//void Boulder::setAlive(bool alive){
//    m_alive = alive;
//}

void Boulder::setStability(std::string state){
    m_state = state;
}

std::string Boulder::getStability(){
    return m_state;
}

void Boulder::changeTicks(int ticks){
    m_waitingTicks += ticks;
}

int Boulder::getTicks(){
    return m_waitingTicks;
}

//void Boulder::annoyProt(){
//    int x = getWorld()->getTunnelMan()->getX();
//    int y = getWorld()->getTunnelMan()->getY();
////    double distance = sqrt(pow(tunnelMan->getX() - getX(), 2) + pow(tunnelMan->getY() - getY(), 2));
//
//    
//}

bool Boulder::collisionWithTunnelMan() {
    // Get TunnelMan's coordinates
    int tunnelManX = getWorld()->getTunnelMan()->getX();
    int tunnelManY = getWorld()->getTunnelMan()->getY();
    
    // Check if Boulder's coordinates overlap with TunnelMan's coordinates
    if (getX() + 3 >= tunnelManX && getX() <= tunnelManX + 3 &&
        getY() <= tunnelManY + 3 && getY() + 3 >= tunnelManY) {
        return true; // Collision detected
    }
    
    return false; // No collision
}


//SQUIRT CLASS DEF
//
Squirt::Squirt(int startX, int startY, Direction dir)
: Goodies(TID_WATER_SPURT, startX, startY, dir, 1.0, 1), m_dist(0)
{
    setWorld(getWorld());
}

void Squirt::doSomething(){
    if (!getState())
        return;
//    if (annoyProtesters()||m_travel == 4 ) {
//        setState(false);
//        return;
//    }
    switch (getDirection()) {
    case left:
        if (getWorld()->hasEarth(getX() - 1, getY()) || getWorld()->isBoulderAt(getX() - 1, getY())) {
            setState(false);
            return;
        }
        else   moveTo(getX() - 1, getY());
        break;
    case right:
        if (getWorld()->hasEarth(getX() + 1, getY()) || getWorld()->isBoulderAt(getX() + 1, getY())) {
            setState(false);
            return;
        }
        else   moveTo(getX() + 1, getY());
        break;
    case up:
        if (getWorld()->hasEarth(getX(), getY() + 1) || getWorld()->isBoulderAt(getX(), getY() + 1)) {
            setState(false);
            return;
        }
        else moveTo(getX(), getY() + 1);
        break;
    case down:
        if (getWorld()->hasEarth(getX(), getY() - 1) || getWorld()->isBoulderAt(getX(), getY() - 1)) {
            setState(false);
            return;
        }
        else moveTo(getX(), getY() - 1);
        break;
    default:
            return;
    }
    m_dist++;
}


void Squirt::setState(bool alive){
    m_state = alive;
}

bool Squirt::getState(){
    return m_state;
}


std::string Squirt::getVal(){
    return m_val;
}



//Barrel functions

Barrel::Barrel(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth)
: Goodies(imageID, startX, startY, dir, size, depth)
{
    m_state = true;
}

Barrel::~Barrel(){}

void Barrel::doSomething(){
    TunnelMan* tunnelMan = getWorld()->getTunnelMan();
    if (!isVisible()) {
        double distance = sqrt(pow(tunnelMan->getX() - getX(), 2) + pow(tunnelMan->getY() - getY(), 2));
        if (distance <= 4.0) {
            setVisible(true);
            return;
        }
    } else if (isVisible()) {
        double distance = sqrt(pow(tunnelMan->getX() - getX(), 2) + pow(tunnelMan->getY() - getY(), 2));
        if (distance <= 3.0) {
            setState(false); // Set the state to dead
            getWorld()->playSound(SOUND_FOUND_OIL);
            getWorld()->increaseScore(1000); // Increase player's score
            return;
        }
    }
    
}

void Barrel::setState(bool alive){
    m_state = alive;
}

bool Barrel::getState(){
    return m_state;
}

std::string Barrel::getVal(){
    return m_val;
}



//SONAR
Sonar::Sonar(int startX, int startY, Direction dir)
: Goodies(TID_SONAR, startX, startY, dir, 1.0, 2), m_waitTicks(0), m_state(true)
{
    
    setVisible(false);
    setWorld(getWorld());
}

void Sonar::doSomething(){
    if(!getState())
        return;
    if(getTicks() == 0){
        setTicks(2000);
        setVisible(false);
    }
    else
        setTicks(-1);
    if(getTicks() == 1000)
        setVisible(true);
    

    TunnelMan* tunnelMan = getWorld()->getTunnelMan();
    if (isVisible()) {
        double distance = sqrt(pow(tunnelMan->getX() - getX(), 2) + pow(tunnelMan->getY() - getY(), 2));
        if (distance <= 3.0) {
            setState(false); // Set the state to dead
            setVisible(false);
            //setTicks(2000);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->increaseScore(75); // Increase player's score
            tunnelMan->addSonar(); // Update the TunnelMan's inventory
            return;
        }
    }
}


void Sonar::setState(bool alive){
    m_state = alive;
}

bool Sonar::getState(){
    return m_state;
}

std::string Sonar::getVal(){
    return m_val;
}

int Sonar::getTicks(){
    return m_waitTicks;
}


void Sonar::setTicks(int howmuch){
    m_waitTicks += howmuch;
}

Sonar::~Sonar(){}



//Water
Water::Water(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth)
: Goodies(imageID, startX, startY, dir, size, depth), m_state(true), m_T(0)
{
    setVisible(true);
}

Water::~Water(){}

void Water::doSomething(){
    if(!m_state)
        return;
    if(m_T == 0){
        setVisible(false);
        setState(false);
        return;
    }
    m_T--;
    
    TunnelMan* tunnelMan = getWorld()->getTunnelMan();
    if (isVisible()) {
        double distance = sqrt(pow(tunnelMan->getX() - getX(), 2) + pow(tunnelMan->getY() - getY(), 2));
        if (distance <= 3.0) {
            setState(false); // Set the state to dead
            setVisible(false);
            //setTicks(2000);
            getWorld()->playSound(SOUND_GOT_GOODIE);
            getWorld()->increaseScore(100); // Increase player's score
            tunnelMan->addWater(); // Update the TunnelMan's inventory
            return;
        }
    }
    
}

void Water::setState(bool alive){
    m_state = alive;
}

bool Water::getState(){
    return m_state;
}

std::string Water::getVal(){
    return m_val;
}

void Water::setTicks(int howmuch){
    m_waitTicks = howmuch;
}

int Water::getTicks(){
    return m_waitTicks;
}


void Water::setT(int T){
    m_T += T;
}





//PROTESTOR
Protestor::Protestor(int imageID, int health, int level)
: Goodies(imageID, 60, 60, left, 1.0, 0), m_giveup(false), m_tTick(200), m_yTick(15), m_state(true), m_level(level)
{
    m_health = health;
    m_move = rand() % 53 + 8;
    m_rTick = std::max(0, 3 - m_level);
}


void Protestor::doSomething(){
        if (!getState()) {
            return; // If dead, return
        }

        if (m_rTick > 0) {
            m_rTick--;
            return; // If resting, update rest ticks and return
        } else {
            m_rTick = std::max(0, 3 - m_level / 4);
            m_tTick++;
            m_yTick++;
        }

        if (m_giveup) {
          //  if (getX() == 60 && getY() == 60) {
                setState(false);
                getWorld()->ProtDead();
                return; // If reached exit, die
           // }
            //getWorld()->ProtGiveUp(this);
            return; // If give up, try to move towards exit
        }

        // Check if close to TunnelMan
        int x = getX();
        int y = getY();
        int Tx = getWorld()->getTunnelMan()->getX();
        int Ty = getWorld()->getTunnelMan()->getY();
        int dist = sqrt(pow(Tx - x, 2) + pow(Ty - y, 2));
        if (dist <= 4 && TowardTman()) {
            if (m_yTick > 15) {
                getWorld()->getTunnelMan()->annoyed(2);
                getWorld()->playSound(SOUND_PROTESTER_YELL);
                m_yTick = 0;
                return;
            }
            return; // If close to TunnelMan, annoy
        }

        // Behavior for moving towards TunnelMan
        Direction D = DtoTman();
        if (dist <= 4 && D != none && isPath(D)) {
            setDirection(D);
            moveD(D);
            m_move = 0;
            return;
        }

        // Behavior for random movement
        m_move--;
        if (m_move <= 0) {
            Direction k;
            do {
                k = Random();
            } while (!freeSpace(getX(), getY(), k));
            setDirection(k);
            m_move = rand() % 53 + 8;
        } else if (isInter() && m_tTick > 200) {
            Turn();
            m_tTick = 0;
            m_move = rand() % 53 + 8;
        }
        moveD(getDirection());
        if (!freeSpace(getX(), getY(), getDirection())) {
            m_move = 0;
        }
    }

//    //if dead ret
//    if(!getState())
//        return;
//    //if resting update the rest ticks
//    if(m_rTick > 0){
//        m_rTick--;
//        return;
//    }
//    else{
//        m_rTick = std::max(0, 3 - m_level / 4);
//            m_tTick++;
//            m_yTick++;
//    }
//
//    if(m_giveup){
//        std::cout<<getX()<< " "<< getY()<<std::endl;
//        if(getX()==60 && getY() == 60){
//            setState(false);
//            getWorld()->ProtDead();//DIE >:(
//            /****************************************************************************************************************************/
//            //ALSO ADD DECREMENTING PROTESTORS FROM GETWORLDS VECTOR HERE
//            return;
//        }
//        getWorld()->ProtGiveUp(this);
//        return;
//
//        //TODO: move one step closer to exit and return
//    }
//
//
//    int x = getX();
//    int y = getY();
//    int Tx = getWorld()->getTunnelMan()->getX();
//    int Ty = getWorld()->getTunnelMan()->getY();
//    int dist = sqrt(pow(Tx - x, 2) + pow(Ty-y, 2));
//    if(dist <= 4 && TowardTman())
//    {
//        if(m_yTick > 15){
//            getWorld()->getTunnelMan()->annoyed(2);
//            getWorld()->playSound(SOUND_PROTESTER_YELL);
//            m_yTick = 0;
//            return;
//        }
//        return;
//    }
//    //TODO: FOR HARD PROT ADD MORE
//
//
//    Direction D = DtoTman();
//    if (dist <= 4 && D != none && isPath(D)){
//        setDirection(D);
//        moveD(D);
//        m_move = 0;
//        return;
//    }
//
//    m_move--;
//    if (m_move <= 0) {
//        Direction k;
//        do {
//            k = Random();
//        } while (!freeSpace(getX(), getY(), k));
//
//        setDirection(k);
//        m_move = rand() % 53 + 8;
//    }
//    else if (isInter() && m_tTick > 200) {
//        Turn();
//        m_tTick = 0;
//        m_move = rand() % 53 + 8;
//    }
//    moveD(getDirection());
//    if (!freeSpace(getX(),getY(),getDirection())) {
//        m_move = 0;
//    }



GraphObject::Direction Protestor::Random(){

        int d;
        d = rand() % 4;
        if(d == 0)
            return down;
        if(d == 1)
            return up;
        if(d == 2)
            return left;
        if(d == 3)
            return right;
        return none;
    
}


void Protestor::moveD(Direction D){
    int newX = getX();
    int newY = getY();
    
    if (D == left) {
        newX = std::max(0, getX() - 1);
        setDirection(left);
    } else if (D == right) {
        newX = std::min(63, getX() + 1);
        setDirection(right);
    } else if (D == up) {
        newY = std::min(60, getY() + 1);
        setDirection(up);
    } else if (D == down) {
        newY = std::max(0, getY() - 1);
        setDirection(down);
    } else if (D == none) {
        return;
    }
    
    if (getX() != newX || getY() != newY) {
        moveTo(newX, newY);
    }
}





GraphObject::Direction Protestor::DtoTman(){
    int x = getWorld()->getTunnelMan()->getX();
    int y = getWorld()->getTunnelMan()->getY();

    if (getY() == y && getX() == x) {
        return getDirection();
    }
    if (getY() == y) {
        if (getX() > x) {
            return left;
        }
        if (getX() < x) {
            return right;
        }
    }

    if (getX() == x) {
        if (getY() < y) {
            return up;
        }
        if (getY() > y) {
            return down;
        }
    }
    return none;

}




bool Protestor::freeSpace(int x, int y, Direction dir)
{
    switch (dir) {
        case left:
            for (int i = x; i >= x - 3; --i) {
                if (getWorld()->hasEarth(i, y) || getWorld()->isBoulderAt(i, y))
                    return false;
            }
            return true;
        case right:
            for (int i = x; i <= x + 3; ++i) {
                if (getWorld()->hasEarth(i, y) || getWorld()->isBoulderAt(i, y))
                    return false;
            }
            return true;
        case up:
            for (int j = y; j <= y + 3; ++j) {
                if (getWorld()->hasEarth(x, j) || getWorld()->isBoulderAt(x, j))
                    return false;
            }
            return true;
        case down:
            for (int j = y; j >= y - 3; --j) {
                if (getWorld()->hasEarth(x, j) || getWorld()->isBoulderAt(x, j))
                    return false;
            }
            return true;
        default:
            return false;
    }
}


bool Protestor::isPath(Direction D){
    int x = getWorld()->getTunnelMan()->getX();
    int y = getWorld()->getTunnelMan()->getX();
    bool obstacleFound = false;

    switch (D) {
        case left:
            for (int i = getX(); i >= x; i--) {
                if (getWorld()->hasEarth(i, getY()) || getWorld()->isBoulderAt(i, getY())) {
                    obstacleFound = true;
                    break;
                }
            }
            return !obstacleFound;
            break;

        case right:
            for (int i = getX(); i <= x; i++) {
                if (getWorld()->hasEarth(i, getY()) || getWorld()->isBoulderAt(i, getY())) {
                    obstacleFound = true;
                    break;
                }
            }
            return !obstacleFound;
            break;

        case up:
            for (int j = getY(); j <= y; j++) {
                if (getWorld()->hasEarth(getX(), j) || getWorld()->isBoulderAt(getX(), j)) {
                    obstacleFound = true;
                    break;
                }
            }
            return !obstacleFound;
            break;

        case down:
            for (int j = getY(); j >= y; j--) {
                if (getWorld()->hasEarth(getX(), j) || getWorld()->isBoulderAt(getX(), j)) {
                    obstacleFound = true;
                    break;
                }
            }
            return !obstacleFound;
            break;

        case none:
            return false;
    }

}

bool Protestor::isInter(){
//    if(getDirection() == right || getDirection() == left){
//        bool one = !getWorld()->hasEarth(getX(), getY()+4) && !getWorld()->hasEarth(getX()+1, getY()+4) && !getWorld()->hasEarth(getX() + 2, getY()+4) && !getWorld()->hasEarth(getX() + 3, getY()+4);
//        bool two = !getWorld()->hasEarth(getX(), getY()-4) && !getWorld()->hasEarth(getX()+1, getY()-4) && !getWorld()->hasEarth(getX() + 2, getY()-4) && !getWorld()->hasEarth(getX() + 3, getY()-4);
//        return one || two;
//    }
//    else{
//        bool one = !getWorld()->hasEarth(getX()+4, getY()) && !getWorld()->hasEarth(getX()+4, getY()+1) && !getWorld()->hasEarth(getX() + 4, getY()+2) && !getWorld()->hasEarth(getX() + 4, getY()+3);
//        bool two = !getWorld()->hasEarth(getX()-4, getY()) && !getWorld()->hasEarth(getX()-4, getY()+1) && !getWorld()->hasEarth(getX() - 4, getY()+2) && !getWorld()->hasEarth(getX() - 4, getY()+3);
//        return one || two;
//    }
        if (getDirection() == right || getDirection() == left) {
            bool one = !getWorld()->hasEarth(getX(), getY() + 4) && !getWorld()->hasEarth(getX() + 1, getY() + 4) && !getWorld()->hasEarth(getX() + 2, getY() + 4) && !getWorld()->hasEarth(getX() + 3, getY() + 4);
            bool two = !getWorld()->hasEarth(getX(), getY() - 4) && !getWorld()->hasEarth(getX() + 1, getY() - 4) && !getWorld()->hasEarth(getX() + 2, getY() - 4) && !getWorld()->hasEarth(getX() + 3, getY() - 4);
            bool noBoulderAbove = true;
            bool noBoulderBelow = true;
            for (int i = -3; i <= 3; ++i) {
                if (getWorld()->isBoulderAt(getX() + i, getY() + 4)) {
                    noBoulderAbove = false;
                }
                if (getWorld()->isBoulderAt(getX() + i, getY() - 4)) {
                    noBoulderBelow = false;
                }
            }
            return (one && noBoulderAbove) || (two && noBoulderBelow);
        }
        else {
            bool one = !getWorld()->hasEarth(getX() + 4, getY()) && !getWorld()->hasEarth(getX() + 4, getY() + 1) && !getWorld()->hasEarth(getX() + 4, getY() + 2) && !getWorld()->hasEarth(getX() + 4, getY() + 3);
            bool two = !getWorld()->hasEarth(getX() - 4, getY()) && !getWorld()->hasEarth(getX() - 4, getY() + 1) && !getWorld()->hasEarth(getX() - 4, getY() + 2) && !getWorld()->hasEarth(getX() - 4, getY() + 3);
            bool noBoulderRight = true;
            bool noBoulderLeft = true;
            for (int i = -3; i <= 3; ++i) {
                if (getWorld()->isBoulderAt(getX() + 4, getY() + i)) {
                    noBoulderRight = false;
                }
                if (getWorld()->isBoulderAt(getX() - 4, getY() + i)) {
                    noBoulderLeft = false;
                }
            }
            return (one && noBoulderRight) || (two && noBoulderLeft);
        }
}



void Protestor::Turn(){
    if (getDirection() == up || getDirection() == down) {
        bool canMoveLeft = isInter() && !getWorld()->isBoulderAt(getX() - 3, getY()) && !getWorld()->isBoulderAt(getX() - 3, getY() + 1) && !getWorld()->isBoulderAt(getX() - 3, getY() + 2) && !getWorld()->isBoulderAt(getX() - 3, getY() + 3) && !getWorld()->hasEarth(getX() - 3, getY()) && !getWorld()->hasEarth(getX() - 3, getY() + 1) && !getWorld()->hasEarth(getX() - 3, getY() + 2) && !getWorld()->hasEarth(getX() - 3, getY() + 3);
        bool canMoveRight = isInter() && !getWorld()->isBoulderAt(getX() + 4, getY()) && !getWorld()->isBoulderAt(getX() + 4, getY() + 1) && !getWorld()->isBoulderAt(getX() + 4, getY() + 2) && !getWorld()->isBoulderAt(getX() + 4, getY() + 3) && !getWorld()->hasEarth(getX() + 4, getY()) && !getWorld()->hasEarth(getX() + 4, getY() + 1) && !getWorld()->hasEarth(getX() + 4, getY() + 2) && !getWorld()->hasEarth(getX() + 4, getY() + 3);
        
        if (!canMoveLeft) {
            setDirection(canMoveRight ? right : none);
        }
        else if (!canMoveRight) {
            setDirection(canMoveLeft ? left : none);
        }
        else {
            int randDir = rand() % 2;
            setDirection(randDir == 0 ? left : right);
        }
    }
    else {
        bool canMoveUp = isInter() && !getWorld()->isBoulderAt(getX(), getY() + 4) && !getWorld()->isBoulderAt(getX() + 1, getY() + 4) && !getWorld()->isBoulderAt(getX() + 2, getY() + 4) && !getWorld()->isBoulderAt(getX() + 3, getY() + 4) && !getWorld()->hasEarth(getX(), getY() + 4) && !getWorld()->hasEarth(getX() + 1, getY() + 4) && !getWorld()->hasEarth(getX() + 2, getY() + 4) && !getWorld()->hasEarth(getX() + 3, getY() + 4);
        bool canMoveDown = isInter() && !getWorld()->isBoulderAt(getX(), getY() - 3) && !getWorld()->isBoulderAt(getX() + 1, getY() - 3) && !getWorld()->isBoulderAt(getX() + 2, getY() - 3) && !getWorld()->isBoulderAt(getX() + 3, getY() - 3) && !getWorld()->hasEarth(getX(), getY() - 3) && !getWorld()->hasEarth(getX() + 1, getY() - 3) && !getWorld()->hasEarth(getX() + 2, getY() - 3) && !getWorld()->hasEarth(getX() + 3, getY() - 3);
        
        if (!canMoveUp) {
            setDirection(canMoveDown ? down : none);
        }
        else if (!canMoveDown) {
            setDirection(canMoveUp ? up : none);
        }
        else {
            int randDir = rand() % 2;
            setDirection(randDir == 0 ? up : down);
        }
    }

}


void Protestor::annoyed(int health){
    if(m_giveup)
        return;
    m_health -= health;
    getWorld()->playSound(SOUND_PROTESTER_ANNOYED);
    stunned();
    if(m_health <= 0){
        m_giveup = true;
        getWorld()->playSound(SOUND_PROTESTER_GIVE_UP);
        m_rTick = 0;
        if(health == 100){//boulder did it
            getWorld()->increaseScore(100);//ADD 100 POINTS IF TAKE OUT PROTESTOR
        }
        else if(getID() == TID_PROTESTER)
            getWorld()->increaseScore(100);
        else
            getWorld()->increaseScore(250);
    }
}

void Protestor::stunned(){
    m_rTick = std::max(50, 100 - m_level*10);
}

void Protestor::Bribed(){
    getWorld()->playSound(SOUND_PROTESTER_FOUND_GOLD);
    if (getID() == TID_PROTESTER) {
        getWorld()->increaseScore(25);
        m_giveup = true;
    } else {
        getWorld()->increaseScore(50);
        int tickRest = std::max(50, 100 - m_level * 10);
        m_rTick = tickRest;
    }

}

void Protestor::setState(bool alive){
    m_state = alive;
}

bool Protestor::getState(){
    return m_state;
}

bool Protestor::TowardTman(){
    Direction D = getDirection();
    if (D == left) {
        return getWorld()->getTunnelMan()->getX() <= getX();
    } else if (D == right) {
        return getWorld()->getTunnelMan()->getX() >= getX();
    } else if (D == up) {
        return getWorld()->getTunnelMan()->getY() >= getY();
    } else if (D == down) {
        return getWorld()->getTunnelMan()->getY() <= getY();
    } else {
        return false;
    }

}
Protestor::~Protestor(){}



RegProt::RegProt(int level)
: Protestor(TID_PROTESTER, 5, level)
{
    
}


std::string Protestor::getVal(){
    return m_value;
}

HardProt::HardProt(int level)
: Protestor(TID_HARD_CORE_PROTESTER, 20, level)
{
    
}
