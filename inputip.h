#ifndef INPUTIP_H
#define INPUTIP_H

#include <QMainWindow>
#include "networkservice.h"

namespace Ui {
class InputIp;
}

class InputIp : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputIp(QWidget *parent = nullptr, NetWorkService* network = nullptr);
    ~InputIp();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InputIp *ui;
    NetWorkService* network;

};

#endif // INPUTIP_H
