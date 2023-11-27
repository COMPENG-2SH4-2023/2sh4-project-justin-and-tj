#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Definitions.h"
using namespace std;

GameMechs Board1;
Player player = Player(&Board1);
string debugMessages = "";

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (Board1.getExitFlagStatus() == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    srand(time(NULL));

    Board1 = GameMechs(BOARD_WIDTH, BOARD_HEIGHT);

    objPosArrayList playerPos;
    player.getPlayerPos(playerPos);
    Board1.generateFood(playerPos);
}

void GetInput(void)
{
    char cmd;
    if (MacUILib_hasChar())
    {
        cmd = MacUILib_getChar();
        if (cmd >= 32 && cmd <= 126)
        {
            Board1.setInput(cmd);
        }
        else
        {
            Board1.setInput(0);
        }
    }
}

void RunLogic(void)
{
    player.updatePlayerDir();
    player.movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    string total;

    objPos foodPos;
    Board1.getFoodPos(foodPos);
    for (int j = 0; j < Board1.getBoardSizeY(); j++)
    {
        for (int i = 0; i < Board1.getBoardSizeX() + 1; i++)
        {
            if (i == Board1.getBoardSizeX())
            {
                total += "\n";
            }
            else if (player.isPlayerPos(i, j))
            {
                objPos currentPos;
                player.getPlayerHeadPos(currentPos);
                total += currentPos.symbol;
            }
            else if (foodPos.isPosEqual(i, j))
            {
                total += FOOD_CHAR;
            }
            else if (j == 0 || j == Board1.getBoardSizeY() - 1 ||
                     i == 0 || i == Board1.getBoardSizeX() - 1)
            {
                total += "#";
            }
            else
            {
                total += " ";
            }
        }
    }
    total += "\n****SNAKE GAME****\nBoard Size: " +
             to_string(Board1.getBoardSizeX()) + " by " + to_string(Board1.getBoardSizeY()) + "\n" +
             "Score\t\t  " + to_string(Board1.getScore()) + "\n\n" +
             "****INSTRUCTIONS****\n Use \"W\", \"A\", \"S\", \"D\" to move the snake around.\n" +
             " Aim for the " + (char)FOOD_CHAR + " to grow your snake longer.\n" +
             " See how long you can get the snake before you run into yourself!";
    cout << total;

    if (DEBUG_FLAG)
    {
        objPos playerHeadPos;
        objPosArrayList playerPositions;
        player.getPlayerHeadPos(playerHeadPos);
        player.getPlayerPos(playerPositions);
        string debug = "\n****DEBUG****\n" + debugMessages + "\n";
        debug += playerPositions.toString();
        debug += "Player Direction: " + to_string(player.getDirection()) + "\n";
        debug += "Food Position\t  " + foodPos.toString();
        debug += "Input: ";

        cout << debug << Board1.getInput() << endl;
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();
    if (Board1.getWinFlagStatus())
    {
        cout << "Your final score was " << to_string(Board1.getScore()) << endl
             << "on a " << to_string(Board1.getBoardSizeX()) << " by " << to_string(Board1.getBoardSizeY()) << " Game Board" << endl;
    }
    else
    {
        cout << "Game Interrupted. Come back again soon!" << endl;
    }
    MacUILib_uninit();
}