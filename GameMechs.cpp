#include "GameMechs.h"
#include "Definitions.h"
#include "Player.h"
#include "objPosArrayList.h"
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

objPosArrayList GameMechs::generateFood(Player *player)
{
    int RandomNum;
    int CheckArray[BOARD_WIDTH][BOARD_HEIGHT];
    for (int j = 0; j < getBoardSizeY(); j++)
    {
        for (int i = 0; i < getBoardSizeX(); i++)
        {
            if (j == 0 || j == Board1.getBoardSizeY() - 1 ||
                i == 0 || i == Board1.getBoardSizeX() - 1)
            {
                CheckArray[i][j] = 1;
            }
        }
    }

    objPosArrayList PlayerPositions;
    player->getPlayerPos(PlayerPositions);
    PlayerPositions.getSize();

    for (int w = 0; w < PlayerPositions.getSize(); w++)
    {
        objPos playerPos;
        PlayerPositions.getElement(playerPos, w);
        CheckArray[PlayerPos.x][PlayerPos.y] = 1;
    }

    objPosArrayList FoodPositions;
}

void Random(objPosArrayList ReturnArray, int CheckArray[][BOARD_HEIGHT], int min, int max)
{
    int num1 = (rand() % (max - min - 1)) + min;
    int num2 = (rand() % (max - min - 1)) + min;

    if (CheckArray[num1][num2] == 1)
    {
        Random(ReturnArray, CheckArray, min, max);
    }
    else
    {
        CheckArray[num1][num2]++;
        ReturnArray.insertHead({num1, num2, FOOD_CHAR});
    }
}