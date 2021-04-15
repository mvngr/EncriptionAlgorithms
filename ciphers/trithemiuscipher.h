#ifndef TRITHEMIUSCIPHER_H
#define TRITHEMIUSCIPHER_H

#include <memory>

#include "encryptionalgorithm.h"
#include "dictionaries/dictionary.h"


class TrithemiusCipher : public EncryptionAlgorithm
{
public:
    explicit TrithemiusCipher(QObject *parent = nullptr);
    explicit TrithemiusCipher(const QString &key, QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:

    QString key_;
    std::unique_ptr<Dictionary> dict_ = nullptr;
    std::vector<std::vector<QChar>> matrix_;
};

#endif // TRITHEMIUSCIPHER_H
