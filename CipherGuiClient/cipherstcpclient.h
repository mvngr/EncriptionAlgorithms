#ifndef CIPHERSTCPCLIENT_H
#define CIPHERSTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class CiphersTcpClient : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString serverMessage READ serverMessage NOTIFY recieveMessageFromServer)
public:
    CiphersTcpClient(QObject *parent = nullptr);

    Q_INVOKABLE bool sendDataToServer(const QString &cipherName, const QString &data);
    void onReadyRead();
    Q_INVOKABLE void setHost(const QString &host);

    QString serverMessage() const;

signals:
    void recieveMessageFromServer();

private:
    QTcpSocket socket_;
    QString serverMessage_;

};

#endif // CIPHERSTCPCLIENT_H
