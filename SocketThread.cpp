#include "SocketThread.h"

#include <QFile>
#include <QHostAddress>
#include <QFileInfo>

SocketThread::SocketThread(QObject *parent) : QObject(parent)
{

}
// 当前是在子线程
void SocketThread::connectServer(quint16 port, QString IP)
{
    m_tcp = new QTcpSocket;
    m_tcp->connectToHost(QHostAddress(IP),port);
    qDebug()<<"connect";
    connect(m_tcp, &QTcpSocket::connected, this, &SocketThread::connectOK);
    connect(m_tcp, &QTcpSocket::disconnected, this, [=](){
        m_tcp->close();
        m_tcp->deleteLater();
        emit gameOver();
    });
    connect(m_tcp, &QTcpSocket::readyRead, this,&SocketThread::onReadyRead);
}

void SocketThread::sendMsgToServer(QString msg)
{
    qDebug()<<"send";
    m_tcp->write(msg.toLocal8Bit());
}
void SocketThread::onReadyRead()
{
    // 读取服务器发送的消息
    QByteArray msg = m_tcp->readAll();
    qDebug() << "Received:" << msg;

    // 发出信号，将消息传递给外部
    emit messageReceived(msg);
}
