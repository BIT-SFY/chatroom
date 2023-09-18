/********************************************************************************
** Form generated from reading UI file 'signinwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNINWINDOW_H
#define UI_SIGNINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SigninWindow
{
public:
    QPushButton *pushButton_Sure;
    QLineEdit *lineEdit_UserName;
    QLabel *label_UserName;
    QLabel *label_PassWord;
    QLineEdit *lineEdit_PassWord;
    QLabel *label_Title;
    QPushButton *pushButton_Exit;
    QLineEdit *lineEdit_RePassWord;
    QLabel *label_RePassWord;

    void setupUi(QWidget *SigninWindow)
    {
        if (SigninWindow->objectName().isEmpty())
            SigninWindow->setObjectName(QString::fromUtf8("SigninWindow"));
        SigninWindow->resize(627, 498);
        pushButton_Sure = new QPushButton(SigninWindow);
        pushButton_Sure->setObjectName(QString::fromUtf8("pushButton_Sure"));
        pushButton_Sure->setGeometry(QRect(150, 400, 110, 60));
        QFont font;
        font.setPointSize(18);
        pushButton_Sure->setFont(font);
        lineEdit_UserName = new QLineEdit(SigninWindow);
        lineEdit_UserName->setObjectName(QString::fromUtf8("lineEdit_UserName"));
        lineEdit_UserName->setGeometry(QRect(210, 120, 321, 60));
        QFont font1;
        font1.setPointSize(20);
        lineEdit_UserName->setFont(font1);
        label_UserName = new QLabel(SigninWindow);
        label_UserName->setObjectName(QString::fromUtf8("label_UserName"));
        label_UserName->setGeometry(QRect(70, 110, 160, 70));
        label_UserName->setFont(font1);
        label_PassWord = new QLabel(SigninWindow);
        label_PassWord->setObjectName(QString::fromUtf8("label_PassWord"));
        label_PassWord->setGeometry(QRect(70, 200, 160, 70));
        label_PassWord->setFont(font1);
        lineEdit_PassWord = new QLineEdit(SigninWindow);
        lineEdit_PassWord->setObjectName(QString::fromUtf8("lineEdit_PassWord"));
        lineEdit_PassWord->setGeometry(QRect(210, 210, 321, 60));
        lineEdit_PassWord->setFont(font1);
        label_Title = new QLabel(SigninWindow);
        label_Title->setObjectName(QString::fromUtf8("label_Title"));
        label_Title->setGeometry(QRect(130, 30, 361, 61));
        QFont font2;
        font2.setPointSize(30);
        font2.setBold(true);
        font2.setWeight(75);
        label_Title->setFont(font2);
        pushButton_Exit = new QPushButton(SigninWindow);
        pushButton_Exit->setObjectName(QString::fromUtf8("pushButton_Exit"));
        pushButton_Exit->setGeometry(QRect(330, 400, 110, 60));
        pushButton_Exit->setFont(font);
        lineEdit_RePassWord = new QLineEdit(SigninWindow);
        lineEdit_RePassWord->setObjectName(QString::fromUtf8("lineEdit_RePassWord"));
        lineEdit_RePassWord->setGeometry(QRect(210, 300, 321, 60));
        lineEdit_RePassWord->setFont(font1);
        label_RePassWord = new QLabel(SigninWindow);
        label_RePassWord->setObjectName(QString::fromUtf8("label_RePassWord"));
        label_RePassWord->setGeometry(QRect(70, 290, 160, 70));
        label_RePassWord->setFont(font1);

        retranslateUi(SigninWindow);

        QMetaObject::connectSlotsByName(SigninWindow);
    } // setupUi

    void retranslateUi(QWidget *SigninWindow)
    {
        SigninWindow->setWindowTitle(QApplication::translate("SigninWindow", "Form", nullptr));
        pushButton_Sure->setText(QApplication::translate("SigninWindow", "\347\241\256\345\256\232", nullptr));
        label_UserName->setText(QApplication::translate("SigninWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_PassWord->setText(QApplication::translate("SigninWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        lineEdit_PassWord->setText(QString());
        label_Title->setText(QApplication::translate("SigninWindow", "\346\263\250\345\206\214chatroom\344\274\232\345\221\230", nullptr));
        pushButton_Exit->setText(QApplication::translate("SigninWindow", "\351\200\200\345\207\272", nullptr));
        lineEdit_RePassWord->setText(QString());
        label_RePassWord->setText(QApplication::translate("SigninWindow", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SigninWindow: public Ui_SigninWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNINWINDOW_H
