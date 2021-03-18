#include "transpositioncipher.h"

#include <QDebug>

TranspositionCipher::TranspositionCipher(QObject *parent) : EncryptionAlgorithm(parent), key_(5)
{

}

TranspositionCipher::TranspositionCipher(std::size_t offsetSize, QObject *parent) : EncryptionAlgorithm(parent), key_(offsetSize)
{

}

TranspositionCipher::~TranspositionCipher()
{

}

QString TranspositionCipher::encrypt(const QString &textForEncrypt)
{
    return makeSymbolTransposition(textForEncrypt, key_);
}

QString TranspositionCipher::decrypt(const QString &encryptedText)
{
    return makeSymbolTransposition(encryptedText, -key_);
}

QString TranspositionCipher::makeSymbolTransposition(const QString &text, std::size_t offset)
{
    QString res;
    wchar_t arr[text.size()]; //Предусмотрительно заганяем в тип, при котором не полетит кирилица и латынь
    int num = text.toWCharArray(arr);
    for(int i = 0; i < text.size(); i++)
        arr[i] += offset;
    res = QString::fromWCharArray(arr, num);

    return res;
}

QString TranspositionCipher::defaultKey() const
{
    return "5";
}

bool TranspositionCipher::setKey(const QString &key)
{
    bool isOk = false;
    std::size_t numberKey = key.toUInt(&isOk);
    if(isOk)
    {
        key_ = numberKey;
    }

    return isOk;
}
