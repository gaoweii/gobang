#ifndef GAMESET_H
#define GAMESET_H
#include "game.h"


class GameSet
{
public:
    virtual void setCurrentPlayer(GameVar::Player) = 0;
    virtual void setGameRole(GameVar::GameRole) = 0;
    virtual void setMap(size_t i, size_t j) = 0;
    virtual void setGameIsEnd(bool gameIsEnd) = 0;
    virtual void setMapCanClick(size_t i, size_t j, bool is) = 0;
    virtual ~GameSet(){}
};

#endif // GAMESET_H
