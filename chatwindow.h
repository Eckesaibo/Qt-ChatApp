#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include "qlistwidget.h"
#include "SocketThread.h"
#include <QTcpSocket>
#include <QMainWindow>
#include <QMessageBox>
#include <QAudioInput>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QAudioSource>
#include <QAudioFormat>
#include <QFile>
#include <QIODevice>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QThread>


QT_BEGIN_NAMESPACE
namespace Ui {
class chatwindow;
}
QT_END_NAMESPACE
class chatwindow : public QMainWindow
{
    Q_OBJECT

public:
    chatwindow(QWidget *parent = nullptr);
    ~chatwindow();
    void setCurrentUsername(const QString &username);
    void initializeContactList();  // 初始化联系人列表
    QString currentusername;  // 存储当前登录的用户名


private slots:
    void readyRead_slot(QByteArray msg); //处理readyRead信号槽函数
    void on_btn1_clicked();
    void onContactClicked(QListWidgetItem *item);
    void sendPhotoButton_clicked();
    void sendFileButton_clicked();
    void receiveFileButton_clicked();
    //语音识别
    void startRecording();
    void writeAudioData();
    void stopRecording();
    void recognizeSpeech();

    void on_backButton_clicked();

private:
    Ui::chatwindow *ui;
    void loadChatHistory(const QString &username);
    QTcpSocket *socket;
    // 录音相关成员变量
    QAudioSource *audioSource = nullptr;
    QIODevice *audioIODevice = nullptr;
    QFile *outputFile = nullptr;
    //创建气泡相关
    QWidget* createMessageBubble(const QString &username, const QString &message, bool isSelf);
    QWidget* createImageBubble(const QString &username, const QString &imagePath, bool isSelf);
    QWidget* createFileBubble(const QString &content);
    QString getAvatarPathFromUsername(const QString &username);
    //聊天记录相关
    void saveMessageToHistory(const QString &sender, const QString &receiver, const QString &content, const QString &contentType);
    void loadChatHistory(const QString &username1, const QString &username2);
    SocketThread *socketThread;

signals:
    void startConnect(quint16, QString);
    void sendMsgSignal(QString);
};

#endif // CHATWINDOW_H
