#ifndef CREATEADDWINDOW_H
#define CREATEADDWINDOW_H

#include "client.h"
#include <QDialog>

namespace Ui
{
class CreateAddWindow;
}

class CreateAddWindow : public QDialog
{
    Q_OBJECT

public:
    Client *user;
    explicit CreateAddWindow(int message_type, QWidget *parent = nullptr);
    ~CreateAddWindow();

private slots:
    void on_pushButton_Sure_clicked();

private:
    int type;
    Ui::CreateAddWindow *ui;
};

#endif // CREATEADDWINDOW_H
