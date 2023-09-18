/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QFrame *frame_User;
    QLabel *label_SenderPort_show;
    QLabel *label_UserName_show;
    QLabel *label_SenderPort;
    QLabel *label_UserName;
    QFrame *frameList;
    QStackedWidget *stackedWidget;
    QWidget *page_UserLIst;
    QLabel *label_UserListNum;
    QListWidget *listWidget_UsersList;
    QLabel *label_UserList;
    QWidget *page_GroupList;
    QPushButton *pushButton_JoinGroup;
    QPushButton *pushButton_CreateGroup;
    QListWidget *listWidget_GroupList;
    QPushButton *pushButton_UserList;
    QPushButton *pushButton_GroupList;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(351, 780);
        MainWindow->setStyleSheet(QString::fromUtf8("/**\346\255\243\345\270\270\346\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QWidget{\n"
"    background-color: white;\n"
"}\344\270\211"));
        frame_User = new QFrame(MainWindow);
        frame_User->setObjectName(QString::fromUtf8("frame_User"));
        frame_User->setGeometry(QRect(0, 0, 351, 121));
        frame_User->setFrameShape(QFrame::StyledPanel);
        frame_User->setFrameShadow(QFrame::Raised);
        label_SenderPort_show = new QLabel(frame_User);
        label_SenderPort_show->setObjectName(QString::fromUtf8("label_SenderPort_show"));
        label_SenderPort_show->setGeometry(QRect(190, 70, 151, 41));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        label_SenderPort_show->setFont(font);
        label_UserName_show = new QLabel(frame_User);
        label_UserName_show->setObjectName(QString::fromUtf8("label_UserName_show"));
        label_UserName_show->setGeometry(QRect(190, 10, 151, 41));
        label_UserName_show->setFont(font);
        label_SenderPort = new QLabel(frame_User);
        label_SenderPort->setObjectName(QString::fromUtf8("label_SenderPort"));
        label_SenderPort->setGeometry(QRect(50, 70, 121, 41));
        QFont font1;
        font1.setPointSize(20);
        label_SenderPort->setFont(font1);
        label_UserName = new QLabel(frame_User);
        label_UserName->setObjectName(QString::fromUtf8("label_UserName"));
        label_UserName->setGeometry(QRect(50, 10, 121, 41));
        label_UserName->setFont(font1);
        frameList = new QFrame(MainWindow);
        frameList->setObjectName(QString::fromUtf8("frameList"));
        frameList->setGeometry(QRect(0, 200, 351, 581));
        frameList->setFrameShape(QFrame::StyledPanel);
        frameList->setFrameShadow(QFrame::Raised);
        stackedWidget = new QStackedWidget(frameList);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 351, 561));
        page_UserLIst = new QWidget();
        page_UserLIst->setObjectName(QString::fromUtf8("page_UserLIst"));
        label_UserListNum = new QLabel(page_UserLIst);
        label_UserListNum->setObjectName(QString::fromUtf8("label_UserListNum"));
        label_UserListNum->setGeometry(QRect(210, 0, 51, 41));
        label_UserListNum->setFont(font1);
        listWidget_UsersList = new QListWidget(page_UserLIst);
        listWidget_UsersList->setObjectName(QString::fromUtf8("listWidget_UsersList"));
        listWidget_UsersList->setGeometry(QRect(0, 50, 351, 571));
        QFont font2;
        font2.setPointSize(24);
        listWidget_UsersList->setFont(font2);
        listWidget_UsersList->setMouseTracking(true);
        label_UserList = new QLabel(page_UserLIst);
        label_UserList->setObjectName(QString::fromUtf8("label_UserList"));
        label_UserList->setGeometry(QRect(50, 0, 271, 41));
        label_UserList->setFont(font1);
        stackedWidget->addWidget(page_UserLIst);
        listWidget_UsersList->raise();
        label_UserList->raise();
        label_UserListNum->raise();
        page_GroupList = new QWidget();
        page_GroupList->setObjectName(QString::fromUtf8("page_GroupList"));
        pushButton_JoinGroup = new QPushButton(page_GroupList);
        pushButton_JoinGroup->setObjectName(QString::fromUtf8("pushButton_JoinGroup"));
        pushButton_JoinGroup->setGeometry(QRect(200, 0, 121, 40));
        QFont font3;
        font3.setPointSize(18);
        pushButton_JoinGroup->setFont(font3);
        pushButton_CreateGroup = new QPushButton(page_GroupList);
        pushButton_CreateGroup->setObjectName(QString::fromUtf8("pushButton_CreateGroup"));
        pushButton_CreateGroup->setGeometry(QRect(30, 0, 120, 40));
        pushButton_CreateGroup->setFont(font3);
        listWidget_GroupList = new QListWidget(page_GroupList);
        listWidget_GroupList->setObjectName(QString::fromUtf8("listWidget_GroupList"));
        listWidget_GroupList->setGeometry(QRect(0, 50, 351, 511));
        listWidget_GroupList->setFont(font2);
        listWidget_GroupList->setMouseTracking(true);
        stackedWidget->addWidget(page_GroupList);
        pushButton_UserList = new QPushButton(MainWindow);
        pushButton_UserList->setObjectName(QString::fromUtf8("pushButton_UserList"));
        pushButton_UserList->setGeometry(QRect(0, 140, 171, 41));
        pushButton_UserList->setStyleSheet(QString::fromUtf8("/**\346\255\243\345\270\270\346\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton{\n"
"	font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"    color: #2f3640;\n"
"    background-color: #f5f6fa;\n"
"    border-color: #2f3640;\n"
"    border-radius: 15px;\n"
"    border-style: solid;\n"
"    border-width: 2px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/**\351\274\240\346\240\207\345\201\234\347\225\231\345\234\250\346\214\211\351\222\256\344\270\212\347\232\204\346\240\267\345\274\217**/\n"
"QPushButton::hover{	\n"
"    color: #FFFFFF;\n"
"    background-color: #718093;\n"
"    border-color: #2f3640;\n"
"}\n"
"\n"
"/**\351\274\240\346\240\207\346\214\211\345\216\213\344\270\213\345\216\273\347\232\204\346\240\267\345\274\217**/\n"
"QPushButton::pressed,QPushButton::checked{\n"
"    color: #FFFFFF;\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);\n"
"}\n"
"\n"
"/**\346\214\211\351\222\256\345\244\261\350\203\275\346"
                        "\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton::disabled{\n"
"    color: #FFFFFF;\n"
"    background-color: #dcdde1;\n"
"    border-color: #dcdde1;\n"
"}\n"
""));
        pushButton_GroupList = new QPushButton(MainWindow);
        pushButton_GroupList->setObjectName(QString::fromUtf8("pushButton_GroupList"));
        pushButton_GroupList->setGeometry(QRect(180, 140, 171, 41));
        pushButton_GroupList->setStyleSheet(QString::fromUtf8("/**\346\255\243\345\270\270\346\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton{\n"
"	font: 16pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"    color: #2f3640;\n"
"    background-color: #f5f6fa;\n"
"    border-color: #2f3640;\n"
"    border-radius: 15px;\n"
"    border-style: solid;\n"
"    border-width: 2px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/**\351\274\240\346\240\207\345\201\234\347\225\231\345\234\250\346\214\211\351\222\256\344\270\212\347\232\204\346\240\267\345\274\217**/\n"
"QPushButton::hover{	\n"
"    color: #FFFFFF;\n"
"    background-color: #718093;\n"
"    border-color: #2f3640;\n"
"}\n"
"\n"
"/**\351\274\240\346\240\207\346\214\211\345\216\213\344\270\213\345\216\273\347\232\204\346\240\267\345\274\217**/\n"
"QPushButton::pressed,QPushButton::checked{\n"
"    color: #FFFFFF;\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 #273c75, stop:1 #487eb0);\n"
"}\n"
"\n"
"/**\346\214\211\351\222\256\345\244\261\350\203\275\346"
                        "\203\205\345\206\265\344\270\213\346\240\267\345\274\217**/\n"
"QPushButton::disabled{\n"
"    color: #FFFFFF;\n"
"    background-color: #dcdde1;\n"
"    border-color: #dcdde1;\n"
"}\n"
""));

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", nullptr));
        label_SenderPort_show->setText(QString());
        label_UserName_show->setText(QString());
        label_SenderPort->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\347\253\257\345\217\243\357\274\232", nullptr));
        label_UserName->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232", nullptr));
        label_UserListNum->setText(QString());
        label_UserList->setText(QApplication::translate("MainWindow", "\345\275\223\345\211\215\347\224\250\346\210\267:                \344\272\272", nullptr));
        pushButton_JoinGroup->setText(QApplication::translate("MainWindow", "\345\212\240\345\205\245\347\276\244\350\201\212", nullptr));
        pushButton_CreateGroup->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\347\276\244\350\201\212", nullptr));
        pushButton_UserList->setText(QApplication::translate("MainWindow", "\347\247\201\350\201\212", nullptr));
        pushButton_GroupList->setText(QApplication::translate("MainWindow", "\347\276\244\350\201\212", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
