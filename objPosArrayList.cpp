#include "objPosArrayList.h"
#include <stdexcept>
#include <string>

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP];
    sizeList = 0;
    sizeArray = ARRAY_MAX_CAP;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

void objPosArrayList::increaseSizeArray()
{
    if (sizeArray + ARRAY_UNIT_SIZE <= ARRAY_MAX_CAP)
    {
        objPos *newList = new objPos[sizeArray + ARRAY_UNIT_SIZE];
        sizeArray += ARRAY_UNIT_SIZE;

        for (int i = 0; i < sizeList; i++)
            newList[i] = aList[i];

        delete[] aList;

        aList = newList;
    }
    else
    {
        throw std::overflow_error("ArrayList is too large to store");
    }
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList + 1 >= sizeArray)
    {
        increaseSizeArray();
    }

    for (int i = 0; i < sizeList; i++)
    {
        aList[i + 1] = aList[i];
    }

    sizeList++;
    aList[0] = thisPos;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList + 1 >= sizeArray)
    {
        increaseSizeArray();
    }

    aList[sizeList] = thisPos;
    sizeList++;
}

void objPosArrayList::removeHead()
{
    sizeList -= 1;
    for (int i = 1; i < sizeList; i++)
    {
        aList[i - 1] = aList[i];
    }
}

void objPosArrayList::removeTail()
{
    sizeList -= 1;
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos = aList[0];
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos = aList[sizeList - 1];
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos = aList[index];
}

std::string objPosArrayList::toString()
{
    std::string output = "";
    output += "Array Length: " + std::to_string(getSize()) + "\n";
    for (int i = 0; i < getSize(); i++)
    {
        output += aList[i].toString() + "\n";
    }
    return output;
}