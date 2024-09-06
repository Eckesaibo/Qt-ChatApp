/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_chatwindow
{
public:
    QWidget *centralWidget;
    QWidget *widget1;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_6;
    QWidget *widget;
    QListWidget *chatList;
    QWidget *verticalWidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *horizontalWidget_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *chatWindowTitleLabel;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *backButton;
    QSpacerItem *horizontalSpacer_8;
    QFrame *line_2;
    QListWidget *ui_mag;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *sendPhotoButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *sendFileButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *receiveFileButton;
    QSpacerItem *horizontalSpacer_5;
    QFrame *line;
    QTextEdit *idt;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *voiceInputButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btn1;
    QSpacerItem *horizontalSpacer_7;
    QMenuBar *menuBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *chatwindow)
    {
        if (chatwindow->objectName().isEmpty())
            chatwindow->setObjectName("chatwindow");
        chatwindow->resize(906, 676);
        centralWidget = new QWidget(chatwindow);
        centralWidget->setObjectName("centralWidget");
        widget1 = new QWidget(centralWidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(-10, -30, 921, 671));
        widget1->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245)"));
        horizontalLayoutWidget_4 = new QWidget(widget1);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(10, 30, 903, 643));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(horizontalLayoutWidget_4);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(54, 641));
        widget->setStyleSheet(QString::fromUtf8("border-image: url(:/contact.png) 0 0 0 0 stretch stretch;"));

        horizontalLayout_6->addWidget(widget);

        chatList = new QListWidget(horizontalLayoutWidget_4);
        chatList->setObjectName("chatList");
        chatList->setMinimumSize(QSize(201, 481));
        chatList->setMaximumSize(QSize(201, 16777215));
        chatList->setStyleSheet(QString::fromUtf8("background-color:rgb(234, 232, 231)"));

        horizontalLayout_6->addWidget(chatList);

        verticalWidget = new QWidget(horizontalLayoutWidget_4);
        verticalWidget->setObjectName("verticalWidget");
        verticalLayout_2 = new QVBoxLayout(verticalWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalWidget_3 = new QWidget(verticalWidget);
        horizontalWidget_3->setObjectName("horizontalWidget_3");
        horizontalLayout_5 = new QHBoxLayout(horizontalWidget_3);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        chatWindowTitleLabel = new QLabel(horizontalWidget_3);
        chatWindowTitleLabel->setObjectName("chatWindowTitleLabel");
        chatWindowTitleLabel->setMinimumSize(QSize(61, 41));
        chatWindowTitleLabel->setStyleSheet(QString::fromUtf8("font: 18pt \"Microsoft YaHei UI\";\n"
"color: rgb(0, 0, 0);"));
        chatWindowTitleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout_5->addWidget(chatWindowTitleLabel);

        horizontalSpacer_6 = new QSpacerItem(418, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);

        backButton = new QPushButton(horizontalWidget_3);
        backButton->setObjectName("backButton");
        backButton->setMinimumSize(QSize(91, 31));
        backButton->setMaximumSize(QSize(91, 16777215));
        backButton->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));

        horizontalLayout_5->addWidget(backButton);

        horizontalSpacer_8 = new QSpacerItem(13, 13, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_8);


        verticalLayout_2->addWidget(horizontalWidget_3);

        line_2 = new QFrame(verticalWidget);
        line_2->setObjectName("line_2");
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgba(231, 231, 231,0.3);"));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line_2);

        ui_mag = new QListWidget(verticalWidget);
        ui_mag->setObjectName("ui_mag");
        ui_mag->setMinimumSize(QSize(0, 241));
        ui_mag->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245)"));

        verticalLayout_2->addWidget(ui_mag);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sendPhotoButton = new QPushButton(verticalWidget);
        sendPhotoButton->setObjectName("sendPhotoButton");
        sendPhotoButton->setMinimumSize(QSize(80, 31));
        sendPhotoButton->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));

        horizontalLayout_2->addWidget(sendPhotoButton);

        horizontalSpacer_3 = new QSpacerItem(28, 36, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        sendFileButton = new QPushButton(verticalWidget);
        sendFileButton->setObjectName("sendFileButton");
        sendFileButton->setMinimumSize(QSize(80, 31));
        sendFileButton->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));

        horizontalLayout_2->addWidget(sendFileButton);

        horizontalSpacer_2 = new QSpacerItem(28, 36, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        receiveFileButton = new QPushButton(verticalWidget);
        receiveFileButton->setObjectName("receiveFileButton");
        receiveFileButton->setMinimumSize(QSize(80, 31));
        receiveFileButton->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));

        horizontalLayout_2->addWidget(receiveFileButton);

        horizontalSpacer_5 = new QSpacerItem(328, 36, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_2);

        line = new QFrame(verticalWidget);
        line->setObjectName("line");
        line->setStyleSheet(QString::fromUtf8("background-color: rgba(231, 231, 231,0.3);"));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        verticalLayout_2->addWidget(line);

        idt = new QTextEdit(verticalWidget);
        idt->setObjectName("idt");
        idt->setMinimumSize(QSize(589, 227));
        idt->setStyleSheet(QString::fromUtf8("background-color:rgb(245, 245, 245);\n"
"color:black;\n"
"font-size:18;"));

        verticalLayout_2->addWidget(idt);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(378, 28, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        voiceInputButton = new QPushButton(verticalWidget);
        voiceInputButton->setObjectName("voiceInputButton");
        voiceInputButton->setMinimumSize(QSize(91, 31));
        voiceInputButton->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));

        horizontalLayout_3->addWidget(voiceInputButton);

        horizontalSpacer_4 = new QSpacerItem(13, 28, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        btn1 = new QPushButton(verticalWidget);
        btn1->setObjectName("btn1");
        btn1->setMinimumSize(QSize(91, 31));
        btn1->setStyleSheet(QString::fromUtf8("background-color: rgb(233, 233, 233);\n"
"color: rgb(7, 193, 96);"));

        horizontalLayout_3->addWidget(btn1);

        horizontalSpacer_7 = new QSpacerItem(38, 28, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_6->addWidget(verticalWidget);

        chatwindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(chatwindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 906, 17));
        chatwindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(chatwindow);
        statusBar->setObjectName("statusBar");
        chatwindow->setStatusBar(statusBar);
        toolBar = new QToolBar(chatwindow);
        toolBar->setObjectName("toolBar");
        chatwindow->addToolBar(Qt::ToolBarArea::RightToolBarArea, toolBar);

        retranslateUi(chatwindow);

        QMetaObject::connectSlotsByName(chatwindow);
    } // setupUi

    void retranslateUi(QMainWindow *chatwindow)
    {
        chatwindow->setWindowTitle(QCoreApplication::translate("chatwindow", "Chat Application", nullptr));
        chatWindowTitleLabel->setText(QString());
        backButton->setText(QCoreApplication::translate("chatwindow", "\350\277\224\345\233\236", nullptr));
        sendPhotoButton->setText(QCoreApplication::translate("chatwindow", "\345\217\221\351\200\201\345\233\276\347\211\207", nullptr));
        sendFileButton->setText(QCoreApplication::translate("chatwindow", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        receiveFileButton->setText(QCoreApplication::translate("chatwindow", "\346\216\245\346\224\266\346\226\207\344\273\266", nullptr));
        voiceInputButton->setText(QCoreApplication::translate("chatwindow", "\350\257\255\351\237\263\350\257\206\345\210\253", nullptr));
        btn1->setText(QCoreApplication::translate("chatwindow", "\345\217\221\351\200\201", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("chatwindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class chatwindow: public Ui_chatwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
