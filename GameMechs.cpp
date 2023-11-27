#include "GameMechs.h"
#include "Definitions.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <iostream>
#include <string>

void Random(objPosArrayList *ReturnArray, int CheckArray[][BOARD_HEIGHT], int min1, int max1, int min2, int max2);

GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    boardSizeX = 10;
    boardSizeY = 10;
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
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

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

void GameMechs::generateFood(objPosArrayList *FoodPositions, objPosArrayList PlayerPositions, int foodCount)
{
    int RandomNum;
    int CheckArray[BOARD_WIDTH][BOARD_HEIGHT];
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

    for (int i = 0; i < FoodPositions->getSize(); i++)
    {
        FoodPositions->removeTail();
    }
    for (int i = 0; i < foodCount; i++)
    {
        Random(FoodPositions, CheckArray, 1, BOARD_WIDTH - 2, 1, BOARD_HEIGHT - 2);
    }
}

void Random(objPosArrayList *ReturnArray, int CheckArray[][BOARD_HEIGHT], int min1, int max1, int min2, int max2)
{
    int num1 = (rand() % (max1 - min1 - 1)) + min1;
    int num2 = (rand() % (max2 - min2 - 1)) + min2;

    if (CheckArray[num1][num2] == 1)
    {
        return Random(ReturnArray, CheckArray, min1, max1, min2, max2);
    }
    else
    {
        CheckArray[num1][num2]++;
        ReturnArray->insertHead({num1, num2, FOOD_CHAR});
    }
}