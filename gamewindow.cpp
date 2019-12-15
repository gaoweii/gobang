#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QPainter>
#include <QButtonGroup>
#include <QPushButton>
#include "buttonStyleSheet.h"
#include <QDebug>
#include <QTimer>
#include <QLCDNumber>
#include <QLabel>
#include <QString>
#include <QMessageBox>


gameWindow::gameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::gameWindow)
{
    initialSet();
}

void gameWindow::initialSet()
{
    gameSet = new myGameSet();
    buttons = new QPushButton**[15];

    for(int i = 0; i < 15; ++i) {
        buttons[i] = new QPushButton*[15];
        for(int j = 0; j < 15; ++j) {
            buttons[i][j] = new QPushButton();
        }
    }
    group = new QButtonGroup();

    chess = new PushChess(group);

    ui->setupUi(this);
    if(game.getGameRole() == GameVar::FREE) {
        freeRuleSet();
    } else if(game.getGameRole() == GameVar::SPECIFIC) {
        specRuleSet();
    }
    publicSet();
}

void gameWindow::freeRuleSet()
{
    this->setFixedSize(800, 660);//设置游戏窗口
}

void gameWindow::specRuleSet()
{
    lcd = new QLCDNumber(this);//设置部件
    timer = new QTimer(this);
    label = new QPushButton(this);
    labelPlayer_2 = new QLabel(this);
    l = new QLabel(this);
    labelTwo = new QPushButton(this);
    labelPlayer_1 = new QLabel(this);
    labelOne = new QPushButton(this);
    chess->setLabel(label);
    chess->setTimer(timer);
    chess->setRemainTime(&remainTime);
    chess->setLabelOne(labelOne);
    chess->setLabelTwo(labelTwo);

    this->setFixedSize(800, 660);
    lcd->move(670, 40);
    lcd->show();
    labelPlayer_1->move(670, 70);
    labelPlayer_1->setText("Player1");
    labelPlayer_1->setStyleSheet("font-size:18px");
    labelPlayer_1->show();
    labelOne->move(670,100);
    labelOne->resize(30, 30);
    labelOne->setCheckable(false);
    labelOne->setStyleSheet(CHANGE_BLACK_STYLE);
    labelOne->show();
    labelPlayer_2->move(670, 130);
    labelPlayer_2->setText("Player2");
    labelPlayer_2->setStyleSheet("font-size:18px");
    labelPlayer_2->show();
    labelTwo->move(670, 160);
    labelTwo->resize(30, 30);
    labelTwo->setCheckable(false);
    labelTwo->setStyleSheet(CHANGE_WHITE_STYLE);
    labelTwo->show();
    l->move(670, 190);
    l->setText("next player:");
    l->setStyleSheet("font-size:18px");
    l->show();
    label->move(670, 220);
    label->resize(30, 30);
    label->setCheckable(false);
    label->setStyleSheet(CHANGE_BLACK_STYLE);
    label->show();

    label->setCheckable(false);
    label->setStyleSheet(CHANGE_BLACK_STYLE);
    label->show();
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));

}

void gameWindow::timerUpdate()//时间更新
{
    QString timeString = QString("%1-%2").arg(remainTime/60, 2, 10, QChar('0')).arg(remainTime % 60, 2, 10, QChar('0'));
    this->lcd->display(timeString);
    if(remainTime == 0) {
        QString winner;
        if(game.getCurrentPlayer() == GameVar::WHITE)
            winner = "black win!";
        else
            winner = "white win!";
        QMessageBox::about(this, "TimeOut", winner);
        gameSet->setGameIsEnd(true);
    }
    remainTime--;
}

void gameWindow::__reStart()
{
    for(size_t i = 0; i < 15; ++i) {
        for(size_t j = 0; j < 15; ++j) {
            gameSet->setMap(i, j, -1);
            buttons[i][j]->setFlat(true);
            buttons[i][j]->setStyleSheet(BUTTON_STYLESHEET);

        }
    }
    if(gameSet->getGameRole() == GameVar::SPECIFIC) {
        remainTime = 80;
        label->setStyleSheet(CHANGE_BLACK_STYLE);
        timerUpdate();
        timer->stop();
    }
}

void gameWindow::publicSet() {//公共设置，棋子初始化
    reStart = new QPushButton(this);
    reStart->setText("重新开始");
    reStart->resize(100, 50);
    if(gameSet->getGameRole() == GameVar::SPECIFIC)
        reStart->move(670, 270);
    else if(gameSet->getGameRole() == GameVar::FREE) {
        reStart->move(670, 40);
    }
    this->setWindowTitle("Gobang");
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#B1723C"));
    this->setPalette(palette);
    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);

    int k = 1;

    for(int i = 0; i < 15; ++i) {
        for(int j = 0; j < 15; ++j) {
            buttons[i][j]->setParent(this);
            buttons[i][j]->move(25 + i * 40, 45 + j * 40);
            buttons[i][j]->resize(30, 30);
            group->addButton(buttons[i][j], k++);
            buttons[i][j]->setStyleSheet(BUTTON_STYLESHEET);
            buttons[i][j]->setFlat(true);
            buttons[i][j]->show();
        }
    }
    connect(group, SIGNAL(buttonClicked(int)), chess, SLOT(chessOnClick(int)));
    connect(reStart, SIGNAL(clicked()), this, SLOT(__reStart()));
}

void gameWindow::paintEvent(QPaintEvent*) {//画棋盘
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen = painter.pen();
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(20, 40, 600, 600);

    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    for(int i = 0; i < 15; ++i) {
        painter.drawLine(40 + i * 40, 60, 40 + i * 40, 620);
        painter.drawLine(40, 60 + i * 40, 600, 60 + i * 40);
    }
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(155, 175, 10, 10);
    painter.drawRect(475, 175, 10, 10);
    painter.drawRect(155, 495, 10, 10);
    painter.drawRect(315, 335, 10, 10);
    painter.drawRect(475, 495, 10, 10);


}
