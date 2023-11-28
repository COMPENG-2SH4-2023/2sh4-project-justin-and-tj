#include "GameMechs.h"
#include "Definitions.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <iostream>
#include <string>

void Random(objPos *returnObj, int CheckArray[][BOARD_HEIGHT], int min1, int max1, int min2, int max2);

/**
 * @brief Construct a new Game Mechs object
 *
 */
GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    winFlag = false;
    boardSizeX = 10;
    boardSizeY = 10;
}

/**
 * @brief Construct a new Game Mechs object
 *
 * @param boardX Board Width
 * @param boardY Board Height
 */
GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    score = 0;
    exitFlag = false;
    winFlag = false;
    exitFlag = false;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

/**
 * @brief Get the current exitFlag status
 *
 * @return bool exitFlag status
 */
bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

/**
 * @brief Get the current input character
 *
 * @return char Current input
 */
char GameMechs::getInput()
{
    return input;
}

/**
 * @brief Check the winFlag status
 *
 * @return bool winFlag status
 */
bool GameMechs::getWinFlagStatus()
{
    return winFlag;
}

/**
 * @brief Get the board's X Size
 *
 * @return int Board X Dimension
 */
int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

/**
 * @brief Get the board's Y Size
 *
 * @return int Board Y Dimension
 */
int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

/**
 * @brief Set exitFlag to true
 *
 */
void GameMechs::setExitTrue()
{
    exitFlag = true;
}

/**
 * @brief Set winFlag to true
 *
 */
void GameMechs::setWinTrue()
{
    winFlag = true;
}

/**
 * @brief Set the current game input
 *
 * @param this_input Character to save as last input
 */
void GameMechs::setInput(char this_input)
{
    input = this_input;
}

/**
 * @brief Clear the current game input
 *
 */
void GameMechs::clearInput()
{
    input = 0;
}

/**
 * @brief Get the current food position
 *
 * @param returnObj Position containing food location
 */
void GameMechs::getFoodPos(objPos &returnObj)
{
    foodPos.getObjPos(returnObj);
}

/**
 * @brief Set the food position to coordinate
 *
 * @param x X-Coordinate for food
 * @param y Y-Coordinate for food
 * @param symbol Food Symbol
 */
void GameMechs::setFoodPos(int x, int y, char symbol)
{
    foodPos.setObjPos(x, y, symbol);
}

/**
 * @brief Add a number to the game score
 *
 * @param n Ammount to add to score
 */
void GameMechs::addToScore(int n)
{
    score += n;
}

/**
 * @brief Get the current score
 *
 * @return int Score ammount
 */
int GameMechs::getScore()
{
    return score;
}

/**
 * @brief Generate a random food object on any unoccupied gameboard space
 *
 * @param PlayerPositions ArrayList containing the player positions
 */
void GameMechs::generateFood(objPosArrayList &PlayerPositions)
{
    // Create an empty check array
    int CheckArray[BOARD_WIDTH][BOARD_HEIGHT] = {0};

    // Populate check array on the game borders
    for (int j = 0; j < getBoardSizeY(); j++)
    {
        for (int i = 0; i < getBoardSizeX(); i++)
        {
            if (j == 0 || j == getBoardSizeY() - 1 ||
                i == 0 || i == getBoardSizeX() - 1)
            {
                CheckArray[i][j] = 1;
            }
        }
    }

    // Populate check array on the player coordinates
    for (int w = 0; w < PlayerPositions.getSize(); w++)
    {
        objPos playerPos;
        PlayerPositions.getElement(playerPos, w);
        CheckArray[playerPos.x][playerPos.y]++;
    }

    // Recursively generate a random position for the food and set it
    Random(&foodPos, CheckArray, 1, BOARD_WIDTH - 2, 1, BOARD_HEIGHT - 2);
}

/**
 * @brief Helper function to randomly assign a position on the game board
 *
 * @param returnObj Position object to fill with random data
 * @param CheckArray Bit-Vector array to not place a random data piece in
 * @param min1 Minimum for the X
 * @param max1 Maximum for the X
 * @param min2 Minimum for the Y
 * @param max2 Maximum for the Y
 */
void Random(objPos *returnObj, int CheckArray[][BOARD_HEIGHT], int min1, int max1, int min2, int max2)
{
    // Generate two random numbers within range
    int num1 = (rand() % (max1 - min1 - 1)) + min1;
    int num2 = (rand() % (max2 - min2 - 1)) + min2;

    // Check if position is occupied
    if (CheckArray[num1][num2] == 1)
    {
        // Check again for an unoccupied position
        return Random(returnObj, CheckArray, min1, max1, min2, max2);
    }
    else
    {
        // Occupy position and populate found position data
        CheckArray[num1][num2]++;
        returnObj->setObjPos(num1, num2, FOOD_CHAR);
    }
}