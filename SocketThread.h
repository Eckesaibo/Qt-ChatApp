#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QObject>
#include <QTcpSocket>
class SocketThread : public QObject
{
    Q_OBJECT
public:
    explicit SocketThread(QObject *parent = nullptr);
    void connectServer(quint16 port, QString IP);
    void sendMsgToServer(QString path);

signals:
    void connectOK();
    void gameOver();
    void messageReceived(QByteArray msg);

private slots:
    void onReadyRead();

private:
    QTcpSocket * m_tcp;
};

#endif

