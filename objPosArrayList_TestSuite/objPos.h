#ifndef OBJPOS_H
#define OBJPOS_H
#include <string>
class objPos
{
public:
    int x;
    int y;
    char symbol;

    objPos();
    objPos(objPos &o); // copy constructor
    objPos(int xPos, int yPos, char sym);

    void setObjPos(objPos o);
    void setObjPos(int xPos, int yPos, char sym);
    void getObjPos(objPos &returnPos);
    char getSymbol();

    bool isPosEqual(const objPos *refPos);
    bool isPosEqual(int x1, int y1);

    char getSymbolIfPosEqual(const objPos *refPos);

    std::string toString();
};

#endif