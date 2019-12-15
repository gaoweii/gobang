#ifndef CHESSCLICKEDSERVICE_H
#define CHESSCLICKEDSERVICE_H

#include <QObject>
#include <QButtonGroup>
#include "mygameset.h"
#include "networkservice.h"
#include "mygamestatus.h"
#include "ai.h"

class ChessClickedService : public QObject
{
    Q_OBJECT
public:
    explicit ChessClickedService(QObject *parent = nullptr, QButtonGroup* buttonGroup = nullptr);

    void setNetwork(NetWorkService *value);


private:
    QButtonGroup* buttonGroup;

    size_t i, j;

    myGameSet gameSet;

    myGameStatus gameStatus;

    bool canClicked = true;

    NetWorkService* network = nullptr;

    AI* ai;


signals:
    void sendToAnother(GameVar::Point);

    void setGameEnd();

public slots:
    void netGameClicked(int i);

    void aiGameClicked(int i);

    void _Clicked(bool can);
};

#endif // CHESSCLICKEDSERVICE_H
