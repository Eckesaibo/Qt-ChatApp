#ifndef CLIENTHANDLERTHREAD_H
#define CLIENTHANDLERTHREAD_H

#include <QThread>
#include <QTcpSocket>

class ClientHandlerThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientHandlerThread(QTcpSocket * tcp, QObject *parent = nullptr);
    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    QTcpSocket * m_tcp;
    static QList<QTcpSocket*> clientList;
};

#endif // CLIENTHANDLERTHREAD_H
