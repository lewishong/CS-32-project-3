#include "Actor.h"
#include "StudentWorld.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    Field f;
    string fieldFile = getFieldFilename();
    string error;
    
    if (f.loadField(fieldFile, error) != Field::LoadResult::load_success)
    {
        setError(fieldFile + " " + error);
        return GWSTATUS_LEVEL_ERROR;
    }
    
    for (int i = 0; i < GRID_MAX; i++)
    {
        for (int j = 0; j < GRID_MAX; j++)
        {
            m_grid[i][j].clear();
        }
    }
    
    Field::FieldItem item;
    for (int i = 0; i < GRID_MAX; i++)
    {
        for (int j = 0; j < GRID_MAX; j++)
        {
            item = f.getContentsOf(j, i);
            if (item == Field::FieldItem::rock)
            {
                m_grid[i][j].push_back(new Pebble(i, j, this));
                
            }
            else if (item == Field::FieldItem::grasshopper)
            {
                m_grid[i][j].push_back(new BabyGrasshopper(i, j, this));
            }
        }
    }
    
    m_ticks = 0;
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    
    m_ticks++;
    list<Actor*>::iterator it;
    
    for (int i = 0; i < GRID_MAX; i++)
    {
        for (int j = 0; j < GRID_MAX; j++)
        {
            if (m_grid[i][j].empty())
                continue;
            for (it = m_grid[i][j].begin(); it != m_grid[i][j].end(); )
            {
                int x = (*it)->getX();
                int y = (*it)->getY();
                if ((*it)->isVisible())
                    (*it)->doSomething();
                int x1 = (*it)->getX();
                int y1 = (*it)->getY();
//                if(x != x1 || y != y1)    // if actor moved
//                {
//                    m_grid[x1][y1].push_back(*it);
//                    delete *it;
//                    it = m_grid[i][j].erase(it);
//                }
//                else
                    it++;
            }
        }
    }
    
    if (m_ticks == 2000)
        return GWSTATUS_NO_WINNER;
    else
        return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it;
    
    for (int i = 0; i < GRID_MAX; i++)
    {
        for (int j = 0; j < GRID_MAX; j++)
        {
            if (m_grid[i][j].empty())
                continue;
            for (it = m_grid[i][j].begin(); it != m_grid[i][j].end(); )
            {
                delete *it;
                it = m_grid[i][j].erase(it);
            }
        }
    }
}

bool StudentWorld::isValidPos(int x, int y)
{
    if (x >= GRID_MAX || x < 0 || y >= GRID_MAX || y < 0)
        return false;
    list<Actor*>::iterator it;
    for (it = m_grid[x][y].begin(); it != m_grid[x][y].end(); it++)
    {
        if (dynamic_cast<Pebble*>(*it) != nullptr)
            return false;
    }
    return true;
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}
