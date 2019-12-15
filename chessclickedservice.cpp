#include "chessclickedservice.h"
#include "buttonStyleSheet.h"
#include <exception>
#include <iostream>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

ChessClickedService::ChessClickedService(QObject *parent, QButtonGroup *buttonGroup) : QObject (parent) {

    try {
        if(buttonGroup == nullptr) throw std::logic_error("buttonGroup is nullptr ");
    } catch (const exception e) {
        cout << e.what() << __LINE__ << endl;
        exit(-1);
    }

    this->buttonGroup = buttonGroup;

}

void ChessClickedService::setNetwork(NetWorkService *value)
{
    network = value;
}

void ChessClickedService::netGameClicked(int i)
{
    if(canClicked == false) return;
    GameVar::Point point;
    this->i = static_cast<size_t>((i - 1) / 15);
    this->j = static_cast<size_t>((i - 1) % 15);

    if(gameSet.getMap_i_j_CanClicked(this->i, this->j) == false) {
        return;
    }

    point.setI(this->i);
    point.setJ(this->j);
    canClicked = false;

    connect(network, SIGNAL(Clicked(bool)), this, SLOT(_Clicked(bool)));
    gameSet.stepAdd();

    if(gameSet.getCurrentPlayer() == GameVar::WHITE) {
        static_cast<QPushButton*>(buttonGroup->button(i))->setStyleSheet(CHANGE_WHITE_STYLE);
        gameSet.setMap(this->i, this->j);
    }
    else if(gameSet.getCurrentPlayer() == GameVar::BLACK) {
        static_cast<QPushButton*>(buttonGroup->button(i))->setStyleSheet(CHANGE_BLACK_STYLE);
        gameSet.setMap(this->i, this->j);
    }
    if(gameStatus.gameEnd() == GameVar::WHITE) {
       QMessageBox::about(nullptr, "Gobang", "white win");
       emit setGameEnd();
    }
    else if(gameStatus.gameEnd() == GameVar::BLACK) {
        QMessageBox::about(nullptr, "Gobang", "black win");
        emit setGameEnd();
    }
    if(network->getType() == NetWork::SERVER) {
        connect(this, SIGNAL(sendToAnother(GameVar::Point)), network, SLOT(sendToClient(GameVar::Point)));
        emit sendToAnother(point);

    } else if(network->getType() == NetWork::CLIENT) {
        connect(this, SIGNAL(sendToAnother(GameVar::Point)), network, SLOT(sendToServer(GameVar::Point)));
        emit sendToAnother(point);
    }
}

void ChessClickedService::aiGameClicked(int i)
{

    GameVar::Point point;
    this->i = static_cast<size_t>((i - 1) / 15);
    this->j = static_cast<size_t>((i - 1) % 15);

    if(gameSet.getMap_i_j_CanClicked(this->i, this->j) == false) {
        return;
    }
    gameSet.setCurrentPlayer(GameVar::BLACK);//慎用，这个直接修改了内核运作机制，很容易写出bug

    static_cast<QPushButton*>(buttonGroup->button(i))->setStyleSheet(CHANGE_BLACK_STYLE);
    gameSet.setMap(this->i, this->j);
    GameVar::Point tmpPoint;


    if(gameStatus.gameEnd() == GameVar::WHITE) {
       QMessageBox::about(nullptr, "Gobang", "white win");
       emit setGameEnd();
    }
    else if(gameStatus.gameEnd() == GameVar::BLACK) {
        QMessageBox::about(nullptr, "Gobang", "black win");
        emit setGameEnd();
    }

    gameSet.stepAdd();
    gameSet.setCurrentPlayer(GameVar::WHITE);

    ai = new AI();
    GameVar::Point tem = ai->getCurrentChessDownPoint();
    int tem_I,tem_J;
    tem_I = tem.getI();
    tem_J = tem.getJ();
    int temp = tem_J*15+tem_I+1;
    QPushButton* cur_computer = static_cast<QPushButton*>(buttonGroup->button(temp));
        cur_computer->setStyleSheet(CHANGE_WHITE_STYLE);
        gameSet.setMap(static_cast<size_t>(tem_J),static_cast<size_t>(tem_I));

    if(gameStatus.gameEnd() == GameVar::WHITE) {
       QMessageBox::about(nullptr, "Gobang", "white win");
       emit setGameEnd();
    }
    else if(gameStatus.gameEnd() == GameVar::BLACK) {
        QMessageBox::about(nullptr, "Gobang", "black win");
        emit setGameEnd();
    }
    gameSet.stepAdd();
}

void ChessClickedService::_Clicked(bool can)
{
    canClicked = can;
}
