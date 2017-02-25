#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include "StudentWorld.h"
#include "GameWorld.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction dir, int depth, StudentWorld* world);
    virtual void doSomething() = 0;
    virtual bool isBugBlocker() = 0;
    inline StudentWorld* world() { return m_swptr; }
    virtual ~Actor();
private:
    StudentWorld *m_swptr;
};

class Bug : public Actor
{
public:
    Bug(int imageID, int startX, int startY, Direction dir, StudentWorld *world);
    
    virtual void doSomething() = 0;
   
    inline virtual bool isBugBlocker() { return false; };
    bool isValidPos(int x, int y);
    
    inline bool isAlive() { return m_state; }
    inline void setState(bool state) { m_state = state; }
    
    inline int hitpoints() { return m_hitpoints; }
    inline void setHitPoints(int hp) { m_hitpoints = hp; }
    inline void decHitPoints() { m_hitpoints--; }
    
    inline bool isStunned() { return m_stunned; }
    inline void setStunned (bool status) { m_stunned = status; }
    
    inline int stunnedticks() { return m_stunnedticks; }
    inline void setStunnedTicks(int ticks) { m_stunnedticks = ticks; }
    inline void decStunnedTicks() { m_stunnedticks--; }
    
    virtual ~Bug();
private:
    bool m_state;
    int m_hitpoints;
    bool m_stunned;
    int m_stunnedticks;
};

class Grasshopper : public Bug
{
public:
    Grasshopper(int imageID, int startX, int startY, StudentWorld *world);
    virtual void doSomething() = 0;
    inline int steps() { return m_steps; }
    inline void setSteps(int steps) { m_steps = steps; }
    inline void decSteps() { m_steps--; }
    virtual ~Grasshopper();
private:
    int m_steps;
};

class BabyGrasshopper : public Grasshopper
{
public:
    BabyGrasshopper(int startX, int startY, StudentWorld *world);
    virtual void doSomething();
    virtual ~BabyGrasshopper();
private:
    
};

class Pebble : public Actor
{
public:
    Pebble(int startX, int startY, StudentWorld *world);
    inline virtual void doSomething() { return; }
    inline virtual bool isBugBlocker() { return true; }
    virtual ~Pebble();
private:
    
};



#endif // ACTOR_H_
