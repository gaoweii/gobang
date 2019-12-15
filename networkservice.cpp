#include "networkservice.h"
#include <algorithm>
#include <sstream>
#include <iostream>
#include <QMessageBox>
#include <QString>

QHostAddress* NetWorkService::ip = new QHostAddress();

quint16 NetWorkService::port = 9999;




void NetWorkService::setIp(const QString &value)
{
    ip->setAddress(value);
}

void NetWorkService::server()
{
    serverSocket->listen(QHostAddress::Any, port);
    qDebug() << serverSocket->serverAddress().toString() << endl;
    connect(serverSocket, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

void NetWorkService::client()
{
    clientSocket->connectToHost(*ip, port);

    if(!clientSocket->waitForConnected(3000)) {
        qDebug() << " failed" << endl;
    }

    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readServer()));
}

void NetWorkService::acceptConnection()
{
    clientConnection = serverSocket->nextPendingConnection();
    qDebug() << " 123 connect true " << endl;

    setHaveClientConnect(true);

    emit clientConnect();

    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void NetWorkService::readClient()
{
    char buffer[1024];
    clientConnection->read(buffer, 1024);
    string tmp(buffer);
    auto pos = find(tmp.begin(), tmp.end(), '#') - tmp.begin();
    getClient = tmp.substr(0, pos);
    istringstream is(getClient);
    string posI, posJ;
    is >> posI >> posJ;
    size_t i, j;
    i = std::stoul(posI.substr(5));
    j = std::stoul(posJ.substr(5));
    GameVar::Point point(i, j);


    gameSet.stepAdd();

    emit changeChess(point);

    gameSet.setMap(i, j);




    emit Clicked(true);
}

void NetWorkService::readServer()
{
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    clientSocket->read(buffer, 1024);
    cout << buffer << endl;
    string tmp(buffer);
    auto pos = find(tmp.begin(), tmp.end(), '#') - tmp.begin();
    getServer = tmp.substr(0, pos);
    istringstream is(getServer);
    string posI, posJ;
    is >> posI >> posJ;
    size_t i, j;
    cout << posI.substr(5) << endl;
    cout << posJ.substr(5) << endl;
    i = std::stoul(posI.substr(5));
    j = std::stoul(posJ.substr(5));
    GameVar::Point point(i, j);


    gameSet.stepAdd();

    emit changeChess(point);

    gameSet.setMap(i, j);




    emit Clicked(true);
}

void NetWorkService::sendToClient(GameVar::Point point)
{
    try {
        if(clientConnection == nullptr) throw logic_error("connection failed");
    } catch (const exception& e) {
        cout << e.what() << endl;
        if(connectNum >= 0) {
            clientConnection = serverSocket->nextPendingConnection();
        } else {
            QMessageBox::information(nullptr, "Connection Failed", "Connection Failed to: " + addr.toString(), QMessageBox::Ok);
        }
    }
    toClient = "posI:" + std::to_string(point.getI()) + " posJ:" + std::to_string(point.getJ()) + "#";
    clientConnection->write(toClient.c_str(), strlen(toClient.c_str()));
}

void NetWorkService::sendToServer(GameVar::Point point)
{
    try {
        if(clientSocket->isOpen() == false) throw logic_error("connection failed");
    } catch (const exception& e) {
        QMessageBox::information(nullptr, "Connection Failed", "Connection Failed to: " + ip->toString(), QMessageBox::Ok);
        cout << e.what() << endl;
    }

    toServer = "posI:" + to_string(point.getI()) + " posJ:" + to_string(point.getJ()) + "#";

    clientSocket->write(toServer.c_str(), strlen(toServer.c_str()));
}

void NetWorkService::setPort(int value)
{
    port = static_cast<quint16>(value);
}

void NetWorkService::setPort(const QString &value)
{
   port = value.toUShort();
}

NetWork::Type NetWorkService::getType()
{
    return this->type;
}

bool NetWorkService::getHaveClientConnect() const
{
    return haveClientConnect;
}

void NetWorkService::setHaveClientConnect(bool value)
{
    haveClientConnect = value;
}

NetWorkService::NetWorkService(NetWork::Type type)
{
    this->type = type;

    if(this->type == NetWork::SERVER) {
        serverSocket = new QTcpServer();
    } else {
        clientSocket = new QTcpSocket();
    }

    gameSet = myGameSet();

    addr = QHostAddress();
}
