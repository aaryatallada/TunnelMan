#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_
#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <vector>
#include <string>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
//class Earth;
//class TunnelMan;
//class Goodies;
//class Nugget;ige

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
//		: GameWorld(assetDir)
//	{
//	}
    ~StudentWorld();
    virtual int init();
//	{
//		return GWSTATUS_CONTINUE_GAME;
//	}

    virtual int move();
//	{
//		// This code is here merely to allow the game to build, run, and terminate after you hit enter a few times.
//		// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
//		decLives();
//		return GWSTATUS_CONTINUE_GAME;
//	}

    virtual void cleanUp();
    TunnelMan* getTunnelMan();
    void setDisplayText();
    bool isBoulderAt(int x, int y) const;
    bool hasEarth(int x, int y) const;
    void addGoodie(Goodies* goodie);
    void illuminate(int x, int y);
    void dropNug(int x, int y);
    int getOilLeft();
    void ProtDead();
    void ProtGiveUp(Protestor* prot);
    bool isBoulderWithinRange(int x, int y);
    bool validMove(int x, int y, GraphObject::Direction dir);
    //void resetGame();

private:
    Earth* m_Earth[64][64];
    TunnelMan* m_TunnelMan;
    std::vector<Goodies*> m_goodies;
    int m_dfs[64][64];
    struct Grid {
        int x;
        int y;
        Grid(int a, int b): x(a),y(b){}
    };
};

#endif // STUDENTWORLD_H_
