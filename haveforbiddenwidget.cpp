#include "haveforbiddenwidget.h"
#include "ui_haveforbiddenwidget.h"
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

HaveForbiddenWidget::HaveForbiddenWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HaveForbiddenWidget)
{
    ui->setupUi(this);
    initialSet();
}

HaveForbiddenWidget::~HaveForbiddenWidget()
{
    delete ui;
}

void HaveForbiddenWidget::paintEvent(QPaintEvent *e)
{
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

void HaveForbiddenWidget::initialSet()
{
    gameSet = new myGameSet();
        buttons = new QPushButton**[15];
        nohands = new NoHands();



        for(int i = 0; i < 15; ++i) {
            buttons[i] = new QPushButton*[15];
            for(int j = 0; j < 15; ++j) {
                buttons[i][j] = new QPushButton();
            }
        }
        group = new QButtonGroup();

        chess = new PushChess(group);

        forbidden = new HaveForbidden(group);

        ui->setupUi(this);
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


      forbiddenRuleSet();
}

void HaveForbiddenWidget::forbiddenRuleSet()
{
    lcd = new QLCDNumber(this);//设置部件
        timer = new QTimer(this);
        label = new QPushButton(this);
        labelPlayer_2 = new QLabel(this);
        l = new QLabel(this);
        labelTwo = new QPushButton(this);
        labelPlayer_1 = new QLabel(this);
        labelOne = new QPushButton(this);
        reStart = new QPushButton(this);
        forbidden->setLabel(label);
        forbidden->setTimer(timer);
        forbidden->setRemainTime(&remainTime);
        forbidden->setLabelOne(labelOne);
        forbidden->setLabelTwo(labelTwo);

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
        haveNoHands = new QPushButton(this);
        haveNoHands->setText("出现禁手");
        haveNoHands->move(660, 300);
        haveNoHands->resize(100, 50);
        haveNoHands->show();
        reStart->setText("重新开始");
        reStart->resize(100, 50);
        reStart->move(660, 360);
        reStart->show();
        label->setCheckable(false);
        label->setStyleSheet(CHANGE_BLACK_STYLE);
        label->show();
        connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
        connect(group, SIGNAL(buttonClicked(int)), forbidden, SLOT(chessOnClick(int)));
        connect(haveNoHands, SIGNAL(clicked()), this, SLOT(_haveNoHands()));
        connect(reStart, SIGNAL(clicked()), this, SLOT(__reStart()));
}

void HaveForbiddenWidget::timerUpdate()
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

void HaveForbiddenWidget::_haveNoHands()
{
    if(can == 0) {
        haveNoHands->setCheckable(false);
        delete haveNoHands;
    }
    if(can <= 0) {
        return;
    }
    if(nohands->is_have_nohands() == true) {
        QMessageBox::information(this, "Gobang", "出现禁手，白棋赢", QMessageBox::Ok);
    } else {
        can--;
    }
}

void HaveForbiddenWidget::__reStart()
{
    for(size_t i = 0; i < 15; ++i) {
        for(size_t j = 0; j < 15; ++j) {
            gameSet->setMap(i, j, -1);
            buttons[i][j]->setFlat(true);
            buttons[i][j]->setStyleSheet(BUTTON_STYLESHEET);

        }
    }
    remainTime = 80;
    label->setStyleSheet(CHANGE_BLACK_STYLE);
    timerUpdate();
    timer->stop();
}


