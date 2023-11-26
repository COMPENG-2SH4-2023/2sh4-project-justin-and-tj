#include "objPos.h"
#include <string>

objPos::objPos()
{
    x = 0;
    y = 0;
    symbol = 0; // NULL
}

objPos::objPos(objPos &o)
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

objPos::objPos(int xPos, int yPos, char sym)
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::setObjPos(objPos o)
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::getObjPos(objPos &returnPos)
{
    returnPos.setObjPos(x, y, symbol);
}

char objPos::getSymbol()
{
    return symbol;
}

bool objPos::isPosEqual(const objPos *refPos)
{
    return (refPos->x == x && refPos->y == y);
}

char objPos::getSymbolIfPosEqual(const objPos *refPos)
{
    if (isPosEqual(refPos))
        return getSymbol();
    else
        return 0;
}

std::string objPos::toString()
{
    std::string output = "x: " + std::to_string(x) + "\n" +
                         "y : " + std::to_string(y) + "\n" +
                         "symbol : " + symbol;
    return output;
}