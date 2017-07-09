#include "GameOfLifeMap.h"
#include <algorithm>
#include <iostream>  
#include <stdlib.h> 
#include <time.h> 


static const int NEIGHBOR_DIRECTIONS [8][2] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1},{-1, 0}, {-1, 1}
};

GameOfLifeMap::GameOfLifeMap(int width, int height) : mWidth(width), mHeight(height), mFieldMap(nullptr), mTmpFieldMap(nullptr)
{   
    srand (time(NULL));
    const size_t mapSize = height * width;
    mTmpFieldMap = (char*) calloc(mapSize, sizeof(char));
    mFieldMap = (char*) calloc(mapSize, sizeof(char));
    for(int i = 0; i < mapSize; i++) {
        mFieldMap[i] = (rand() % 101) > 60; // 40% alive chance
    }
}

GameOfLifeMap::~GameOfLifeMap() 
{
    if (mFieldMap != nullptr) {
        free(mFieldMap);
        mFieldMap = nullptr;
    }

    if (mTmpFieldMap != nullptr) {
        free(mTmpFieldMap);
    }
}

int GameOfLifeMap::width() 
{
    return mWidth;
}

int GameOfLifeMap::height() 
{
    return mHeight;
}

char GameOfLifeMap::getFieldState(int x, int y) 
{   
    if (isInsideMap(x, y)) {
        return mFieldMap[x + y * mWidth];
    }

    return FIELD_STATE_INVALID;
}

bool GameOfLifeMap::nextSimulationStep() 
{
    bool anyChanges = false;
    int livingNeighbors = 0;
    int neighbor_x;
    int neighbor_y;
    int activeState;

    for (int y = 0; y < mHeight; y++) {
        for (int x = 0; x < mWidth; x++) {
             livingNeighbors = 0;
             for (int i = 0; i < 8; i++) {
                 neighbor_x = x + NEIGHBOR_DIRECTIONS[i][0];
                 neighbor_y = y + NEIGHBOR_DIRECTIONS[i][1];
                
                if (getFieldState(neighbor_x, neighbor_y)) {
                    livingNeighbors++;
                }
             }

            char activeState = getFieldState(x, y);
            if (activeState == FIELD_STATE_ALIVE) {
                if (livingNeighbors < 2 || livingNeighbors > 3 ) {
                    activeState = FIELD_STATE_DEAD;
                    anyChanges = true;
                }
            } else if (livingNeighbors == 3) {
                activeState = FIELD_STATE_ALIVE;
                anyChanges = true;
            }
             
             
             mTmpFieldMap[y * mWidth + x] = activeState;
        }
    }

    std::swap(mFieldMap, mTmpFieldMap);
    return anyChanges;
}

bool GameOfLifeMap::isInsideMap(int x, int y) {
    return x >= 0 && x < mWidth && y > 0 && y < mHeight;
}
