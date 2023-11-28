#include "Player.h"
#include "objPosArrayList.h"

/**
 * @brief Construct a new Player object
 *
 * @param thisGMRef Game Mechanics reference for game board interactions
 */
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
    delete playerPos;
}

/**
 * @brief Get the ArrayList containing the player's position data
 *
 * @param returnPos ArrayList containing a copy of the current player position objects
 */
void Player::getPlayerPos(objPosArrayList &returnPos)
{
    // Empty incoming Array List
    for (int i = 0; i < returnPos.getSize(); i++)
        returnPos.removeHead();

    // Populate with position data from this Array List
    for (int i = 0; i < playerPos->getSize(); i++)
    {
        objPos currentEl;
        playerPos->getElement(currentEl, i);
        returnPos.insertHead(currentEl);
    }
}

/**
 * @brief Get the position of the player's head element
 *
 * @param returnPos Position that will contain head element
 */
void Player::getPlayerHeadPos(objPos &returnPos)
{
    playerPos->getHeadElement(returnPos);
}

/**
 * @brief Check if coordinate is occupied by this player
 *
 * @param x X-Coordinate to check
 * @param y Y-Coordiante to check
 * @return true if coordinate is occupied by player
 * @return false if coordinate is not occupied by player
 */
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

/**
 * @brief Get a player's direction
 *
 * @return int Current Direction based on the Dir Enumeration
 */
int Player::getDirection()
{
    return myDir;
}

/**
 * @brief Update the current player's direction based on user input
 *
 */
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
    // Escape case to close game before completion
    else if (cmd == 32)
    {
        mainGameMechsRef->setExitTrue();
    }
}

/**
 * @brief Move the player one step based on the current direction
 *
 */
void Player::movePlayer()
{
    // Get the current head and food positions
    objPos currentPos;
    objPos foodPos;
    getPlayerHeadPos(currentPos);
    mainGameMechsRef->getFoodPos(foodPos);

    // PPA3 Finite State Machine logic
    // Get game board dimensions
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    switch (myDir)
    {
    case STOP:
        break;
    case UP:
        // Wrap-Around logic case
        if (currentPos.y - 1 == 0)
        {
            // Check for self-collision in wrap-around case
            if (playerPos->isElement({currentPos.x, boardY - 2, '@'}))
            {
                // Mark game as complete and finish loop
                mainGameMechsRef->setWinTrue();
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.y = boardY - 2;
            }
        }
        else
        {
            // Check for self-collision in normal case
            if (playerPos->isElement({currentPos.x, currentPos.y - 1, '@'}))
            {
                // Mark game as complete and finish loop
                mainGameMechsRef->setWinTrue();
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.y -= 1;
            }
        }

        // Insert new position to the front of the playerPositions
        playerPos->insertHead(currentPos);

        // Check for non-food case
        if (!playerPos->isElement(foodPos))
        {
            // Remove last playerPosition to make the snake appear like it is moving
            playerPos->removeTail();
        }
        // For the previous section, we want to "move" the snake if there's no food, and if there is food we leave the last element
        // and have the snake grow longer by one.

        // The structure is identical for all the other cases, just with varying wrap-around and movement positions
        break;
    case DOWN:
        if (currentPos.y + 1 == boardY - 1)
        {
            if (playerPos->isElement({currentPos.x, 1, '@'}))
            {
                mainGameMechsRef->setWinTrue();
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
                mainGameMechsRef->setWinTrue();
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.y += 1;
            }
        }

        playerPos->insertHead(currentPos);

        if (!playerPos->isElement(foodPos))
        {
            playerPos->removeTail();
        }
        break;
    case LEFT:
        if (currentPos.x - 1 == 0)
        {
            if (playerPos->isElement({boardX - 2, currentPos.y, '@'}))
            {
                mainGameMechsRef->setWinTrue();
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
                mainGameMechsRef->setWinTrue();
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.x -= 1;
            }
        }

        playerPos->insertHead(currentPos);
        if (!playerPos->isElement(foodPos))
        {
            playerPos->removeTail();
        }
        break;
    case RIGHT:
        if (currentPos.x + 1 == boardX - 1)
        {
            if (playerPos->isElement({1, currentPos.y, '@'}))
            {
                mainGameMechsRef->setWinTrue();
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
                mainGameMechsRef->setWinTrue();
                mainGameMechsRef->setExitTrue();
            }
            else
            {
                currentPos.x += 1;
            }
        }

        playerPos->insertHead(currentPos);
        if (!playerPos->isElement(foodPos))
        {
            playerPos->removeTail();
        }
        break;
    }

    // Refresh food positions and award points if the player moved onto a food object
    if (playerPos->isElement(foodPos))
    {
        objPosArrayList playerPositions;
        getPlayerPos(playerPositions);
        mainGameMechsRef->addToScore(1);
        mainGameMechsRef->generateFood(playerPositions);
    }
}