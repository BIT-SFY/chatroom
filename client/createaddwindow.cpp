#include "createaddwindow.h"
#include "ui_createaddwindow.h"

CreateAddWindow::CreateAddWindow(int message_type, QWidget *parent) : QDialog(parent), type(message_type),
                                                                      ui(new Ui::CreateAddWindow)
{
    ui->setupUi(this);
    QString t;
    if (type == CREATEGROUP) {
        t = QString::fromUtf8("创建群聊:");
    } else if (type == JOINGROUP) {
        t = QString::fromUtf8("加入群聊:");
        ui->label_GroupName->setVisible(false);
        ui->lineEdit_GroupName->setVisible(false);
    }
    this->setWindowTitle("chatroom");
    ui->label->setText(t);
}

CreateAddWindow::~CreateAddWindow()
{
    delete ui;
}

void CreateAddWindow::on_pushButton_Sure_clicked()
{
    // 将创建的群号和群名称发送出去,如果是加入群聊则:后为空
    QString s = ui->lineEdit_id->text() + ':' + ui->lineEdit_GroupName->text();
    user->SendMessageToServer(s.toStdString(), user->port, type);
    this->close();
}
