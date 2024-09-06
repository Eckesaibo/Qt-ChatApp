#include "clienthandlerthread.h"
#include <QFile>
QList<QTcpSocket*> ClientHandlerThread::clientList; // 初始化静态成员变量

ClientHandlerThread::ClientHandlerThread(QTcpSocket * tcp, QObject *parent) : QThread(parent)
{
    m_tcp = tcp;
    clientList.append(m_tcp);
}
void ClientHandlerThread::run()
{
    qDebug() << "服务器子线程：" << QThread::currentThread();

    connect(m_tcp, &QTcpSocket::readyRead, this, [=]()
            {
                qDebug() << "read";
                QByteArray msg = m_tcp->readAll();

                // 将消息广播给所有客户端
                for (QTcpSocket *client : clientList)
                {
                    if (client && client->state() == QAbstractSocket::ConnectedState)
                    {
                        client->write(msg);
                    }
                }
            });

    exec();
}
