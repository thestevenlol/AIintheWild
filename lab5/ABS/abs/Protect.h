#ifndef PROTECT_H
#define PROTECT_H

#include "Droid.h"
#include "Routine.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>   

class Protect : public Routine
{
public:
    int destX;
    int destY;
    int droidA;  // The attacker/threat
    int droidB;  // The droid to protect

    Protect(int droidA, int droidB, Grid& grid) : Routine(), destX(1), destY(1), droidA(droidA), droidB(droidB)
    {
        // If we get -1 passed in then we will self-select the droids in 'act' below.
        // Otherwise subtract 1 so we map to the correct index (starting at 0).
        if (droidA != -1)
            this->droidA = droidA - 1;
        if (droidB != -1)
            this->droidB = droidB - 1;

        this->routineType = "Protect";
        this->routineGrid = &grid;
    }

    void reset(std::string msg)
    {
        std::cout << ">>> Resetting routine " << routineType << " " << msg << std::endl;
        state = RoutineState::None;
    }

    void act(Droid* droid, Grid& grid)
    {
        // Randomly select droidA/droidB if not pre-specified.
        if (droidA == -1 || droidB == -1)
        {
            selectRandomDroids(droid, grid);
        }

        if (isRunning())
        {
            if (!droid->isAlive() || droid->alarmHasBeenRaised)
            {
                fail();
                return;
            }

            // Compute the intercept position using integer arithmetic.
            computeIntercept(grid);

            // Set the droid's target location.
            droid->target = grid.getGridLocation(destX, destY);

            if (!isDroidAtDestination(droid, grid))
            {
                moveDroid(droid, grid);
            }
            else
            {
                succeed("Protect for " + droid->name);
            }
        }
    }

private:
    // If droid indices are not specified, randomly select two different droids.
    void selectRandomDroids(Droid* currentDroid, Grid& grid)
    {
        static bool seeded = false;
        if (!seeded)
        {
            std::srand(static_cast<unsigned int>(std::time(0)));
            seeded = true;
        }
        int gridSize = grid.m_gridDroids.size();
        if (gridSize < 3) return; // Not enough droids.

        if (droidA == -1)
        {
            do
            {
                droidA = std::rand() % gridSize;
            } while (grid.m_gridDroids[droidA] == currentDroid);
        }
        if (droidB == -1)
        {
            do
            {
                droidB = std::rand() % gridSize;
            } while (grid.m_gridDroids[droidB] == currentDroid || droidB == droidA);
        }
    }

    // Compute an intercept position that lies between droid A and droid B.
    void computeIntercept(Grid& grid)
    {

        // midpoint algorithm = (x1 + x2) / 2, (y1 + y2) / 2

        int droidAx = grid.m_gridDroids[droidA]->x;
        int droidAy = grid.m_gridDroids[droidA]->y;
        int droidBx = grid.m_gridDroids[droidB]->x;
        int droidBy = grid.m_gridDroids[droidB]->y;

        destX = (droidAx + droidBx) / 2; // x1 + x2 / 2
        destY = (droidAy + droidBy) / 2; // y1 + y2 / 2

        // Disallow the protection droid from sitting inside the attacker.
        if (droidBy > droidAy && destY >= droidBy)
            destY = droidBy - 1;
        if (droidBy < droidAy && destY <= droidBy)
            destY = droidBy + 1;
        if (droidBx > droidAx && destX >= droidBx)
            destX = droidBx - 1;
        if (droidBx < droidAx && destX <= droidBx)
            destX = droidBx + 1;

        // clamp the destination to the grid boundaries.
        if (destX < 1) destX = 1;
        if (destY < 1) destY = 1;
        if (destX > grid.gridSize) destX = grid.gridSize;
        if (destY > grid.gridSize) destY = grid.gridSize;

        std::cout << "Droid A at: " << droidAx << ", " << droidAy << std::endl;
        std::cout << "Droid B at: " << droidBx << ", " << droidBy << std::endl;
        std::cout << "Destination: " << destX << ", " << destY << std::endl;
    }

    void moveDroid(Droid* droid, Grid& grid)
    {
        std::cout << ">>> Droid " << droid->name << " moving to " << destX << ", " << destY << std::endl;
        // Check we are within grid boundaries.
        if (destX < 1 || destX > grid.gridSize || destY < 1 || destY > grid.gridSize)
            return;

        // Move one unit at a time towards the target.
        if (droid->target.y != droid->position.y)
        {
            droid->position.y += (droid->target.y > droid->position.y) ? 1 : -1;
        }
        if (droid->target.x != droid->position.x)
        {
            droid->position.x += (droid->target.x > droid->position.x) ? 1 : -1;
        }

        if (isDroidAtDestination(droid, grid))
        {
            succeed("Protect for " + droid->name);
        }
    }

    bool isDroidAtDestination(Droid* droid, Grid& grid)
    {
        sf::Vector2f delta = droid->target - droid->position;
        return (static_cast<int>(grid.length(delta)) == 0);
    }
};

#endif // PROTECT_H
