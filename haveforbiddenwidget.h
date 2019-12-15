#ifndef HAVEFORBIDDENWIDGET_H
#define HAVEFORBIDDENWIDGET_H

#include <QMainWindow>
#include "pushchess.h"
#include <QPushButton>
#include <QButtonGroup>
#include <QLCDNumber>
#include <QLabel>
#include <game.h>
#include <QTimer>
#include "mygameset.h"
#include "haveforbidden.h"
#include "nohands.h"

namespace Ui {
class HaveForbiddenWidget;
}

class HaveForbiddenWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit HaveForbiddenWidget(QWidget *parent = nullptr);
    ~HaveForbiddenWidget();

private:
    Ui::HaveForbiddenWidget *ui;
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
    static bool isIntialed;
    HaveForbidden* forbidden;
    NoHands* nohands;
    QPushButton* haveNoHands;
    int can = 3;
    QPushButton* reStart;

protected:
    void paintEvent(QPaintEvent* e);

    void initialSet(); //初始化设置

    void forbiddenRuleSet();//竞技模式设置

protected slots:
    void timerUpdate();
protected slots:
    void _haveNoHands();

    void __reStart();

};

#endif // HAVEFORBIDDENWIDGET_H
