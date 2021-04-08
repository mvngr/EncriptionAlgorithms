#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include <memory>

#include "encryptionalgorithm.h"
#include "dictionaries/dictionary.h"

class PlayfairCipher : public EncryptionAlgorithm
{
public:
    explicit PlayfairCipher(QObject *parent = nullptr);
    explicit PlayfairCipher(const QString &key, QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:

    QString key_;
    std::unique_ptr<Dictionary> dict_ = nullptr;
};

#endif // PLAYFAIRCIPHER_H
