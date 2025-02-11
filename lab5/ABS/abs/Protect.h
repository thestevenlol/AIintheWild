#ifndef PROTECT_H
#define PROTECT_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cmath>        // std::abs

//
// This behaviour picks 2 other droids - A and B.
// It then tries to position itself between A and B.
// In effect it protects B from A by intercepting.
//
class Protect : public Routine
{
public:
    int destX;
    int destY;
    sf::Vector2f target;
    int droidA;  // The attacker/threat
    int droidB;  // The droid to protect

    Protect(int droidA, int droidB, Grid& g) : Routine()
    {
        this->destX = 1;
        this->destY = 1;
        this->target = g.getGridLocation(destX, destY);
        this->routineType = "Protect";
        this->routineGrid = &g;

        // If we get -1 passed in then we will self select the droids in 'Act' below
        // Otherwise subtract 1 so we map to the correct index which starts at 0
        this->droidA = droidA;
        this->droidB = droidB;
        if (droidA != -1) this->droidA = droidA - 1;
        if (droidB != -1) this->droidB = droidB - 1;
    }

    void reset(string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        int droidAx;
        int droidAy;
        int droidBx;
        int droidBy;

        // First time we enter we must set the two target droids if they weren't specified
        if (droidA == -1 || droidB == -1)
        {
            srand(time(0));
            int r = 0;
            while (droidA == -1)
            {
                r = (rand() % (int)grid.m_gridDroids.size()-1) + 1;
                if (grid.m_gridDroids[r] != droid)
                {
                    droidA = r;
                }
            }
            while (droidB == -1)
            {
                r = (rand() % (int)grid.m_gridDroids.size() - 1) + 1;
                if (grid.m_gridDroids[r] != droid && r != droidA)
                {
                    droidB = r;
                }
            }
        }

        if (isRunning())
        {
            if (!droid->isAlive() || droid->alarmHasBeenRaised)
            {
                fail();
                return;
            }

            droidAx = grid.m_gridDroids[droidA]->x;
            droidAy = grid.m_gridDroids[droidA]->y;
            droidBx = grid.m_gridDroids[droidB]->x;
            droidBy = grid.m_gridDroids[droidB]->y;

            // Calculate the midpoint between droids A and B
            sf::Vector2f AB = sf::Vector2f(droidBx-droidAx, droidBy-droidAy);
            sf::Vector2f midpoint = sf::Vector2f(droidAx + AB.x * 0.5f, droidAy + AB.y * 0.5f);
            
            // Set destination to the calculated midpoint
            destX = round(midpoint.x);
            destY = round(midpoint.y);

            // Ensure we stay within grid boundaries
            if (destX < 1) destX = 1;
            if (destY < 1) destY = 1;
            if (destX > grid.gridSize) destX = grid.gridSize;
            if (destY > grid.gridSize) destY = grid.gridSize;

            droid->target = grid.getGridLocation(destX, destY);
            
            if (!isDroidAtDestination(droid, grid)) {
                moveDroid(droid, grid);
            }
            else {
                succeed("Protect for " + droid->name);
            }
        }
    }
    
    void moveDroid(Droid* droid, Grid& grid)
    {
        std::cout << ">>> Droid " << droid->name << " moving to " << destX << ", " << destY << std::endl;
        // Check are we going out of the Grid
        if (destX < 1 || destX > grid.gridSize || destY < 1 || destY > grid.gridSize)
            return;

        sf::Vector2f direction = droid->target - droid->position;
        if (std::abs(grid.length(direction)) > 0)
        {
            if (droid->target.y != droid->position.y)
            {
                if (droid->target.y > droid->position.y)
                {
                    droid->position.y = droid->position.y + 1;
                }
                else {
                    droid->position.y = droid->position.y - 1;
                }
            }
            if (droid->target.x != droid->position.x)
            {
                if (droid->target.x > droid->position.x)
                {
                    droid->position.x = droid->position.x + 1;
                }
                else {
                    droid->position.x = droid->position.x - 1;
                }
            }
        }

        if (isDroidAtDestination(droid, grid)) {
            succeed("Protect for " + droid->name);
        }
    }

    bool isDroidAtDestination(Droid* droid, Grid& grid)
    {
        sf::Vector2f direction = droid->target - droid->position;
        return ((int)grid.length(direction) == 0);
    }
};
#endif