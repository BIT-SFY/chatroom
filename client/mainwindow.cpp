#include "mainwindow.h"
#include "createaddwindow.h"
#include "ui_mainwindow.h"
#include <QCloseEvent>
#include <QListWidgetItem>
#include <unistd.h>

//-------------------------------------------------------------------
// 主页面构造函数
//-------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) : QWidget(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 修改主页面标题
    this->setWindowTitle("chatroom");
}

//-------------------------------------------------------------------
// 主页面析构函数
//-------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//-------------------------------------------------------------------
// 初始化主页面内容
//-------------------------------------------------------------------
void MainWindow::InitMainWindowInfo()
{
    // 显示当前端口号
    ui->label_SenderPort_show->setText(QString::number(user->port));
    // 显示当前用户名
    QString a(user->username.c_str());
    ui->label_UserName_show->setText(a);
    // 创建主页面接收消息线程
    class thread pthread(Data_handle, this);
    pthread.detach();
    // 申请更新用户列表
    user->SendMessageToServer("", user->port, ONLINE);
    // 申请更新群聊列表
    user->SendMessageToServer("", user->port, CALLGROUPLIST);
}

//-------------------------------------------------------------------
// 更新在线用户列表
//-------------------------------------------------------------------
void MainWindow::UpdateUsersList(Message &s)
{
    string str, UsersList = s.content;
    int pos1 = 0, pos2 = 0, count = 0;
    // 将用户列表清空
    ui->listWidget_UsersList->clear();
    // 拆分content找出每个用户的用户名和端口号
    while (UsersList.find('.', pos1) != UsersList.npos) {
        pos2 = UsersList.find('.', pos1); // 找username
        str += UsersList.substr(pos1, pos2++ - pos1);
        str.push_back(':');
        pos1 = UsersList.find('.', pos2); // 找port
        str += UsersList.substr(pos2, pos1++ - pos2);
        QString a(str.c_str());
        ui->listWidget_UsersList->addItem(a);
        str.clear();
        count++;
    }
    ui->label_UserListNum->setText(QString::number(count));
}

//-------------------------------------------------------------------
// 更新群聊列表
//-------------------------------------------------------------------
void MainWindow::UpdateGroupList(Message &s)
{
    string GroupList = s.content;
    int pos1 = 0, pos2 = 0;
    // 将群聊列表清空
    ui->listWidget_GroupList->clear();
    string str;
    while (GroupList.find(':', pos1) != GroupList.npos) {
        pos2 = GroupList.find(':', pos1);     // 找第一个:,其前面是groupname
        pos2 = GroupList.find(':', pos2 + 1); // 找第二个:,其前面是groupid
        str = GroupList.substr(pos1, pos2 - pos1);
        pos1 = pos2 + 1;
        QString a(str.c_str());
        ui->listWidget_GroupList->addItem(a);
    }
}

//-------------------------------------------------------------------
// 双击某个用户，进入和该用户的聊天页面
//-------------------------------------------------------------------
void MainWindow::on_listWidget_UsersList_itemDoubleClicked(QListWidgetItem *item)
{
    // 获取当前行的内容
    string str = item->text().toStdString();
    int pos = str.find(':');
    // 拆分出用户名和端口号
    QString recver_name(str.substr(0, pos).c_str());
    QString recver_port(str.substr(pos + 1).c_str());
    auto cw = new ChatWindow();
    cw->user = this->user;
    cw->recver_name = recver_name.toStdString();
    cw->recver_port = recver_port.toInt();
    cw->type = SENDMSG; // 私聊
    cw->showRecvInfo();
    cwHashMap[cw->recver_port] = cw; // 将当前对话窗口放在对话窗口映射表中，一个端口对应一个表
    cw->show();
    cw->ShowMessage(msgBuff[cw->recver_port]);
    connect(cw, &ChatWindow::back_to_mainwindow, this, [=]() {
        cwHashMap.erase(cw->recver_port);
    });
}

