#include "loadingwidget.h"
#include "ui_loadingwidget.h"

LoadingWidget::LoadingWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadingWidget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    int x = width();
    int y = height();


}

LoadingWidget::~LoadingWidget()
{
    delete ui;
}
