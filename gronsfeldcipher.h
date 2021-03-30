#ifndef GRONSFELDCIPHER_H
#define GRONSFELDCIPHER_H

#include "encryptionalgorithm.h"
#include "dictionaries/cyrillicdictionary.h"

class GronsfeldCipher : public EncryptionAlgorithm
{
public:
    GronsfeldCipher(QObject *parent = nullptr);
    GronsfeldCipher(const QString &key, QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    QString key_;
    std::vector<std::vector<QChar>> matrix_;
    std::vector<QChar> textDictionary_;
    std::vector<QChar> keyDictionary_;
};

#endif // GRONSFELDCIPHER_H
