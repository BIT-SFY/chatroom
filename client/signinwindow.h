#ifndef SIGNINWINDOW_H
#define SIGNINWINDOW_H

#include "client.h"
#include <QWidget>

namespace Ui
{
class SigninWindow;
}

class SigninWindow : public QWidget
{
    Q_OBJECT

public:
    Client *tmpClient;
    bool isFormatCorrect(QString user_name, QString user_password, QString user_repassword);
    explicit SigninWindow(QWidget *parent = nullptr);
    ~SigninWindow();

signals:
    void BackToLoginWindow();

private slots:
    void on_pushButton_Exit_clicked();

    void on_pushButton_Sure_clicked();

private:
    Ui::SigninWindow *ui;
};

#endif // SIGNINWINDOW_H
