#ifndef NETWORKSERVICE_H
#define NETWORKSERVICE_H

#include <QtNetwork>
#include <QObject>
#include <string>
#include <QString>
#include <mygameset.h>

using namespace std;

namespace NetWork {

enum Type{SERVER, CLIENT};

const char IP[] = "";

const quint16 PORT = 8888;

const int MAXCONNECTNUM = 3;

}


class NetWorkService : public QObject
{
    Q_OBJECT
private:

    QTcpServer* serverSocket = nullptr;

    QTcpSocket* clientSocket = nullptr;

    QTcpSocket* clientConnection = nullptr;

    QHostAddress addr;

    static QHostAddress* ip;

    static quint16 port;

    NetWork::Type type = NetWork::SERVER;

    string getClient = "";

    string toClient = "";

    string toServer = "";

    string getServer = "";

    bool haveClientConnect = false;

    myGameSet gameSet;

    int connectNum = NetWork::MAXCONNECTNUM;

public:
    NetWorkService() = delete;

    NetWorkService(NetWork::Type);

    QString getIp() const;

    static void setIp(const QString &value);

    static void setPort(int value);

    static void setPort(const QString & value);

    NetWork::Type getType();

    bool getHaveClientConnect() const;

    void setHaveClientConnect(bool value);

public slots:

    void server();

    void client();

    void acceptConnection();

    void sendToClient(GameVar::Point);

    void sendToServer(GameVar::Point);

    void readClient();

    void readServer();

public:
signals:
    void changeChess(GameVar::Point);

signals:
    void Clicked(bool);

signals:
    void clientConnect();

};

#endif // NETWORKSERVICE_H
