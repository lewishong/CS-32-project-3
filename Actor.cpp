#include "Actor.h"
#include "GameController.h"
#include "StudentWorld.h"

// ACTOR

Actor::Actor(int imageID, int startX, int startY, Direction dir, int depth, StudentWorld* world)
:GraphObject(imageID, startX, startY, dir, depth)
{
    setVisible(true);
    m_swptr = world;
}

Actor::~Actor()
{
    setVisible(false);
}

// BUG

Bug::Bug(int imageID, int startX, int startY, Direction dir, StudentWorld *world)
:Actor(imageID, startX, startY, dir, 1, world)
{
    
}

bool Bug::isValidPos(int x, int y)
{
    return world()->isValidPos(x, y);
}

Bug::~Bug()
{
    
}

// GRASSHOPPER

Grasshopper::Grasshopper(int imageID, int startX, int startY, StudentWorld *world)
:Bug(imageID, startX, startY, (Direction)randInt(1, 4), world)
{
    m_steps = randInt(2, 10);
}

Grasshopper::~Grasshopper()
{
    
}

// BABY GRASSHOPPER

BabyGrasshopper::BabyGrasshopper(int startX, int startY, StudentWorld *world)
:Grasshopper(IID_BABY_GRASSHOPPER, startX, startY, world)
{
    setHitPoints(500);
    setStunned(false);
}

void BabyGrasshopper::doSomething()
{
    decHitPoints();
    if (hitpoints() <= 0)
    {
        // TODO: add 100 units food (make function for killing bugs)
        // setState(false);
        return;
    }
    else if (isStunned())
    {
        decStunnedTicks();
        return;
    }
    else
    {
        if (hitpoints() >= 1600)
        {
            // TODO: add adult grasshopper in same position
            // kill baby grasshopper
            return;
        }
        // TODO: eating food case
        // setTicks to 2 and return
        else if (steps() <= 0)
        {
            setDirection((Direction)randInt(1, 4));
            setSteps(randInt(2, 10));
        }
        
        switch(getDirection()){
            case up:
                for (int i = 0; i < steps(); i++)
                {
                    if (isValidPos(getX(), getY() + 1))
                        moveTo(getX(), getY() + 1);
                    else
                    {
                        setSteps(0);
                        setStunnedTicks(2);
                        return;
                    }
                }
                break;
            case down:
                for (int i = 0; i < steps(); i++)
                {
                    if (isValidPos(getX(), getY() - 1))
                        moveTo(getX(), getY() - 1);
                    else
                    {
                        setSteps(0);
                        setStunnedTicks(2);
                        return;
                    }
                }
                break;
            case left:
                for (int i = 0; i < steps(); i++)
                {
                    if (isValidPos(getX() - 1, getY()))
                        moveTo(getX() - 1, getY());
                    else
                    {
                        setSteps(0);
                        setStunnedTicks(2);
                        return;
                    }
                }
                break;
            case right:
                for (int i = 0; i < steps(); i++)
                {
                    if (isValidPos(getX() - 1, getY()))
                        moveTo(getX() + 1, getY());
                    else
                    {
                        setSteps(0);
                        setStunnedTicks(2);
                        return;
                    }
                }
                break;
            default:
                break;
        }
        decSteps();
        setStunnedTicks(2);
    }
}

BabyGrasshopper::~BabyGrasshopper()
{
    
}

// PEBBLE

Pebble::Pebble(int startX, int startY, StudentWorld *world)
:Actor(IID_ROCK, startX, startY, right, 1, world)
{
    
}

Pebble::~Pebble()
{
    
}
