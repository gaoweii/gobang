#pragma once
#include <QMainWindow>
#include "pushchess.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLCDNumber>
#include <QLabel>
#include <game.h>
#include <QTimer>
#include "mygameset.h"


namespace Ui {
class gameWindow;
}

class gameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit gameWindow(QWidget *parent = nullptr);

    ~gameWindow() {
        delete chess;
        for(int i = 0; i < 15; ++i) {
           delete[] buttons;
        }
        delete group;
        delete lcd;
        delete label;
        delete gameSet;
        delete timer;
        delete l;
    }

private:
    Ui::gameWindow *ui;
    PushChess* chess;
    QPushButton*** buttons;
    QButtonGroup* group;
    QLCDNumber* lcd;
    QPushButton* label, *labelOne, *labelTwo;
    Game game;
    QTimer* timer;
    myGameSet* gameSet;
    int remainTime = 80;
    QLabel* l, *labelPlayer_1, *labelPlayer_2;
    QPushButton* reStart;
    static bool isIntialed;

protected:
    void paintEvent(QPaintEvent* e);

    void publicSet();

    void initialSet(); //初始化设置

    void freeRuleSet();//自由对战模式设置

    void specRuleSet();//竞技模式设置

protected slots:
    void timerUpdate();

    void __reStart();

};

