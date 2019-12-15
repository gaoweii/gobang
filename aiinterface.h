#ifndef AIINTERFACE_H
#define AIINTERFACE_H
#include "game.h"

typedef GameVar::Point curPoint;

class AIinterface : public Game
{
public:
    virtual curPoint getCurrentChessDownPoint() = 0;
    virtual ~AIinterface() {};
    AIinterface();
};

#endif // AIINTERFACE_H
