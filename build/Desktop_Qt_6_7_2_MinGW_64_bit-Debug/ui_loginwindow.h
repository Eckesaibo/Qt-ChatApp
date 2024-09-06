/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
    QPushButton *loginButton_2;
    QWidget *widget;

    void setupUi(QWidget *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(400, 200);
        LoginWindow->setStyleSheet(QString::fromUtf8(""));
        usernameLineEdit = new QLineEdit(LoginWindow);
        usernameLineEdit->setObjectName("usernameLineEdit");
        usernameLineEdit->setGeometry(QRect(120, 60, 131, 31));
        usernameLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 10pt \"Microsoft YaHei UI\";"));
        passwordLineEdit = new QLineEdit(LoginWindow);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setGeometry(QRect(120, 110, 131, 31));
        passwordLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"font: 10pt \"Microsoft YaHei UI\";"));
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        loginButton = new QPushButton(LoginWindow);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(300, 90, 61, 31));
        loginButton->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));
        loginButton_2 = new QPushButton(LoginWindow);
        loginButton_2->setObjectName("loginButton_2");
        loginButton_2->setGeometry(QRect(320, 10, 61, 31));
        loginButton_2->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));
        widget = new QWidget(LoginWindow);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(-90, -50, 501, 261));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/login.png) 0 0 0 0 stretch stretch;"));
        widget->raise();
        usernameLineEdit->raise();
        passwordLineEdit->raise();
        loginButton->raise();
        loginButton_2->raise();

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QWidget *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        loginButton->setText(QCoreApplication::translate("LoginWindow", "\347\231\273\345\275\225", nullptr));
        loginButton_2->setText(QCoreApplication::translate("LoginWindow", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
