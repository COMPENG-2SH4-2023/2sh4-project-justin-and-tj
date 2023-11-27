#ifndef PLAYER_H
#define PLAYER_H

#include "objPos.h"
#include "objPosArrayList.h"
#include "GameMechs.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

    Player(GameMechs *thisGMRef);
    ~Player();

    void getPlayerPos(objPosArrayList *returnPos); // Upgrade this in iteration 3.
    void getPlayerHeadPos(objPos &returnPos);
    bool isPlayerPos(int x, int y);
    int getDirection();
    void updatePlayerDir();
    void movePlayer();

private:
    objPosArrayList *playerPos;
    enum Dir myDir;

    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;
};

#endif