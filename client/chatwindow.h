#ifndef CHATWINDOW_H
#define CHATWINDOW_H
#include "Frame.h"
#include "client.h"
#include <QWidget>

namespace Ui
{
class ChatWindow;
}

class ChatWindow : public QWidget
{
    Q_OBJECT

public:
    Client *user;
    int recver_port;    // 接收方端口
    string recver_name; // 接收方用户名
    int group_id;       // 群号
    string group_name;  // 群名
    int type;

    void ShowMessage(queue<Message> &msgbuff);
    void showRecvInfo();
    void closeEvent(QCloseEvent *event) override;
    explicit ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();

private slots:
    void on_pushButton_SendMessage_clicked();
    void on_pushButton_QuitGroup_clicked();

signals:
    void back_to_mainwindow();
    void quit_group(int group_id);

private:
    Ui::ChatWindow *ui;
};

#endif // CHATWINDOW_H
