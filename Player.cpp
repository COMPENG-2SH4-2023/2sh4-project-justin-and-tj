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

bool Player::isPlayerPos(int x, int y)
{
    for (int i = 0; i < playerPos->getSize(); i++)
    {
        objPos currentPosition;
        playerPos->getElement(currentPosition, i);
        if (currentPosition.x == x && currentPosition.y == y)
        {
            return 1;
        }
    }
    return 0;
}

int Player::getDirection()
{
    return myDir;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char cmd = mainGameMechsRef->getInput();
    if (cmd == 'w' && myDir != DOWN)
    {
        myDir = UP;
    }
    else if (cmd == 'd' && myDir != LEFT)
    {
        myDir = RIGHT;
    }
    else if (cmd == 'a' && myDir != RIGHT)
    {
        myDir = LEFT;
    }
    else if (cmd == 's' && myDir != UP)
    {
        myDir = DOWN;
    }
}

void Player::movePlayer()
{
    objPos currentPos;
    getPlayerPos(currentPos);
    // PPA3 Finite State Machine logic
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();
    switch (myDir)
    {
    case STOP:
        break;
    case UP:

        if (currentPos.y - 1 == 0)
        {
            currentPos.y = boardY - 2;
        }
        else
        {
            currentPos.y -= 1;
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case DOWN:
        if (currentPos.y + 1 == boardY - 1)
        {
            currentPos.y = 1;
        }
        else
        {
            currentPos.y += 1;
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case LEFT:
        if (currentPos.x - 1 == 0)
        {
            currentPos.x = boardX - 2;
        }
        else
        {
            currentPos.x -= 1;
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case RIGHT:
        if (currentPos.x + 1 == boardX - 1)
        {
            currentPos.x = 1;
        }
        else
        {
            currentPos.x += 1;
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    }
}