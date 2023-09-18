#include "chatwindow.h"
#include "ui_chatwindow.h"
#include <QCloseEvent>

ChatWindow::ChatWindow(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::ChatWindow)
{
    ui->setupUi(this);
}

ChatWindow::~ChatWindow()
{
    delete ui;
}

//-------------------------------------------------------------------
// 展示收到的消息
//-------------------------------------------------------------------
void ChatWindow::ShowMessage(queue<Message> &msgbuff)
{
    while (!msgbuff.empty()) {
        Message s = msgbuff.front();
        // 将消息buff中的消息全都处理了
        QString a(s.sender_name);
        QString b(s.content);
        // 把时间戳转化为time_t
        time_t t_t = (time_t)s.send_time;
        struct tm *now = gmtime(&t_t);
        char timenow[100];
        sprintf(timenow, "%d月%d日 %02d:%02d", now->tm_mon + 1, now->tm_mday, (now->tm_hour + 8) % 24, now->tm_min);
        QString t(timenow);
        // 将接受到的消息以蓝色的形式展示
        ui->textBrowser_RecvMessage->append(QObject::tr("<font color=blue>%1</font>").arg(t + " @" + a + ": " + b));
        msgbuff.pop();
    }
}

//-------------------------------------------------------------------
// 展示聊天框的一些信息
//-------------------------------------------------------------------
void ChatWindow::showRecvInfo()
{
    if (type == SENDMSG) { // 私聊
        QString a(recver_name.c_str());
        ui->label_RecverName->setText(a);
        ui->pushButton_QuitGroup->setVisible(false);
    } else if (type == SENDALL) { // 群聊
        QString a(group_name.c_str());
        a = a + "  (" + QString::number(group_id) + ")";
        ui->label_RecverName->setText(a);
    }
}

//-------------------------------------------------------------------
// 按下x
//-------------------------------------------------------------------
void ChatWindow::closeEvent(QCloseEvent *event)
{
    back_to_mainwindow();
    event->accept();
}

//-------------------------------------------------------------------
// 按下发送按钮
//-------------------------------------------------------------------
void ChatWindow::on_pushButton_SendMessage_clicked()
{
    // 首先将发送方的消息打在屏幕上
    QString content = ui->textEdit_MessageBuffer->toPlainText();
    QString a(user->username.c_str());
    time_t nowtime;
    time(&nowtime);              // 获取1900年1月1日0点0分0秒到现在经过的秒数
    tm *p = localtime(&nowtime); // 将秒数转换为本地时间,年从1900算起,需要+1900,月为0-11,所以要+1
    char timenow[100];
    sprintf(timenow, "%d月%d日 %02d:%02d", p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min);
    QString t(timenow);
    ui->textBrowser_RecvMessage->append(t + " @" + a + ": " + content);

    // 清空发送文本区
    ui->textEdit_MessageBuffer->clear();
    // 如果是群发消息
    if (type == SENDALL)
        recver_port = group_id;
    // 调用发送端发送函数
    user->SendMessageToServer(content.toStdString(), recver_port, type);
}

//-------------------------------------------------------------------
// 退出群聊
//-------------------------------------------------------------------
void ChatWindow::on_pushButton_QuitGroup_clicked()
{
    quit_group(group_id);
    user->SendMessageToServer("", group_id, QUITGROUP);
    this->close();
}
