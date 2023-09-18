#include "signinwindow.h"
#include "client.h"
#include "ui_signinwindow.h"

int GetRandomPort();

bool SigninWindow::isFormatCorrect(QString user_name, QString user_password, QString user_repassword)
{
    if (user_name.size() == 0) {
        QMessageBox::warning(NULL, "warning", "用户名不能为空", QMessageBox::Yes);
        return false;
    }
    if (user_name.size() > 20) {
        QMessageBox::warning(NULL, "warning", "用户名不能超过20位", QMessageBox::Yes);
        return false;
    }
    if (user_password.size() == 0 || user_repassword.size() == 0) {
        QMessageBox::warning(NULL, "warning", "密码不能为空", QMessageBox::Yes);
        return false;
    }
    if (user_password.size() > 20 || user_repassword.size() > 20) {
        QMessageBox::warning(NULL, "warning", "密码不能超过20位", QMessageBox::Yes);
        return false;
    }
    if (user_password != user_repassword) {
        QMessageBox::warning(NULL, "warning", "两次密码输入不同", QMessageBox::Yes);
        return false;
    }
    return true;
}

SigninWindow::SigninWindow(QWidget *parent) : QWidget(parent), ui(new Ui::SigninWindow)
{
    ui->setupUi(this);
    tmpClient = new Client();
}

SigninWindow::~SigninWindow()
{
    delete ui;
}

//-------------------------------------------------------------------
// 按下退出按钮
//-------------------------------------------------------------------
void SigninWindow::on_pushButton_Exit_clicked()
{
    // 触发信号令登录页显示
    BackToLoginWindow();
    // 关闭socket连接，清除申请的临时客户端
    shutdown(tmpClient->client_socket_fd, SHUT_RDWR);
    delete tmpClient;
    // 注册页面删除
    this->close();
}

//-------------------------------------------------------------------
// 按下确定按钮
//-------------------------------------------------------------------
void SigninWindow::on_pushButton_Sure_clicked()
{
    QString user_name = ui->lineEdit_UserName->text();
    QString user_password = ui->lineEdit_PassWord->text();
    QString user_repassword = ui->lineEdit_RePassWord->text();
    if (isFormatCorrect(user_name, user_password, user_repassword)) {
        if (tmpClient->flag == 0) {
            tmpClient->InitClient(user_name.toStdString(), user_password.toStdString(), GetRandomPort());
            tmpClient->ConnectWithServer();
        } else {
            tmpClient->username = user_name.toStdString();
            tmpClient->password = user_password.toStdString();
        }
        tmpClient->SendMessageToServer("", tmpClient->port, SIGNIN);
        Message s; // 创建结构体用来接收服务端发送回来的注册请求
        if (recv(tmpClient->client_socket_fd, &s, sizeof(Message), 0) < 0) {
            perror("Server Recieve Data Failed:");
        }
        if (s.sender_id == -1) {
            QMessageBox::warning(NULL, "warning", "注册失败", QMessageBox::Yes);
        } else {
            QString QOK = "注册成功, 您的uid为:" + QString::number(s.sender_id);
            QMessageBox::information(NULL, "成功", QOK, QMessageBox::Yes);
            on_pushButton_Exit_clicked();
        }
    }
}
