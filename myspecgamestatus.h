#ifndef MYSPECGAMESTATUS_H
#define MYSPECGAMESTATUS_H
#include "specgamestatus.h"
#include "game.h"
#include "mygamestatus.h"
#include "mygameset.h"
#include <stack>
#include <vector>


class MySpecGameStatus : public SpecGameStatus, public Game
{
public:
    void rule() override;
    GameVar::Player gameEnd() override;
    MySpecGameStatus();
    ~MySpecGameStatus() override;

private:
    myGameSet gameSet;
    bool change = false;

};

#endif // MYSPECGAMESTATUS_H
