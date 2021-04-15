#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <memory>

#include "encryptionalgorithm.h"
#include "dictionaries/dictionary.h"

class VigenereCipher : public EncryptionAlgorithm
{
public:
    explicit VigenereCipher(QObject *parent = nullptr);
    explicit VigenereCipher(const QString key, QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:

    QString repeatKeyToSize(const int size);

    QString key_;
    std::unique_ptr<Dictionary> dict_ = nullptr;
    std::vector<std::vector<QChar>> matrix_;
};

#endif // VIGENERECIPHER_H
