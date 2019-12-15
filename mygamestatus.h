#ifndef MYGAMESTATUS_H
#define MYGAMESTATUS_H
#include "gamestatus.h"
#include "game.h"


class myGameStatus : virtual public GameStatus, public Game
{
private:
    bool check(int indexI, int indexJ);
    vector<vector<int>> map;
public:
    GameVar::Player gameEnd() override;
    ~myGameStatus() override;
    myGameStatus();
};

#endif // MYGAMESTATUS_H
