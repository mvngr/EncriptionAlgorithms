#include "cipherstcpclient.h"

#include <QByteArray>
#include <QHostAddress>

CiphersTcpClient::CiphersTcpClient(QObject *parent) : QObject(parent)
{
    socket_.connectToHost(QHostAddress("127.0.0.1"), 12393);
    connect(&socket_, &QTcpSocket::readyRead, this, &CiphersTcpClient::onReadyRead);
}

bool CiphersTcpClient::sendDataToServer(const QString &cipherName, const QString &data)
{
    return socket_.write((cipherName + ';' + data).toLocal8Bit()) != -1;
}

void CiphersTcpClient::onReadyRead()
{
    QByteArray data = socket_.readAll();
    serverMessage_ = QString::fromLocal8Bit(data);
    emit recieveMessageFromServer();
}

void CiphersTcpClient::setHost(const QString &host)
{
    socket_.disconnectFromHost();
    socket_.connectToHost(QHostAddress(host), 12393);
}

QString CiphersTcpClient::serverMessage() const
{
    return serverMessage_;
}
