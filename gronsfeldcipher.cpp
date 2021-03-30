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
    QString keyForText;
    //дополняем недостающими знаками
    for(int i = 0; i < textForEncrypt.size(); i++)
    {
        keyForText += key_.at(i % key_.size());
    }

    for(int i = 0; i < textForEncrypt.size(); i++)
    {
        auto foundIt = std::find(textDictionary_.cbegin(), textDictionary_.cend(), textForEncrypt.at(i));
        if(foundIt == textDictionary_.cend())
        {
            error_ = tr("В введенном тексте для шифрации содержится недопустимый символ \"%1\"").arg(textForEncrypt.at(i));
        }
        else
        {
            auto foundKeyIt = std::find(keyDictionary_.cbegin(), keyDictionary_.cend(), keyForText.at(i));
            if(foundKeyIt == keyDictionary_.cend())
            {
                error_ = tr("В введенном ключе для шифрации содержутся недопустимые символ \"%1\"").arg(keyForText.at(i));
            }
            else
            {

            }
        }
    }
    return textForEncrypt;
}

QString GronsfeldCipher::decrypt(const QString &encryptedText)
{
    return "";
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
