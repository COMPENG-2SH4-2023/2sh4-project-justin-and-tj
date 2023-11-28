#include "objPosArrayList.h"
#include <stdexcept>
#include <string>

// Check lecture contents on general purpose array list construction,
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_UNIT_SIZE];
    sizeList = 0;
    sizeArray = ARRAY_UNIT_SIZE;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

/**
 * @brief Increase the current Array List's Array Size by ARRAY_UNIT_SIZE, but not exceeding the ARRAY_MAX_CAP
 *
 */
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

/**
 * @brief Get the current list size
 *
 * @return int Size of list
 */
int objPosArrayList::getSize()
{
    return sizeList;
}

/**
 * @brief Insert a position object at the front of the list
 *
 * @param thisPos Object to insert
 */
void objPosArrayList::insertHead(objPos thisPos)
{
    if (sizeList + 1 >= sizeArray)
    {
        increaseSizeArray();
    }

    for (int i = sizeList - 1; i >= 0; i--)
    {
        aList[i + 1] = aList[i];
    }

    sizeList++;
    aList[0] = thisPos;
}

/**
 * @brief Insert a position object at the end of the list
 *
 * @param thisPos Object to insert
 */
void objPosArrayList::insertTail(objPos thisPos)
{
    if (sizeList + 1 >= sizeArray)
    {
        increaseSizeArray();
    }

    aList[sizeList] = thisPos;
    sizeList++;
}

/**
 * @brief Remove a position object at the front of the list
 *
 */
void objPosArrayList::removeHead()
{
    sizeList -= 1;
    for (int i = 1; i < sizeList; i++)
    {
        aList[i - 1] = aList[i];
    }
}

/**
 * @brief Remove a position object at the end of the list
 *
 */
void objPosArrayList::removeTail()
{
    sizeList -= 1;
}

/**
 * @brief Get the first element in the list
 *
 * @param returnPos Element to populate with head data
 */
void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos = aList[0];
}

/**
 * @brief Get the last element in the list
 *
 * @param returnPos Element to populate with tail data
 */
void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos = aList[sizeList - 1];
}

/**
 * @brief Get an element in the list
 *
 * @param returnPos Position to populate with data
 * @param index Index of position in the list
 */
void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos = aList[index];
}

/**
 * @brief Check to see if element is in current list
 *
 * @param input Element to check
 * @return bool Element's status in this list
 */
bool objPosArrayList::isElement(objPos input)
{
    bool isInArrayList = 0;
    for (int i = 0; i < sizeList; i++)
    {
        objPos test;
        getElement(test, i);
        if (input.isPosEqual(&test))
        {
            isInArrayList = 1;
        }
    }
    return isInArrayList;
}

/**
 * @brief Get a string representation of the current list
 *
 * @return std::string String output of current Array List
 */
std::string objPosArrayList::toString()
{
    std::string output = "";
    output += "Array Length: " + std::to_string(getSize()) + "\n";
    for (int i = 0; i < getSize(); i++)
    {
        output += aList[i].toString();
    }
    return output;
}