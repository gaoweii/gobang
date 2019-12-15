#include "inputip.h"
#include "ui_inputip.h"
#include <QString>
#include "networkservice.h"
#include "aiandnetgame.h"

InputIp::InputIp(QWidget *parent, NetWorkService* _network) :
    QMainWindow(parent),
    ui(new Ui::InputIp),
    network(_network)
{
    ui->setupUi(this);
}

InputIp::~InputIp()
{
    delete ui;
}

void InputIp::on_pushButton_clicked()
{
   QString ip =  ui->textEdit->toPlainText();
   QString port = ui->textEdit_2->toPlainText();
   NetWorkService::setIp(ip);
   NetWorkService::setPort(port);
   network = new NetWorkService(NetWork::CLIENT);
   network->client();
   AiAndNetGame* game = new AiAndNetGame(nullptr, network);
   game->show();
}
