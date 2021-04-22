#include "cipherstcpserver.h"

#include <QtNetwork>
#include <QObject>
#include <QDebug>
#include <QCoreApplication>

CiphersTcpServer::CiphersTcpServer()
{
    tcpServer_ = new QTcpServer(this);

    connect(tcpServer_, &QTcpServer::newConnection, this, &CiphersTcpServer::newConnection);

    if(!tcpServer_->listen(QHostAddress::Any, 12393))
    {
        qDebug() << tr("Сервер не смог запуститься");
    }
    else
    {
        qDebug() << tr("Сервер запущен");
    }
}

void CiphersTcpServer::newConnection()
{
    QTcpSocket *socket = tcpServer_->nextPendingConnection();

    connect(socket, &QTcpSocket::readyRead, this, &CiphersTcpServer::onReadyRead);
    connect(socket, &QTcpSocket::stateChanged, this, &CiphersTcpServer::onSocketStateChanged);
    sockets_.push_back(socket);

    qDebug() << tr("Новое подключение:") << socket->peerName();
}

void CiphersTcpServer::onReadyRead()
{
    QTcpSocket *sender = static_cast<QTcpSocket *>(QObject::sender());
    QByteArray data = sender->readAll();
    qDebug() << QString::fromLocal8Bit(data);
}

void CiphersTcpServer::onSocketStateChanged(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
    {
        QTcpSocket *sender = static_cast<QTcpSocket *>(QObject::sender());
        auto foundIt = std::find(sockets_.begin(), sockets_.end(), sender);
        if(foundIt != sockets_.end())
            sockets_.erase(foundIt);
        else
            qWarning() << tr("Не удалось найти сокет в контейнере с сокетами!");
    }
}
