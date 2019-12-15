#ifndef CHECKGAMEISEND_H
#define CHECKGAMEISEND_H

#include <QObject>
#include "mygamestatus.h"

class CheckGameIsEnd : public QObject
{
    Q_OBJECT
public:
    CheckGameIsEnd();

    void check();
signals:
    void gameEnd();

private:
    myGameStatus gameSatus;
};

#endif // CHECKGAMEISEND_H
