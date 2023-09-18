/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QPushButton *pushButton_SendMessage;
    QTextEdit *textEdit_MessageBuffer;
    QLabel *label_RecverName;
    QTextBrowser *textBrowser_RecvMessage;
    QPushButton *pushButton_QuitGroup;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(759, 652);
        pushButton_SendMessage = new QPushButton(ChatWindow);
        pushButton_SendMessage->setObjectName(QString::fromUtf8("pushButton_SendMessage"));
        pushButton_SendMessage->setGeometry(QRect(620, 580, 141, 81));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        pushButton_SendMessage->setFont(font);
        textEdit_MessageBuffer = new QTextEdit(ChatWindow);
        textEdit_MessageBuffer->setObjectName(QString::fromUtf8("textEdit_MessageBuffer"));
        textEdit_MessageBuffer->setGeometry(QRect(0, 470, 761, 191));
        QFont font1;
        font1.setPointSize(20);
        textEdit_MessageBuffer->setFont(font1);
        label_RecverName = new QLabel(ChatWindow);
        label_RecverName->setObjectName(QString::fromUtf8("label_RecverName"));
        label_RecverName->setGeometry(QRect(30, 10, 571, 51));
        QFont font2;
        font2.setPointSize(22);
        font2.setBold(true);
        font2.setUnderline(true);
        font2.setWeight(75);
        label_RecverName->setFont(font2);
        textBrowser_RecvMessage = new QTextBrowser(ChatWindow);
        textBrowser_RecvMessage->setObjectName(QString::fromUtf8("textBrowser_RecvMessage"));
        textBrowser_RecvMessage->setGeometry(QRect(0, 80, 761, 381));
        textBrowser_RecvMessage->setFont(font1);
        pushButton_QuitGroup = new QPushButton(ChatWindow);
        pushButton_QuitGroup->setObjectName(QString::fromUtf8("pushButton_QuitGroup"));
        pushButton_QuitGroup->setGeometry(QRect(670, 40, 89, 41));
        QFont font3;
        font3.setPointSize(16);
        pushButton_QuitGroup->setFont(font3);
        textEdit_MessageBuffer->raise();
        label_RecverName->raise();
        pushButton_SendMessage->raise();
        textBrowser_RecvMessage->raise();
        pushButton_QuitGroup->raise();

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QApplication::translate("ChatWindow", "Form", nullptr));
        pushButton_SendMessage->setText(QApplication::translate("ChatWindow", "\345\217\221\351\200\201", nullptr));
        textEdit_MessageBuffer->setHtml(QApplication::translate("ChatWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:20pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_RecverName->setText(QString());
        pushButton_QuitGroup->setText(QApplication::translate("ChatWindow", "\351\200\200\345\207\272\350\257\245\347\276\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
