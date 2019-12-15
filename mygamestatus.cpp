#include "mygamestatus.h"
#include <queue>
#include <QDebug>

myGameStatus::myGameStatus()
{
}

GameVar::Player myGameStatus::gameEnd() {
    map = getMap();
    GameVar::Point point = getCurrentPoint();
    if(check(point.getI(), point.getJ()) == true) return getCurrentPlayer();
    for(size_t i = 0; i < 15; ++i) {
        for(size_t j = 0; j < 15; ++j) {
            if(map[i][j] == -1)
                return GameVar::NONE;
        }
    }
    return GameVar::PEACE;
}

myGameStatus::~myGameStatus()
{

}

bool myGameStatus::check(int indexI, int indexJ) {//广搜判断输赢
    map = getMap();
    int tmpXIndex = indexI;
    int tmpYIndex = indexJ;
    int count = 1;
    bool flag = true;
    int*** dir = new int**[4];
    for(int i = 0; i < 4; ++i) {
        dir[i] = new int*[2];
        for(int j = 0; j < 2; ++j) {
            dir[i][j] = new int[2];
        }
    }
    dir[0][0][0] = -1;
    dir[0][0][1] = 0;
    dir[0][1][0] = 1;
    dir[0][1][1] = 0;
    dir[1][0][0] = 0;
    dir[1][0][1] = -1;
    dir[1][1][0] = 0;
    dir[1][1][1] = 1;
    dir[2][0][0] = -1;
    dir[2][0][1] = -1;
    dir[2][1][0] = 1;
    dir[2][1][1] = 1;
    dir[3][0][0] = 1;
    dir[3][0][1] = -1;
    dir[3][1][0] = -1;
    dir[3][1][1] = 1;

    for(int i = 0; i < 4; ++i) {
        count = 1;

        for(int j = 0; j < 2; ++j) {
            flag = true;
            while(flag) {
                tmpXIndex += dir[i][j][0];
                tmpYIndex += dir[i][j][1];
                if(tmpXIndex >= 0 && tmpXIndex < 15 && tmpYIndex >= 0 && tmpYIndex < 15) {
                    if(map[static_cast<size_t>(tmpXIndex)][static_cast<size_t>(tmpYIndex)]
                            == map[static_cast<size_t>(indexI)][static_cast<size_t>(indexJ)]) {
                        count++;
                    } else flag = false;
                } else flag = false;
            }
            tmpXIndex = indexI;
            tmpYIndex = indexJ;

        }
        if(count > 5 && getGameRole() == GameVar::HAVENOHANDS){
            currentPlayer = GameVar::WHITE;
            return true;
        }
        if(count >= 5) return true;
    }
    return false;
}
