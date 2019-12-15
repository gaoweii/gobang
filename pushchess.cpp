#include "pushchess.h"
#include "buttonStyleSheet.h"
#include <QPushButton>
#include <QMessageBox>
#include <stack>
#include <QDebug>
#include <algorithm>


void PushChess::chessOnClick(int id) {//棋子点击事件
    i = static_cast<size_t>((id - 1) / 15);//按钮ＩＤ与坐标转换
    j = static_cast<size_t>((id - 1) % 15);



   if(gameSet.getGameRole() == GameVar::SPECIFIC) {
        specGameStatus.rule();
        if(gameSet.getGameStep() == 0) {
            if(i != 7 || j != 7)
                return;
        }
        if(gameSet.getGameStep() == 6) {//五手两打

           if(!myStack.empty()) {
                point1 = myStack.top();
                myStack.pop();
                point2 = myStack.top();
                myStack.pop();
           }

            if(!((i == static_cast<size_t>(point1.i) && j == static_cast<size_t>(point1.j)) ||
                    (i == static_cast<size_t>(point2.i) && j == static_cast<size_t>(point2.j)))) {
                gameRule2();
                return;
            }
            tmpButton = static_cast<QPushButton*>(group->button(id));
            gameSet.setMap(i, j, -1);
            tmpButton->setStyleSheet(BUTTON_STYLESHEET);
            tmpButton->setFlat(true);
            timer->start(80);
            timer->setInterval(1000);
            gameSet.stepAdd();
            return;
        }
   }
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
    if(gameSet.getGameRole() == GameVar::SPECIFIC) {
         gameRule1();
         gameRule2();
        changeTimerAndLabel();
    }

}

void PushChess::setRemainTime(int *value)
{
    remainTime = value;
}

void PushChess::changeTimerAndLabel()
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

void PushChess::setLabelOne(QPushButton *value)
{
    labelOne = value;
}

void PushChess::setLabelTwo(QPushButton *value)
{
    labelTwo = value;
}

PushChess::PushChess(QButtonGroup *group)
{
    this->group = group;
}

void PushChess::setTimer(QTimer *value)
{
    timer = value;
}

void PushChess::setLabel(QPushButton *value)
{
    label = value;
}

void PushChess::gameRule1()
{
    if(gameSet.getGameStep() == 3){  //三手交换
           QMessageBox* tmp = new QMessageBox();
           int tmpI = tmp->information(nullptr, "Gobang", "do you want to exchange?", QMessageBox::No, QMessageBox::Yes);
           timer->stop();
           if(tmpI == QMessageBox::Yes) {
               labelOne->setStyleSheet(CHANGE_WHITE_STYLE);
               labelTwo->setStyleSheet(CHANGE_BLACK_STYLE);
           }
    }
}

void PushChess::gameRule2()
{
    if(gameSet.getGameStep() == 5) {
        GameVar::Point tmpPoint;
        tmpPoint.i = i;
        tmpPoint.j = j;
        myStack.push(tmpPoint);
    }
    if(gameSet.getGameStep() == 6) {
        //五手两打
        if(getBook() == false) {
            GameVar::Point tmpPoint;
            tmpPoint.i = i;
            tmpPoint.j = j;
            myStack.push(tmpPoint);
            book = true;
        }
        timer->stop();
        if(QMessageBox::information(nullptr, "Gobang", "choose which black chess to remove", QMessageBox::Ok) == QMessageBox::Ok) {
            timer->start(80);
            timer->setInterval(1000);
        }

    }

}

bool PushChess::getBook()
{
    return book;

}

