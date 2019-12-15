#include "haveforbidden.h"
#include "buttonStyleSheet.h"
#include <QPushButton>
#include <QMessageBox>
#include <stack>
#include <QDebug>
#include <algorithm>

HaveForbidden::HaveForbidden(QButtonGroup *group)
{
    this->group = group;
}

bool HaveForbidden::getBook()
{

}

void HaveForbidden::setTimer(QTimer *value)
{
    timer = value;
}

void HaveForbidden::setRemainTime(int *value)
{
    remainTime = value;
}

void HaveForbidden::changeTimerAndLabel()
{
    timer->stop();
    if(gameSet.getGameIsEnd() == true)
        return;
    *remainTime = 80;
    if(gameSet.getCurrentPlayer() == GameVar::BLACK)
        label->setStyleSheet(CHANGE_WHITE_STYLE);
     else if(gameSet.getCurrentPlayer() == GameVar::WHITE)
         label->setStyleSheet(CHANGE_BLACK_STYLE);

     timer->start(1000);
}

void HaveForbidden::setLabelOne(QPushButton *value)
{
    labelOne = value;
}

void HaveForbidden::setLabelTwo(QPushButton *value)
{
    labelTwo = value;
}

void HaveForbidden::setLabel(QPushButton *value)
{
    label = value;
}

void HaveForbidden::chessOnClick(int id)
{
    i = static_cast<size_t>((id - 1) / 15);//按钮ＩＤ与坐标转换
    j = static_cast<size_t>((id - 1) % 15);
    if(gameSet.getMap_i_j_CanClicked(i, j) == false || gameStatus.getGameIsEnd() == true)//如果不可点击或者游戏结束，立即返回
          return;


     gameSet.stepAdd();
     QPushButton* cur = static_cast<QPushButton*>(group->button(id));

     if(gameSet.getCurrentPlayer() == GameVar::BLACK) {
           cur->setStyleSheet(CHANGE_BLACK_STYLE);
     } else if(gameSet.getCurrentPlayer() == GameVar::WHITE) {
           cur->setStyleSheet(CHANGE_WHITE_STYLE);
     }

     gameSet.setMap(i, j);
     changeTimerAndLabel();
     if(gameStatus.gameEnd() != GameVar::NONE) {
          QMessageBox* box = new QMessageBox();
          if(gameStatus.gameEnd() == GameVar::WHITE) {//对局结束，
               box->setText("white win!");
            }
          else if(gameStatus.gameEnd() == GameVar::BLACK) {
               box->setText("black win!");
          } else {
               box->setText("peace!");
          }
          box->resize(400, 200);
          box->show();
          gameSet.setGameIsEnd(true);
     }
}

