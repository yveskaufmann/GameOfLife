#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H 1

#define FIELD_STATE_INVALID -1
#define FIELD_STATE_ALIVE 1
#define FIELD_STATE_DEAD 0

class GameOfLifeMap {

public:
    GameOfLifeMap(int width, int height);
    virtual ~GameOfLifeMap();

    int width();
    int height();
    char getFieldState(int x, int y);
    bool nextSimulationStep();

private: 
    bool isInsideMap(int x, int y);

    int mWidth;
    int mHeight;
    char *mFieldMap;
    char *mTmpFieldMap;
};

#endif



