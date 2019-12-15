#ifndef SPECGAMESTATUS_H
#define SPECGAMESTATUS_H
#include "gamestatus.h"



class SpecGameStatus : virtual public GameStatus
{
public:
    virtual GameVar::Player gameEnd() = 0;
    virtual GameVar::Point ifBreak(){ return GameVar::Point(); }
    virtual void rule() = 0;
    SpecGameStatus();
    virtual ~SpecGameStatus() {}
};

#endif // SPECGAMESTATUS_H
