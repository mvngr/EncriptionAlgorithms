#include "gronsfeldcipher.h"

GronsfeldCipher::GronsfeldCipher(QObject *parent) : EncryptionAlgorithm(parent)
{
    CyrillicDictionary d;
    matrix_ = d.mergeWithDictionary(d);
    textDictionary_ = d.dictionary();
    keyDictionary_ = d.dictionary();
}

GronsfeldCipher::GronsfeldCipher(const QString &key, QObject *parent) : EncryptionAlgorithm(parent), key_(key)
{
    CyrillicDictionary d;
    matrix_ = d.mergeWithDictionary(d);
    textDictionary_ = d.dictionary();
    keyDictionary_ = d.dictionary();
}

QString GronsfeldCipher::encrypt(const QString &textForEncrypt)
{
    error_ = "";
    QString encryptedText;

    QString keyForText;
    //дополняем недостающими знаками
    for(int i = 0; i < textForEncrypt.size(); i++)
    {
        keyForText += key_.at(i % key_.size());
    }

    for(int i = 0; i < textForEncrypt.size(); i++)
    {
        int textIndex = indexOf(textForEncrypt.at(i), textDictionary_);
        if(textIndex == -1)
        {
            error_ = tr("В введенном тексте для шифрации содержится недопустимый символ \"%1\"").arg(textForEncrypt.at(i));
        }
        else
        {
            auto keyIndex = indexOf(keyForText.at(i), keyDictionary_);
            if(keyIndex == -1)
            {
                error_ = tr("В введенном ключе для шифрации содержутся недопустимые символ \"%1\"").arg(keyForText.at(i));
            }
            else
            {
                encryptedText += matrix_.at(keyIndex).at(textIndex);
            }
        }
    }
    return encryptedText;
}

QString GronsfeldCipher::decrypt(const QString &encryptedText)
{
    error_ = "";
    QString decryptedText;

    QString keyForText;
    //дополняем недостающими знаками
    for(int i = 0; i < encryptedText.size(); i++)
    {
        keyForText += key_.at(i % key_.size());
    }

    for(int i = 0; i < encryptedText.size(); i++)
    {
        auto keyIndex = indexOf(keyForText.at(i), keyDictionary_);
        if(keyIndex == -1)
        {
            error_ = tr("В введенном ключе для дешифрации содержутся недопустимые символ \"%1\"").arg(keyForText.at(i));
        }
        else
        {
            int textIndex = indexOf(encryptedText.at(i), matrix_.at(keyIndex));
            if(textIndex == -1)
            {
                error_ = tr("В введенном тексте для дешифрации содержится недопустимый символ \"%1\"").arg(encryptedText.at(i));
            }
            else
            {
                decryptedText += textDictionary_.at(textIndex);
            }
        }
    }
    return decryptedText;
}

int GronsfeldCipher::indexOf(QChar value, std::vector<QChar> dictionary)
{
    int res = -1;
    for(std::size_t i = 0; i < dictionary.size(); i++)
    {
        if(dictionary.at(i) == value)
        {
            res = static_cast<int>(i);
            break;
        }
    }
    return res;
}

QString GronsfeldCipher::defaultKey() const
{
    return "гронсфельд";
}

bool GronsfeldCipher::setKey(const QString &key)
{
    key_ = key;

    return true;
}
