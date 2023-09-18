/********************************************************************************
** Form generated from reading UI file 'createaddwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEADDWINDOW_H
#define UI_CREATEADDWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CreateAddWindow
{
public:
    QLabel *label;
    QLineEdit *lineEdit_id;
    QPushButton *pushButton_Sure;
    QLabel *label_GroupName;
    QLineEdit *lineEdit_GroupName;

    void setupUi(QDialog *CreateAddWindow)
    {
        if (CreateAddWindow->objectName().isEmpty())
            CreateAddWindow->setObjectName(QString::fromUtf8("CreateAddWindow"));
        CreateAddWindow->resize(407, 233);
        label = new QLabel(CreateAddWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 131, 41));
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
        lineEdit_id = new QLineEdit(CreateAddWindow);
        lineEdit_id->setObjectName(QString::fromUtf8("lineEdit_id"));
        lineEdit_id->setGeometry(QRect(140, 40, 251, 51));
        lineEdit_id->setFont(font);
        pushButton_Sure = new QPushButton(CreateAddWindow);
        pushButton_Sure->setObjectName(QString::fromUtf8("pushButton_Sure"));
        pushButton_Sure->setGeometry(QRect(310, 180, 81, 41));
        QFont font1;
        font1.setPointSize(18);
        pushButton_Sure->setFont(font1);
        label_GroupName = new QLabel(CreateAddWindow);
        label_GroupName->setObjectName(QString::fromUtf8("label_GroupName"));
        label_GroupName->setGeometry(QRect(10, 120, 131, 41));
        label_GroupName->setFont(font);
        lineEdit_GroupName = new QLineEdit(CreateAddWindow);
        lineEdit_GroupName->setObjectName(QString::fromUtf8("lineEdit_GroupName"));
        lineEdit_GroupName->setGeometry(QRect(140, 120, 251, 51));
        lineEdit_GroupName->setFont(font);

        retranslateUi(CreateAddWindow);

        QMetaObject::connectSlotsByName(CreateAddWindow);
    } // setupUi

    void retranslateUi(QDialog *CreateAddWindow)
    {
        CreateAddWindow->setWindowTitle(QApplication::translate("CreateAddWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("CreateAddWindow", "\345\210\233\345\273\272\347\276\244\350\201\212\357\274\232", nullptr));
        pushButton_Sure->setText(QApplication::translate("CreateAddWindow", "\347\241\256\345\256\232", nullptr));
        label_GroupName->setText(QApplication::translate("CreateAddWindow", "\347\276\244\350\201\212\345\220\215\347\247\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CreateAddWindow: public Ui_CreateAddWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEADDWINDOW_H
