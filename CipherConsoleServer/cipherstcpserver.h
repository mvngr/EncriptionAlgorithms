#ifndef CIPHERSTCPSERVER_H
#define CIPHERSTCPSERVER_H

#include <QTcpServer>
#include <QObject>
#include <list>

class CiphersTcpServer : public QObject
{
    Q_OBJECT

public:
    CiphersTcpServer();

    void newConnection();
    void onReadyRead();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);

private:

    QTcpServer *tcpServer_ = nullptr;
    std::list<QTcpSocket *> sockets_;
};

#endif // CIPHERSTCPSERVER_H
