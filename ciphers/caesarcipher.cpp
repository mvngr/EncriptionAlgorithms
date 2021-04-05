#include "caesarcipher.h"

CaesarCipher::CaesarCipher(QObject *parent) : EncryptionAlgorithm(parent)
{

}

CaesarCipher::CaesarCipher(std::size_t key, QObject *parent) : EncryptionAlgorithm(parent), key_(key)
{

}

QString CaesarCipher::encrypt(const QString &textForEncrypt)
{
    return makeSymbolTransposition(textForEncrypt, key_);
}

QString CaesarCipher::decrypt(const QString &encryptedText)
{
    return makeSymbolTransposition(encryptedText, -key_);
}

QString CaesarCipher::makeSymbolTransposition(const QString &text, std::size_t offset)
{
    QString res;
    wchar_t arr[text.size()]; //Предусмотрительно заганяем в тип, при котором не полетит кирилица и латынь
    int num = text.toWCharArray(arr);
    for(int i = 0; i < text.size(); i++)
        arr[i] += offset;
    res = QString::fromWCharArray(arr, num);

    return res;
}

QString CaesarCipher::defaultKey() const
{
    return "5";
}

bool CaesarCipher::setKey(const QString &key)
{
    bool isOk = false;
    std::size_t numberKey = key.toUInt(&isOk);
    if(isOk)
    {
        key_ = numberKey;
    }

    return isOk;
}
