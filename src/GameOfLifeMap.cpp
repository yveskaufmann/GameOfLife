#include "GameOfLifeMap.h"
#include <assert.h>
#include <algorithm>
#include <iostream>  
#include <stdlib.h> 
#include <time.h> 


static const int NEIGHBOR_DIRECTIONS [8][2] = {
    {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1},{-1, 0}, {-1, 1}
};

GameOfLifeMap::GameOfLifeMap(int width, int height) : mWidth(width), mHeight(height), 
    mFieldMapSize(width * height), mFieldMap(nullptr), mTmpFieldMap(nullptr)
{   

    mFieldMap = (char*) calloc(mFieldMapSize, sizeof(char));
    mTmpFieldMap = (char*) calloc(mFieldMapSize, sizeof(char));
    generate();
    
}

GameOfLifeMap::~GameOfLifeMap() 
{
    this->release();
}

void GameOfLifeMap::generate() {
    srand ((time(NULL) + rand()) % 0x7FFFFF);
    for(int i = 0; i < mFieldMapSize; i++) {
        mTmpFieldMap[i] = FIELD_STATE_DEAD;
        // estimates the  40% alive chance
        mFieldMap[i] = (rand() % 101) > 40; 
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

void GameOfLifeMap::toggleFieldState(int x, int y) {
    char state = getFieldState(x, y);
    
    switch(state) {
        case FIELD_STATE_ALIVE:
            state = FIELD_STATE_DEAD;
            break;
        case FIELD_STATE_DEAD:
            state = FIELD_STATE_ALIVE;
            break;
        case FIELD_STATE_INVALID:
            return;
            break;
    }
    
    setFieldState(x, y, state);
}

void GameOfLifeMap::setFieldState(int x, int y, char state) {
    assert (state == FIELD_STATE_ALIVE || state == FIELD_STATE_DEAD);
    if (isInsideMap(x, y)) {
        mFieldMap[x + y * mWidth] = state;
    }
}

bool GameOfLifeMap::nextSimulationStep() 
{
    bool anyChanges = false;
    int livingNeighbors = 0;
    int neighbor_x;
    int neighbor_y;
    char activeState;
    
    for (auto y = 0; y < mHeight; y++) {
        for (auto x = 0; x < mWidth; x++) {
             livingNeighbors = 0;
             for (auto i = 0; i < 8; i++) {
                 neighbor_x = x + NEIGHBOR_DIRECTIONS[i][0];
                 neighbor_y = y + NEIGHBOR_DIRECTIONS[i][1];
                
                if (getFieldState(neighbor_x, neighbor_y) == FIELD_STATE_ALIVE) {
                    livingNeighbors++;
                }
             }

            activeState = getFieldState(x, y);
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

void GameOfLifeMap::release() {
    if (mFieldMap != nullptr) {
        free(mFieldMap);
        mFieldMap = nullptr;
    }

    if (mTmpFieldMap != nullptr) {
        free(mTmpFieldMap);
        mTmpFieldMap = nullptr;
    }
}