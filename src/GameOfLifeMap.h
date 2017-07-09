#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H 1

#define FIELD_STATE_INVALID -1
#define FIELD_STATE_ALIVE 1
#define FIELD_STATE_DEAD 0

#include "IDisposable.h"

class GameOfLifeMap : public IDisposable {

public:
    GameOfLifeMap(int width, int height);
    virtual ~GameOfLifeMap();

    void generate();
    int width();
    int height();
    char getFieldState(int x, int y);
    void setFieldState(int x, int y, char state); 
    void toggleFieldState(int x, int y);
    bool nextSimulationStep();
    
    virtual void release();

private: 
    bool isInsideMap(int x, int y);

    int mWidth;
    int mHeight;
    int mFieldMapSize;
    char *mFieldMap;
    char *mTmpFieldMap;
};

#endif



