#ifndef HAVEFORBIDDEN_H
#define HAVEFORBIDDEN_H
#include <QPushButton>
#include <stack>
#include <QTimer>
#include <QObject>
#include <QButtonGroup>
#include "mygameset.h"
#include "mygamestatus.h"


class HaveForbidden: public QObject
{
    Q_OBJECT
private:
    QButtonGroup* group;
    myGameSet gameSet;
    myGameStatus gameStatus;
    int* remainTime;
    QTimer* timer;
    size_t i, j;
    bool book = false;
    QPushButton* label, *labelOne, *labelTwo, *tmpButton;



public:
    HaveForbidden(QButtonGroup* group);

    bool getBook();

    GameVar::Point res;

    void setTimer(QTimer *value);

     void setRemainTime(int *value);

     void changeTimerAndLabel();

     void setLabelOne(QPushButton *value);

     void setLabelTwo(QPushButton *value);

      void setLabel(QPushButton *value);

public slots:
    void chessOnClick(int);

};

#endif // HAVEFORBIDDEN_H
