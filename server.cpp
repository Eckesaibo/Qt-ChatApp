#include "server.h"
#include "clienthandlerthread.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    //实例化一个服务器
    m_Server = new QTcpServer(this);
}

// 启动服务器按钮对应的槽函数
void Server::start()
{
    // 获取ui界面上的端口号
    quint16 port = 8888;
    // 将服务器设置为监听状态
    m_Server->listen(QHostAddress::Any, port);
    qDebug()<<"server listen";
    // 将该信号链接到自定义槽函数中，处理相关逻辑
    connect(m_Server, &QTcpServer::newConnection, this, [=]()
            {
                // 得到用于通信的套接字对象
                QTcpSocket * m_tcp = m_Server->nextPendingConnection();
                ClientHandlerThread * sub = new ClientHandlerThread(m_tcp);
                sub->start();
            });
}
