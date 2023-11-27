#include "GameMechs.h"
#include "Definitions.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <iostream>
#include <string>

void Random(objPos *returnObj, int CheckArray[][BOARD_HEIGHT], int min1, int max1, int min2, int max2);

GameMechs::GameMechs()
{
    input = 0;
    score = 0;
    exitFlag = false;
    winFlag = false;
    boardSizeX = 10;
    boardSizeY = 10;
}

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

// do you need a destructor?

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    return input;
}

bool GameMechs::getWinFlagStatus()
{
    return winFlag;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setWinTrue()
{
    winFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::getFoodPos(objPos &returnObj)
{
    foodPos.getObjPos(returnObj);
}

void GameMechs::setFoodPos(int x, int y, char symbol)
{
    foodPos.setObjPos(x, y, symbol);
}

void GameMechs::addToScore(int n)
{
    score += n;
}

int GameMechs::getScore()
{
    return score;
}

void GameMechs::generateFood(objPosArrayList &PlayerPositions)
{
    int CheckArray[BOARD_WIDTH][BOARD_HEIGHT] = {0};
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

    for (int w = 0; w < PlayerPositions.getSize(); w++)
    {
        objPos playerPos;
        PlayerPositions.getElement(playerPos, w);
        CheckArray[playerPos.x][playerPos.y]++;
    }

    Random(&foodPos, CheckArray, 1, BOARD_WIDTH - 2, 1, BOARD_HEIGHT - 2);
}

void Random(objPos *returnObj, int CheckArray[][BOARD_HEIGHT], int min1, int max1, int min2, int max2)
{
    int num1 = (rand() % (max1 - min1 - 1)) + min1;
    int num2 = (rand() % (max2 - min2 - 1)) + min2;

    if (CheckArray[num1][num2] == 1)
    {
        return Random(returnObj, CheckArray, min1, max1, min2, max2);
    }
    else
    {
        CheckArray[num1][num2]++;
        returnObj->setObjPos(num1, num2, FOOD_CHAR);
    }
}