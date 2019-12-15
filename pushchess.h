#ifndef PUSHCHESS_H
#define PUSHCHESS_H
#include <QObject>
#include <QButtonGroup>
#include "mygameset.h"
#include "mygamestatus.h"
#include "myspecgamestatus.h"
#include <QPushButton>
#include <stack>
#include <QTimer>


class PushChess : public QObject
{
    Q_OBJECT

private:

    QButtonGroup* group;
    myGameSet gameSet;
    myGameStatus gameStatus;
    MySpecGameStatus specGameStatus;
    QPushButton* label, *labelOne, *labelTwo, *tmpButton;
    int* remainTime;
    QTimer* timer;
    stack<GameVar::Point> myStack;
    void *specRule1();
    void *specRule2();
    GameVar::Point point1, point2;

    size_t i, j;

    bool book = false;

public:
    PushChess() = delete;

    PushChess(QButtonGroup* group);

    ~PushChess() {
        delete group;
    }

    bool getBook();

    GameVar::Point res;

    void setTimer(QTimer *value);

    void setLabel(QPushButton *value);

    void gameRule1();

    void gameRule2();

    void setRemainTime(int *value);

    void changeTimerAndLabel();

    void setLabelOne(QPushButton *value);

    void setLabelTwo(QPushButton *value);

public slots:
    void chessOnClick(int);
};

#endif
