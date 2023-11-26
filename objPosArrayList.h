#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200
#define ARRAY_UNIT_SIZE 5

#include "objPos.h"

class objPosArrayList
{
private:
    objPos *aList;
    int sizeList;
    int sizeArray;

    void increaseSizeArray();

public:
    objPosArrayList();
    ~objPosArrayList();

    int getSize();
    void insertHead(objPos thisPos);
    void insertTail(objPos thisPos);
    void removeHead();
    void removeTail();

    void getHeadElement(objPos &returnPos);
    void getTailElement(objPos &returnPos);
    void getElement(objPos &returnPos, int index);
};

#endif