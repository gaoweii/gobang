#include "gobang.h"
#include "ui_gobang.h"
#include "gamewindow.h"
#include "aiandnetgame.h"
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include "inputip.h"
#include "haveforbiddenwidget.h"
//#include "inputport.h"

Gobang::Gobang(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gobang)
{
    ui->setupUi(this);
    gameSet = new myGameSet();
}

Gobang::~Gobang()
{
    delete ui;
    delete gameSet;
}


void Gobang::on_pushButton_clicked()
{
    gameSet->setGameRole(GameVar::FREE);
    this->close();
    gameWindow* game = new gameWindow(nullptr);
    game->show();
}

void Gobang::on_pushButton_2_clicked()
{
   this->close();
    gameSet->setGameRole(GameVar::SPECIFIC);
    gameWindow* game = new gameWindow(nullptr);
    game->show();
}

void Gobang::on_pushButton_3_clicked()
{
    this->close();
    gameSet->setGameRole(GameVar::INTERNET);
    QAbstractButton* chooseServer, *chooseClient;
    QMessageBox messageBox(this);
    chooseServer = messageBox.addButton(tr("Server"), QMessageBox::ApplyRole);
    chooseClient = messageBox.addButton(tr("Client"), QMessageBox::ApplyRole);
    messageBox.resize(300, 200);
    messageBox.setText("are you a server or client");
    messageBox.exec();
    if(messageBox.clickedButton() == chooseServer) {
        network = new NetWorkService(NetWork::SERVER);
        network->server();

        AiAndNetGame* game = new AiAndNetGame(nullptr, network);
        game->show();
    } else if(messageBox.clickedButton() == chooseClient) {
        InputIp* inputwindow = new InputIp(nullptr, network);
        inputwindow->show();
    }
}

void Gobang::on_pushButton_4_clicked()
{
    this->close();
    gameSet->setGameRole(GameVar::PLAY_WITH_COMPUTER);
    AiAndNetGame* game = new AiAndNetGame();
    game->show();
}

void Gobang::on_pushButton_5_clicked()
{
   this->close();
    gameSet->setGameRole(GameVar::HAVENOHANDS);
   HaveForbiddenWidget* game = new HaveForbiddenWidget();
   game->show();

}
