#include "aiandnetgame.h"
#include <QPainter>
#include "ui_aiandnetgame.h"
#include "buttonStyleSheet.h"
#include <QMessageBox>

AiAndNetGame::AiAndNetGame(QWidget *parent, NetWorkService* network) :
    QMainWindow(parent),
    ui(new Ui::AiAndNetGame),
    network(network)
{
    ui->setupUi(this);
    buttons = new QPushButton**[GameVar::INT_MAP_SIZE];
    buttonGroup = new QButtonGroup(this);
    chessClick = new ChessClickedService(nullptr, buttonGroup);
//    if(gameSet.getGameRole() == GameVar::PLAY_WITH_COMPUTER)
//        chessClick->setNetwork(network);

    initialSet();
    if(gameSet.getGameRole() == GameVar::INTERNET)
        netGameSet();
    else if(gameSet.getGameRole() == GameVar::PLAY_WITH_COMPUTER)
        aiGameSet();
}

AiAndNetGame::~AiAndNetGame()
{
    delete ui;
}

void AiAndNetGame::initialSet()
{
    this->setFixedSize(660, 660);
    for(int i = 0; i < GameVar::INT_MAP_SIZE; ++i) {
        buttons[i] = new QPushButton*[GameVar::INT_MAP_SIZE];
        for(int j = 0; j < GameVar::INT_MAP_SIZE; ++j) {
            buttons[i][j] = new QPushButton(this);
        }
    }

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#B1723C"));
    this->setPalette(palette);
    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);

    int k = 1;

    for(int i = 0; i < GameVar::INT_MAP_SIZE; ++i) {
        for(int j = 0; j <GameVar::INT_MAP_SIZE; ++j) {
            buttons[i][j]->setParent(this);
            buttons[i][j]->move(25 + i * 40, 45 + j * 40);
            buttons[i][j]->resize(30, 30);
            buttonGroup->addButton(buttons[i][j], k++);
            buttons[i][j]->setStyleSheet(BUTTON_STYLESHEET);
            buttons[i][j]->setFlat(true);
            buttons[i][j]->show();
        }
    }

    connect(chessClick, SIGNAL(setGameEnd()), this, SLOT(gameEnd()));
}

void AiAndNetGame::gameEnd()
{
    for(int i = 0; i < GameVar::INT_MAP_SIZE; ++i) {
        for(int j = 0; j < GameVar::INT_MAP_SIZE; ++j) {
            buttons[i][j]->setCheckable(false);
            gameSet.setMap(static_cast<size_t>(i), static_cast<size_t>(j), 2);
        }
    }

}

void AiAndNetGame::_changeChess(GameVar::Point point)
{
    gameSet.setMap(static_cast<size_t>(point.getI()),static_cast<size_t>(point.getJ()));
    if(gameSet.getCurrentPlayer() == GameVar::WHITE) {
        buttons[point.getI()][point.getJ()]->setStyleSheet(CHANGE_WHITE_STYLE);

    }
    else if(gameSet.getCurrentPlayer() == GameVar::BLACK) {
        buttons[point.getI()][point.getJ()]->setStyleSheet(CHANGE_BLACK_STYLE);

    }
    if(gameStatus.gameEnd() == GameVar::WHITE) {
        gameEnd();
        QMessageBox::information(this, "Gobang", "white win!", QMessageBox::Ok);
    }
    else if(gameStatus.gameEnd() == GameVar::BLACK) {
        gameEnd();
        QMessageBox::information(this, "Gobang", "black win!", QMessageBox::Ok);
    }
    else if(gameStatus.gameEnd() == GameVar::PEACE) {
        gameEnd();
        QMessageBox::information(this, "Gobang", "peace", QMessageBox::Ok);
    }

}


void AiAndNetGame::paintEvent(QPaintEvent*) {//画棋盘
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

void AiAndNetGame::netGameSet()
{
    chessClick->setNetwork(network);

    if(network->getType() == NetWork::SERVER)
        this->setWindowTitle("Gobang-server");
    else
        this->setWindowTitle("Gobang-client");

    connect(buttonGroup, SIGNAL(buttonClicked(int)), chessClick, SLOT(netGameClicked(int)));

    connect(network, SIGNAL(changeChess(GameVar::Point)), this, SLOT(_changeChess(GameVar::Point)));
}

void AiAndNetGame::aiGameSet()
{
    this->setWindowTitle("Gobang-AI");
    connect(buttonGroup, SIGNAL(buttonClicked(int)), chessClick, SLOT(aiGameClicked(int)));
}
