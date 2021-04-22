#include "caesarcipher.h"

#include "dictionaries/cyrillicdictionary.h"

CaesarCipher::CaesarCipher(QObject *parent) : EncryptionAlgorithm(parent)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
}

CaesarCipher::CaesarCipher(std::size_t key, QObject *parent) : EncryptionAlgorithm(parent), key_(key)
{
    dict_ = std::unique_ptr<CyrillicDictionary>(new CyrillicDictionary());
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

    for(const QChar &ch : text)
    {
        res.push_back(dict_->offsetChar(ch, offset));
    }

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
