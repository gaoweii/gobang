#ifndef GOBANG_H
#define GOBANG_H

#include <QMainWindow>
#include "mygameset.h"
#include "networkservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Gobang; }
QT_END_NAMESPACE

class Gobang : public QMainWindow
{
    Q_OBJECT


public:
    Gobang(QWidget *parent = nullptr);
    ~Gobang();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Gobang *ui;
    myGameSet* gameSet;
    NetWorkService* network;

};
#endif // GOBANG_H
