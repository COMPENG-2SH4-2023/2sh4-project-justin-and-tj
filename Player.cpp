#include "Player.h"
#include "objPosArrayList.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos = new objPosArrayList();

    playerPos->insertHead({1, 1, '@'});
    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
    delete[] playerPos;
}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos array list
    playerPos->getHeadElement(returnPos);
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    if (mainGameMechsRef->getInput() == 'w' && myDir != DOWN)
    {
        myDir = UP;
    }
    else if (mainGameMechsRef->getInput() == 'd' && myDir != LEFT)
    {
        myDir = RIGHT;
    }
    else if (mainGameMechsRef->getInput() == 'a'  && myDir != RIGHT)
    {
        myDir = LEFT;
    }
    else if (mainGameMechsRef->getInput() == 's' && myDir != UP)
    {
        myDir = DOWN;
    }
}

void Player::movePlayer()
{
    objPos currentPos;
    getPlayerPos(currentPos);
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case STOP:
        break;
    case UP:
        currentPos.y -= 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case DOWN:
        currentPos.y += 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case LEFT:
        currentPos.x -= 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case RIGHT:
        currentPos.x += 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    }
}