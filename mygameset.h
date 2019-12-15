#ifndef MYGAMESET_H
#define MYGAMESET_H
#include "gameset.h"
#include "game.h"


class myGameSet : virtual public GameSet, public Game
{
public:
    void setMap(size_t i, size_t j) override;
    void setGameRole(GameVar::GameRole role) override;
    void setCurrentPlayer(GameVar::Player player) override;
    void setGameIsEnd(bool gameIsEnd) override;
    void setMapCanClick(size_t i, size_t j, bool is) override;
    void setMap(size_t i, size_t j, int v);
    void setCurPoint(GameVar::Point);

    ~myGameSet() override;
    myGameSet();
};

#endif // MYGAMESET_H
