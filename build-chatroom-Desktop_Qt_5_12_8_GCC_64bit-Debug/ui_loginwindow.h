/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLabel *label_UserName;
    QLineEdit *lineEdit_UserName;
    QLineEdit *lineEdit_PassWord;
    QPushButton *pushButton_SignIn;
    QPushButton *pushButton_LogIn;
    QPushButton *pushButton_Exit;
    QLabel *label_PassWord;
    QLabel *label_Title;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName(QString::fromUtf8("LoginWindow"));
        LoginWindow->resize(669, 423);
        label_UserName = new QLabel(LoginWindow);
        label_UserName->setObjectName(QString::fromUtf8("label_UserName"));
        label_UserName->setGeometry(QRect(100, 110, 160, 70));
        QFont font;
        font.setPointSize(20);
        label_UserName->setFont(font);
        lineEdit_UserName = new QLineEdit(LoginWindow);
        lineEdit_UserName->setObjectName(QString::fromUtf8("lineEdit_UserName"));
        lineEdit_UserName->setGeometry(QRect(240, 120, 350, 60));
        lineEdit_UserName->setFont(font);
        lineEdit_PassWord = new QLineEdit(LoginWindow);
        lineEdit_PassWord->setObjectName(QString::fromUtf8("lineEdit_PassWord"));
        lineEdit_PassWord->setGeometry(QRect(240, 200, 350, 60));
        lineEdit_PassWord->setFont(font);
        pushButton_SignIn = new QPushButton(LoginWindow);
        pushButton_SignIn->setObjectName(QString::fromUtf8("pushButton_SignIn"));
        pushButton_SignIn->setGeometry(QRect(100, 300, 110, 60));
        QFont font1;
        font1.setPointSize(18);
        pushButton_SignIn->setFont(font1);
        pushButton_LogIn = new QPushButton(LoginWindow);
        pushButton_LogIn->setObjectName(QString::fromUtf8("pushButton_LogIn"));
        pushButton_LogIn->setGeometry(QRect(280, 300, 110, 60));
        pushButton_LogIn->setFont(font1);
        pushButton_Exit = new QPushButton(LoginWindow);
        pushButton_Exit->setObjectName(QString::fromUtf8("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(460, 300, 110, 60));
        pushButton_Exit->setFont(font1);
        label_PassWord = new QLabel(LoginWindow);
        label_PassWord->setObjectName(QString::fromUtf8("label_PassWord"));
        label_PassWord->setGeometry(QRect(100, 190, 160, 70));
        label_PassWord->setFont(font);
        label_Title = new QLabel(LoginWindow);
        label_Title->setObjectName(QString::fromUtf8("label_Title"));
        label_Title->setGeometry(QRect(230, 30, 261, 61));
        QFont font2;
        font2.setPointSize(30);
        font2.setBold(true);
        font2.setWeight(75);
        label_Title->setFont(font2);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QApplication::translate("LoginWindow", "ChatRoom", nullptr));
        label_UserName->setText(QApplication::translate("LoginWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        lineEdit_UserName->setText(QString());
        pushButton_SignIn->setText(QApplication::translate("LoginWindow", "\346\263\250\345\206\214", nullptr));
        pushButton_LogIn->setText(QApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        pushButton_Exit->setText(QApplication::translate("LoginWindow", "\351\200\200\345\207\272", nullptr));
        label_PassWord->setText(QApplication::translate("LoginWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        label_Title->setText(QApplication::translate("LoginWindow", "\345\234\250\347\272\277\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
