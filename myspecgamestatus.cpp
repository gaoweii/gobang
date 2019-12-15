#include "myspecgamestatus.h"

void MySpecGameStatus::rule()
{
    if(this->getGameStep() <= 2) {
        for(size_t i = 0; i < 15; ++i) {
            for(size_t j = 0; j < 15; ++j) {
                if((i < 5 || i >= 10) || (j < 5 || j >= 10))
                    gameSet.setMapCanClick(i, j, false);//前三手规定区域才可点击
            }
        }
    } else if(this->getGameStep() == 3) {
        for(size_t i = 0; i < 15; ++i) {
            for(size_t j = 0; j < 15; ++j) {
                if((i < 5 || i >= 10) || (j < 5 || j >= 10))
                    gameSet.setMapCanClick(i, j, true);
            }
        }
    }
}

GameVar::Player MySpecGameStatus::gameEnd()
{
    return GameVar::NONE;
}

MySpecGameStatus::MySpecGameStatus()
{

}

MySpecGameStatus::~MySpecGameStatus()
{

}


