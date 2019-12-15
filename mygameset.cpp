#include "mygameset.h"
#include <QDebug>

myGameSet::myGameSet()
{
}

myGameSet::~myGameSet(){}

void myGameSet::setMap(size_t i, size_t j) {
    if(currentPlayer == GameVar::WHITE) map[i][j] = 1;
    else if(currentPlayer == GameVar::BLACK) map[i][j] = 0;
    currentPoint.i = i;
    currentPoint.j = j;
}

void myGameSet::setGameRole(GameVar::GameRole role) {
    gameRole = role;
}

void myGameSet::setCurrentPlayer(GameVar::Player player) {
    currentPlayer = player;
}

void myGameSet::setGameIsEnd(bool gameIsEnd) { this->gameIsEnd = gameIsEnd; }

void myGameSet::setMapCanClick(size_t i, size_t j, bool is)
{
   if(is == false) {
       map[i][j] = 2;
   }
   else {
       map[i][j] = -1;
   }
}

void myGameSet::setMap(size_t i, size_t j, int v)
{
    map[i][j] = v;
}

void myGameSet::setCurPoint(GameVar::Point point)
{
    currentPoint = point;
}
