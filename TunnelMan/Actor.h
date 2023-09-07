#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"
//#include "StudentWorld.h"
class StudentWorld;
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class GameObject : public GraphObject{ //derived from GraphObject
public:
    GameObject(int imageID, int startX, int startY, Direction dir = right, double size = 1, unsigned int depth = 0);
    virtual ~GameObject();
    virtual void doSomething(); //IDK IF VOID IS RIGHT FOR NOW
    
    //IDK IF I SHOULD ADD THIS
    StudentWorld* getWorld();
    void setWorld(StudentWorld* world);
private:
    StudentWorld* m_StudentWorld;
};



//EARTH CLASS DEFINITION
class Earth : public GameObject{
public:
    Earth(int imageID, int startX, int startY, Direction dir = right, double size = .25, unsigned int depth = 3);
    virtual ~Earth();
    virtual void doSomething();
};




////TUNNELMAN CLASS DEFINITION
//class TunnelMan : public GameObject{
//public:
//    TunnelMan(int imageID = TID_PLAYER, int startX = 30, int startY = 60, Direction dir = right, double size = 1, unsigned int depth = 0);
//    virtual ~TunnelMan();
//    virtual void doSomething();
//    void increaseScore(int score);
//    int getScore();
//    void addInventory();
//private:
//    int m_hitPoints = 10;
//    int m_squirt = 5;
//    int m_sonar = 1;
//    int m_nugget = 0;
//    int m_score = 0;
//    std::vector<Goodies*> m_inventory;
//};






//GOODIES CLASS DEFINITION


class Goodies : public GameObject {
public:
    Goodies(int imageID, int startX, int startY, Direction dir, double size, unsigned int depth);
    virtual ~Goodies();
    virtual void doSomething();
    virtual bool getState();
    virtual void setState(bool alive);
    virtual std::string getStability();
    virtual std::string getVal();
    virtual  void setTicks(int howmuch);
    virtual void setWaiting (bool wait);
    virtual bool isWaiting ();
    virtual int getTicks();
private:
    bool m_state;
    int m_waitTicks;
};

class Nugget : public Goodies {
public:
    Nugget(int imageID = TID_GOLD, int startX = rand() % 60, int startY = rand() % 56, Direction dir = right, double size = 1, unsigned int depth = 2);
    virtual ~Nugget();
    virtual void doSomething();
    virtual void setState(bool alive);
    virtual bool getState();
    virtual std::string getStability();
    virtual std::string getVal();
    virtual int getTicks();
    virtual void setTicks(int howmuch);
    virtual bool isWaiting();
    virtual void setWaiting(bool wait);
private:
    bool m_state;
    bool m_waiting = false;
    std::string m_val = "nugget";
    int m_waitTicks;
};



//BARREL CLASS DEFINITION
class Barrel : public Goodies{
public:
    Barrel(int imageID = TID_BARREL, int startX = rand() % 60, int startY = rand() % 56, Direction dir = right, double size = 1.0, unsigned int depth = 2);
    virtual ~Barrel();
    virtual void doSomething();
    virtual void setState(bool alive);
    virtual bool getState();
    virtual std::string getVal();
private:
    bool m_state;
    std::string m_val = "barrel";
    
};

//TUNNELMAN CLASS DEFINITION
class TunnelMan : public GameObject{
public:
    TunnelMan(int imageID = TID_PLAYER, int startX = 30, int startY = 60, Direction dir = right, double size = 1, unsigned int depth = 0);
    virtual ~TunnelMan();
    virtual void doSomething();
//    void increaseScore(int score);
    void addNugget();
    void removeNugget();
//    int getScore();
    int getNugget();
    bool getLostLife();
    void setLostLife(bool life);
    virtual void annoyed(int hit);
    virtual void die();
    void shoot();
    int getSquirt();
    void addWater();
    int getSonar();
    void setSonar(int howmuch);
    int getHealth();
    void addSonar();
private:
    int m_hitPoints = 10;
    int m_squirt = 5;
    int m_sonar = 1;
    int m_nugget = 0;
    bool m_lostLife = false;
//    int m_score = 0;
};




//BOULDER CLASS DEFINITION
class Boulder : public Goodies {
public:
    Boulder(int startX, int startY);
    virtual ~Boulder();
    virtual void doSomething();
//    bool isAlive();
//    void setAlive(bool alive);
    void setStability(std::string state);
    virtual std::string getStability();
    void changeTicks(int ticks);
    int getTicks();
    bool collisionWithTunnelMan();
    virtual std::string getVal();
    //void annoyProt();

    
    // Other member functions and variables

private:
//    bool m_alive;
    std::string m_state;
    int m_waitingTicks;
    std::string m_val = "boulder";
    // Other private members
};


class Squirt : public Goodies {
public:
    Squirt(int startX, int startY, Direction dir);
    virtual void doSomething();
    virtual void setState(bool alive);
    virtual bool getState();
    virtual std::string getVal();

private:
    int m_dist;
    bool m_state;
    std::string m_val = "squirt";

};



//SONAR KIT CLASS

class Sonar : public Goodies{
public:
    Sonar(int startX = 0, int startY = 60, Direction dir = right);
    virtual ~Sonar();
    virtual void doSomething();
    virtual void setState(bool alive);
    virtual bool getState();
    virtual std::string getVal();
    virtual void setTicks(int howmuch);
    virtual int getTicks();
private:
    bool m_state;
    std::string m_val = "sonar";
    int m_waitTicks;
    
};
class Water : public Goodies{
public:
    Water(int imageID = TID_WATER_POOL, int startX = rand() % 60, int startY = rand() % 56, Direction dir = right, double size = 1.0, unsigned int depth = 2);
    virtual ~Water();
    virtual void doSomething();
    virtual void setState(bool alive);
    virtual bool getState();
    virtual std::string getVal();
    virtual void setTicks(int howmuch);
    virtual int getTicks();
    void setT(int T);

private:
    bool m_state;
    std::string m_val = "water";
    int m_waitTicks;
    int m_T;
};







//PROTESTORS
class Protestor : public Goodies{
public:
    Protestor(int imageID, int health, int Level);
    virtual void doSomething();
    virtual ~Protestor();
    virtual void Bribed();
    void moveD(Direction D);
    virtual void annoyed(int health);
    void stunned();
    bool TowardTman();
    Direction DtoTman();
    bool isPath(Direction D);
    bool isInter();
    void Turn();
    virtual void setState(bool alive);
    virtual bool getState();
    Direction Random();
    bool freeSpace(int x, int y, Direction d);
    virtual std::string getVal();
private:
    int m_rTick;
    int m_yTick;
    int m_tTick;
    int m_move;
    bool m_giveup;
    bool m_state;
    int m_health;
    int m_level;
    std::string m_value = "prot";
};

//i

class RegProt : public Protestor{
public:
    RegProt(int level);
//    virtual ~RegProt();
};

class HardProt : public Protestor{
public:
    HardProt(int level);
//    virtual ~RegProt();
};

#endif // ACTOR_H_
