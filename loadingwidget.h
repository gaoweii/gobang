#ifndef LOADINGWIDGET_H
#define LOADINGWIDGET_H

#include <QDialog>

namespace Ui {
class LoadingWidget;
}

class LoadingWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LoadingWidget(QWidget *parent = nullptr);
    ~LoadingWidget();

private:
    Ui::LoadingWidget *ui;
};

#endif // LOADINGWIDGET_H
