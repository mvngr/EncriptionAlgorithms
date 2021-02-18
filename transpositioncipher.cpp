#include "transpositioncipher.h"

#include <QDebug>

TranspositionCipher::TranspositionCipher(std::size_t offsetSize) : EncryptionAlgorithm(), key_(offsetSize)
{

}

TranspositionCipher::~TranspositionCipher()
{

}

QString TranspositionCipher::encrypt(const QString &textForEncrypt)
{
    QString res;

    wchar_t arr[textForEncrypt.size()]; //Предусмотрительно заганяем в тип, при котором не полетит кирилица и латынь
    int num = textForEncrypt.toWCharArray(arr);
    for(int i = 0; i < textForEncrypt.size(); i++)
        arr[i] += key_;
    res = QString::fromWCharArray(arr, num);

    return res;
}

QString TranspositionCipher::decrypt(const QString &encryptedText)
{
    QString res;

    wchar_t arr[encryptedText.size()]; //Предусмотрительно заганяем в тип, при котором не полетит кирилица и латынь
    int num = encryptedText.toWCharArray(arr);
    for(int i = 0; i < encryptedText.size(); i++)
        arr[i] -= key_;
    res = QString::fromWCharArray(arr, num);

    return res;
}
