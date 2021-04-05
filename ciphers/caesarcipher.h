#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include "encryptionalgorithm.h"

class CaesarCipher : public EncryptionAlgorithm
{
public:
    CaesarCipher( QObject *parent = nullptr);
    CaesarCipher(std::size_t key, QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    QString makeSymbolTransposition(const QString &text, std::size_t offset);

    std::size_t key_;
};

#endif // CAESARCIPHER_H
