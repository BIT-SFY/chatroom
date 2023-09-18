#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "chatwindow.h"
#include "client.h"
#include <QListWidgetItem>
#include <QWidget>
#include <unordered_map>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    Client *user;                                    // 在主页面中使用客户端
    unordered_map<int, ChatWindow *> cwHashMap;      // 对话窗口映射表,端口+窗口的指针
    unordered_map<int, ChatWindow *> cwGroupHashMap; // 群聊对话窗口映射表,群号+窗口的指针
    unordered_map<int, queue<Message>> msgBuff;      // 端口：私聊消息缓存
    unordered_map<int, queue<Message>> msgGroupBuff; // 群号：群消息缓存
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void InitMainWindowInfo();
    static void Data_handle(MainWindow *mw);
    void closeEvent(QCloseEvent *event) override;

signals:
    void BackToLoginWindow();

private slots:
    void UpdateUsersList(Message &s);

    void UpdateGroupList(Message &s);

    void on_listWidget_UsersList_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_CreateGroup_clicked();

    void on_pushButton_JoinGroup_clicked();

    void on_listWidget_GroupList_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_UserList_clicked();

    void on_pushButton_GroupList_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
