#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "mainwindow.h"
#include "signinwindow.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    Client *user;
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_pushButton_Exit_clicked();

    void on_pushButton_LogIn_clicked();

    void on_pushButton_SignIn_clicked();

private:
    Ui::LoginWindow *ui;
    MainWindow *mainwindow;
    SigninWindow *signinwindow;
};
#endif // LOGINWINDOW_H
