#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Definitions.h"
using namespace std;

GameMechs Board1;
Player player = Player(&Board1);

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

    Board1 = GameMechs(BOARD_WIDTH, BOARD_HEIGHT);
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
    cout << total;

    objPos playerHeadPos;
    player.getPlayerHeadPos(playerHeadPos);

    string debug = "";
    debug += "Player Head, x: " + to_string(playerHeadPos.x) + " y: " + to_string(playerHeadPos.y) + " symbol: " + playerHeadPos.symbol + "\n";
    debug += "Player Direction:" + to_string(player.getDirection()) + "\n";
    debug += "Input: ";

    cout << debug << Board1.getInput() << endl;
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();
}
