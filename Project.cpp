#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;
GameMechs Board1;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (exitFlag == false)
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

    Board1 = GameMechs(20, 10);
    exitFlag = false;
}

void GetInput(void)
{
}

void RunLogic(void)
{
}

void DrawScreen(void)
{
    string total;

    for (int j = 0; j < Board1.getBoardSizeY(); j++)
    {
        for (int i = 0; i < Board1.getBoardSizeX() + 2; i++)
        {
            if ( j == 0 || j == Board1.getBoardSizeY() - 1)
            {
                total += "#";
            }
            else if (i == 0 || i == Board1.getBoardSizeX() - 1)
            {
                total += "#";
            }
            else if (i == Board1.getBoardSizeX() + 1)
            {
                total += "\n";
            }
            else
            {
                total += " ";
            }
        }
        
    }
    cout << total << endl;
    MacUILib_clearScreen();
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
