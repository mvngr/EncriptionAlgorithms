#include "transpositioncipher.h"

#include <QDebug>

TranspositionCipher::TranspositionCipher(QObject *parent) : EncryptionAlgorithm(parent)
{

}

TranspositionCipher::~TranspositionCipher()
{

}

QString TranspositionCipher::encrypt(const QString &textForEncrypt)
{

}

QString TranspositionCipher::decrypt(const QString &encryptedText)
{

}

QString TranspositionCipher::defaultKey() const
{
    return "qwe";
}

bool TranspositionCipher::setKey(const QString &key)
{
    return true;
}
