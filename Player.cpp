#include "Player.h"
#include "objPosArrayList.h"

Player::Player(GameMechs *thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos = new objPosArrayList();

    playerPos->insertHead(objPos(1, 1, '@'));
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
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    switch (myDir)
    {
    case STOP:
        break;
    case UP:
        objPos currentPos;
        playerPos->getHeadElement(currentPos);
        currentPos.y -= 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case DOWN:
        objPos currentPos;
        playerPos->getHeadElement(currentPos);
        currentPos.y += 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case LEFT:
        objPos currentPos;
        playerPos->getHeadElement(currentPos);
        currentPos.x -= 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case RIGHT:
        objPos currentPos;
        playerPos->getHeadElement(currentPos);
        currentPos.x += 1;
        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    }
}