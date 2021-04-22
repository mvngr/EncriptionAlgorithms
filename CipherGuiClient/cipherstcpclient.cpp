#include "cipherstcpclient.h"

#include <QByteArray>
#include <QHostAddress>

CiphersTcpClient::CiphersTcpClient(QObject *parent) : QObject(parent)
{
    socket_.connectToHost(QHostAddress("127.0.0.1"), 12393);
    connect(&socket_, &QTcpSocket::readyRead, this, &CiphersTcpClient::onReadyRead);
}

bool CiphersTcpClient::sendDataToServer(const QString &data)
{
    return socket_.write(data.toLocal8Bit()) != -1;
}

void CiphersTcpClient::onReadyRead()
{
    QByteArray data = socket_.readAll();
    serverMessage_ = QString::fromLatin1(data);
    emit recieveMessageFromServer();
    qDebug() << data;
}

QString CiphersTcpClient::serverMessage() const
{
    return serverMessage_;
}
