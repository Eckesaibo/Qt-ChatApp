#ifndef SERVER_H
#define SERVER_H

#include <QWidget>
#include <QTcpServer>        //服务器头文件
#include <QTcpSocket>     //客户端头文件
#include <QList>       //客户端容器链表
#include <QMessageBox>

class Server : public QObject
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    void start();
private:
    //定义服务器指针
    QTcpServer * m_Server;
};

#endif // SERVER_H