//-------------------------------------------------------------------
// 双击某个群聊，进入该群聊页面
//-------------------------------------------------------------------
void MainWindow::on_listWidget_GroupList_itemDoubleClicked(QListWidgetItem *item)
{
    // 获取当前行的内容
    string str = item->text().toStdString();
    int pos = str.find(':');
    // 拆分出群名和群号
    QString group_name(str.substr(0, pos).c_str());
    QString group_id(str.substr(pos + 1).c_str());
    auto cw = new ChatWindow();
    cw->user = this->user;
    cw->group_name = group_name.toStdString();
    cw->group_id = group_id.toInt();
    cw->type = SENDALL; // 群聊
    cw->showRecvInfo();
    cwGroupHashMap[cw->group_id] = cw; // 将当前对话窗口放在对话窗口映射表中，一个端口对应一个表
    cw->show();
    cw->ShowMessage(msgGroupBuff[cw->group_id]);
    connect(cw, &ChatWindow::back_to_mainwindow, this, [=]() {
        cwGroupHashMap.erase(cw->group_id);
    });
    connect(cw, &ChatWindow::quit_group, this, [=]() {
        cwGroupHashMap.erase(cw->group_id);
        msgGroupBuff.erase(cw->group_id);
    });
}

//-------------------------------------------------------------------
// 客户端接受服务器发来的消息
//-------------------------------------------------------------------
void MainWindow::Data_handle(MainWindow *mw)
{

    int session_fd = mw->user->client_socket_fd;
    Message s; // 创建结构体用来接受信息
               //    int i =0;
    while (mw->user->flag) {
        if (recv(session_fd, &s, sizeof(Message), 0) < 0) {
            perror("Server Recieve Data Failed:");
            break;
        }
        //        cout << i++ << endl;
        if (mw->user->flag) {
            if (s.message_type == SENDMSG) {
                // 将消息加入消息栈
                mw->msgBuff[s.sender_port].push(s);
                // 如果打开了当前的对话窗口
                if (mw->cwHashMap.find(s.sender_port) != mw->cwHashMap.end()) {
                    mw->cwHashMap[s.sender_port]->ShowMessage(mw->msgBuff[s.sender_port]);
                }
            } else if (s.message_type == ONLINE) {
                mw->UpdateUsersList(s);
            } else if (s.message_type == CREATEGROUP) {
                if (s.sender_id == -1) {
                    QMessageBox::warning(NULL, "warning", "创建群聊失败", QMessageBox::Yes);
                } else {
                    mw->UpdateGroupList(s);
                }
            } else if (s.message_type == CALLGROUPLIST) { // 申请群聊列表
                mw->UpdateGroupList(s);
            } else if (s.message_type == JOINGROUP) {
                if (s.sender_id == -1) {
                    QMessageBox::warning(NULL, "warning", "加入群聊失败", QMessageBox::Yes);
                } else {
                    mw->UpdateGroupList(s);
                }
            } else if (s.message_type == SENDALL) {
                // 将消息加入消息栈
                cout << "群消息来了" << endl;
                mw->msgGroupBuff[s.recver_id].push(s);
                // 如果打开了群消息的对话窗口
                if (mw->cwGroupHashMap.find(s.recver_id) != mw->cwGroupHashMap.end()) {
                    mw->cwGroupHashMap[s.recver_id]->ShowMessage(mw->msgGroupBuff[s.recver_id]);
                }
            }
        }
    }
    return; // terminate calling thread!
}

//-------------------------------------------------------------------
// 按下右上角的X
//-------------------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
    // 该用户下线
    user->flag = 0;
    // 告知服务器用户离线,服务器端会close对应socket的收发功能，这会导致客户端socket的发收功能也中断
    user->SendMessageToServer("", user->port, -2);
    // 触发信号
    BackToLoginWindow();
    // 继续交由父类去执行
    event->accept();
}

//-------------------------------------------------------------------
// 点击创建群聊
//-------------------------------------------------------------------
void MainWindow::on_pushButton_CreateGroup_clicked()
{
    auto tmpwin = new CreateAddWindow(CREATEGROUP);
    tmpwin->user = user;
    tmpwin->show();
}

//-------------------------------------------------------------------
// 点击加入群聊
//-------------------------------------------------------------------
void MainWindow::on_pushButton_JoinGroup_clicked()
{
    auto tmpwin = new CreateAddWindow(JOINGROUP);
    tmpwin->user = user;
    tmpwin->show();
}

//-------------------------------------------------------------------
// 切换到私聊列表
//-------------------------------------------------------------------
void MainWindow::on_pushButton_UserList_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_UserLIst);
}

//-------------------------------------------------------------------
// 切换到群聊列表
//-------------------------------------------------------------------
void MainWindow::on_pushButton_GroupList_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_GroupList);
}
