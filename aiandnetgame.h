#ifndef AIANDNETGAME_H
#define AIANDNETGAME_H

#include <QMainWindow>
#include <QPushButton>
#include <QButtonGroup>
#include <game.h>
#include "mygameset.h"
#include "networkservice.h"
#include "chessclickedservice.h"
#include "mygamestatus.h"

namespace Ui {
class AiAndNetGame;
}

class AiAndNetGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit AiAndNetGame(QWidget *parent = nullptr, NetWorkService* network = nullptr);
    ~AiAndNetGame();

    void paintEvent(QPaintEvent*);

    void netGameSet();

    void aiGameSet();

    void initialSet();

private:
    Ui::AiAndNetGame *ui;

    QPushButton*** buttons;

    QButtonGroup* buttonGroup;

    myGameSet gameSet;

    NetWorkService* network;

    ChessClickedService* chessClick;

    myGameStatus gameStatus;


public slots:

    void gameEnd();

public slots:

    void _changeChess(GameVar::Point point);

};

#endif // AIANDNETGAME_H
