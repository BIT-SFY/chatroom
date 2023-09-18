#include "loginwindow.h"
#include "client.h"
#include "ui_loginwindow.h"

void Data_handle(MainWindow *mw, int session_fd);
bool WaitPassWord = true;
int CheckPassWord = 0;
int GetRandomPort();

//-------------------------------------------------------------------
// 登录页面的构造函数
//-------------------------------------------------------------------
LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    // 创建一个客户端
    user = new Client();
}

//-------------------------------------------------------------------
// 退出页面的析构函数
//-------------------------------------------------------------------
LoginWindow::~LoginWindow()
{
    delete ui;
    delete mainwindow;
}

//-------------------------------------------------------------------
// 按下退出按钮
//-------------------------------------------------------------------
void LoginWindow::on_pushButton_Exit_clicked()
{
    if (user->flag == 1) {
        // 如果此用户与服务器建立了连接，则告知服务器用户离线,服务器端会close对应socket的收发功能，这会导致客户端socket的发收功能也中断
        user->SendMessageToServer("", user->port, -2);
    }
    shutdown(user->client_socket_fd, SHUT_RDWR);
    // 删除用户
    delete user;
    // 关闭登录页面
    this->close();
}

//-------------------------------------------------------------------
// 按下登录按钮
//-------------------------------------------------------------------
void LoginWindow::on_pushButton_LogIn_clicked()
{
    // 获取当前用户在登录页面输入的信息，并据此信息创建一个客户端
    QString user_name = ui->lineEdit_UserName->text();
    if (user_name.isEmpty())
        user_name = "admin";
    QString user_password = ui->lineEdit_PassWord->text();
    if (user_password.isEmpty())
        user_password = "123";
    if (user->flag == 0) { // client还没激活
        user->InitClient(user_name.toStdString(), user_password.toStdString(), GetRandomPort());
        user->ConnectWithServer();
    } else {
        user->username = user_name.toStdString();
        user->password = user_password.toStdString();
    }
    user->SendMessageToServer("", user->port, LOGIN);
    Message s;
    if (recv(user->client_socket_fd, &s, sizeof(Message), 0) < 0) {
        perror("Server Recieve Data Failed:");
    }
    if (s.sender_id >= 0) { // 密码正确
        // 设置用户的uid
        user->uid = s.sender_id;
        // 创建主页面
        mainwindow = new MainWindow();
        // 信号：主页面的登出按钮，槽函数:显示登录页面
        connect(mainwindow, &MainWindow::BackToLoginWindow, this, [=]() {
            this->show();
        });
        // 将创建的客户信息与主页面的客户指针绑定
        mainwindow->user = user;
        // 初始化主页面相关内容
        mainwindow->InitMainWindowInfo();
        // 隐藏登录页面
        this->hide();
        // 显示主页面
        mainwindow->show();
    } else { // 密码错误
        QMessageBox::warning(NULL, "warning", "密码错误", QMessageBox::Yes);
    }
}

//-------------------------------------------------------------------
// 按下注册按钮
//-------------------------------------------------------------------
void LoginWindow::on_pushButton_SignIn_clicked()
{
    // 创建注册页
    signinwindow = new SigninWindow();
    // 修改主页面标题
    signinwindow->setWindowTitle("chatroom");
    // 隐藏登录页面
    this->hide();
    // 显示注册页面
    signinwindow->show();
    // 信号：注册页的登出按钮，槽函数:显示登录页面
    connect(signinwindow, &SigninWindow::BackToLoginWindow, this, [=]() {
        this->show();
    });
}

//-------------------------------------------------------------------
// 获取随机可用端口
//-------------------------------------------------------------------
int GetRandomPort()
{
    int port;
    time_t t;
    char port_cmd[512];
    srand((unsigned)time(&t));
    while (true) {
        port = rand() % 4001 + 5000;
        sprintf(port_cmd, "netstat -an | grep :%d > /dev/null", port);
        if (system(port_cmd))
            break;
    }
    return port;
}
