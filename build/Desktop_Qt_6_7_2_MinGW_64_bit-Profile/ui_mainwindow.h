/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *sendFileButton;
    QListWidget *userListWidget;
    QTextBrowser *chatTextBrowser;
    QTextEdit *messageTextEdit;
    QPushButton *sendButton;
    QLabel *titleLabel;
    QPushButton *backButton;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(805, 581);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        sendFileButton = new QPushButton(centralWidget);
        sendFileButton->setObjectName("sendFileButton");
        sendFileButton->setGeometry(QRect(210, 330, 80, 31));
        userListWidget = new QListWidget(centralWidget);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setGeometry(QRect(6, 6, 191, 531));
        chatTextBrowser = new QTextBrowser(centralWidget);
        chatTextBrowser->setObjectName("chatTextBrowser");
        chatTextBrowser->setGeometry(QRect(210, 60, 581, 261));
        messageTextEdit = new QTextEdit(centralWidget);
        messageTextEdit->setObjectName("messageTextEdit");
        messageTextEdit->setGeometry(QRect(210, 370, 581, 171));
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(690, 500, 91, 31));
        titleLabel = new QLabel(centralWidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(210, 10, 251, 41));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        backButton = new QPushButton(centralWidget);
        backButton->setObjectName("backButton");
        backButton->setGeometry(QRect(699, 10, 91, 31));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 805, 17));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Chat Application", nullptr));
        sendFileButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "Chat Title", nullptr));
        backButton->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
