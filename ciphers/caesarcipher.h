#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <memory>

#include "encryptionalgorithm.h"
#include "dictionaries/dictionary.h"

class CaesarCipher : public EncryptionAlgorithm
{
public:
    explicit CaesarCipher( QObject *parent = nullptr);
    explicit CaesarCipher(std::size_t key, QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    QString makeSymbolTransposition(const QString &text, std::size_t offset);

    std::unique_ptr<Dictionary> dict_;
    std::size_t key_;
};

#endif // CAESARCIPHER_H
