#include "transpositioncipher.h"

#include <QtMath>

TranspositionCipher::TranspositionCipher(QObject *parent) : EncryptionAlgorithm(parent), key_(2)
{

}

TranspositionCipher::TranspositionCipher(std::size_t key, QObject *parent) : EncryptionAlgorithm(parent), key_(key)
{

}

TranspositionCipher::~TranspositionCipher()
{

}

QString TranspositionCipher::encrypt(const QString &textForEncrypt)
{
    QString encrypted;
    QString text = textForEncrypt;

    //Добавляем пробелы до прямоугольника
    int intKey = static_cast<int>(key_);
    if(textForEncrypt.size() % intKey > 0)
        for(int i = 0; i < intKey - ( textForEncrypt.size() % intKey ); i++)
        {
            text += ' ';
        }

    for(int i = 0; i < intKey; i++)
    {
        for(int j = 0; j < text.size() / intKey; j++)
        {
            encrypted += text.at(j * key_ + i);
        }
    }
    return encrypted;
}

QString TranspositionCipher::decrypt(const QString &encryptedText)
{
    return encrypt(encryptedText);
}

QString TranspositionCipher::defaultKey() const
{
    return "2";
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
