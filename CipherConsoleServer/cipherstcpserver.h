#ifndef CIPHERSTCPSERVER_H
#define CIPHERSTCPSERVER_H

#include <QTcpServer>
#include <QObject>
#include <list>
#include <map>
#include <functional>

#include "ciphers/caesarcipher.h"
#include "ciphers/encryptionalgorithm.h"
#include "ciphers/giovanniportacipher.h"
#include "ciphers/gronsfeldcipher.h"
#include "ciphers/magicsquarecipher.h"
#include "ciphers/playfaircipher.h"
#include "ciphers/transpositioncipher.h"
#include "ciphers/trithemiuscipher.h"
#include "ciphers/vigenerecipher.h"


class CiphersTcpServer : public QObject
{
    Q_OBJECT

public:
    CiphersTcpServer();

    void newConnection();
    void onReadyRead();
    void onSocketStateChanged(QAbstractSocket::SocketState socketState);

private:

    template<typename T>
    static QString getDecryptedText(const QString &data)
    {
        auto cipher = new T();
        cipher->setKey(cipher->defaultKey());
        QString res = cipher->decrypt(data);
        delete cipher;
        return res;
    }

    std::map<QString, std::function<QString(QString &)>> decryptFuncs_
    {
        { "Transposition", [](QString &data)    { return getDecryptedText<TranspositionCipher>(data); } },
        { "MagicSquare", [](QString &data)      { return getDecryptedText<MagicSquareCipher>(data); } },
        { "Caesar", [](QString &data)           { return getDecryptedText<CaesarCipher>(data); } },
        { "Gronsfeld", [](QString &data)        { return getDecryptedText<GronsfeldCipher>(data); } },
        { "Playfair", [](QString &data)         { return getDecryptedText<PlayfairCipher>(data); } },
        { "GiovanniPorta", [](QString &data)    { return getDecryptedText<GiovanniPortaCipher>(data); } },
        { "Vigenere", [](QString &data)         { return getDecryptedText<VigenereCipher>(data); } },
        { "Trithemius", [](QString &data)       { return getDecryptedText<TrithemiusCipher>(data); } }
    };

    QTcpServer *tcpServer_ = nullptr;
    std::list<QTcpSocket *> sockets_;
};

#endif // CIPHERSTCPSERVER_H
