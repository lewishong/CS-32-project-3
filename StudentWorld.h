#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include "GameConstants.h"
#include "Field.h"
#include <list>
#include <cstdlib>
#include <string>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

const int GRID_MAX = 64;

class Actor;

class StudentWorld : public GameWorld
{
public:
	StudentWorld(string assetDir)
	 : GameWorld(assetDir)
	{
        
	}

    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    bool isValidPos(int x, int y);
    
    virtual ~StudentWorld();

private:
    list<Actor*> m_grid[GRID_MAX][GRID_MAX];
    int m_ticks;
};

#endif // STUDENTWORLD_H_
