#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include "game.h"


class GameStatus
{
public:
    virtual GameVar::Player gameEnd() = 0;
    virtual ~GameStatus(){}
};

#endif // GAMESTATUS_H
