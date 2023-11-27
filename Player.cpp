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

void Player::getPlayerPos(objPosArrayList *returnPos)
{
    // return the reference to the playerPos array list
    returnPos = playerPos;
}

void Player::getPlayerHeadPos(objPos &returnPos)
{
    // return the reference to the head of the playerPos array list
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
    else if (cmd == 32)
    {
        mainGameMechsRef->setExitTrue();
    }
}

void Player::movePlayer()
{
    objPos currentPos;
    getPlayerHeadPos(currentPos);
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

            if (playerPos->isElement({currentPos.x, boardY - 2, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.y = boardY - 2;
            }
        }
        else
        {
            if (playerPos->isElement({currentPos.x, currentPos.y - 1, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.y -= 1;
            }
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case DOWN:
        if (currentPos.y + 1 == boardY - 1)
        {
            if (playerPos->isElement({currentPos.x, 1, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.y = 1;
            }
        }
        else
        {
            if (playerPos->isElement({currentPos.x, currentPos.y + 1, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.y += 1;
            }
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case LEFT:
        if (currentPos.x - 1 == 0)
        {
            if (playerPos->isElement({boardX - 2, currentPos.y, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.x = boardX - 2;
            }
        }
        else
        {
            if (playerPos->isElement({currentPos.x - 1, currentPos.y, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.x -= 1;
            }
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    case RIGHT:
        if (currentPos.x + 1 == boardX - 1)
        {
            if (playerPos->isElement({1, currentPos.y, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.x = 1;
            }
        }
        else
        {
            if (playerPos->isElement({currentPos.x + 1, currentPos.y, '@'}))
            {
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.x += 1;
            }
        }

        playerPos->insertHead(currentPos);
        playerPos->removeTail();
        break;
    }
}