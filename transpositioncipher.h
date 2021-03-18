#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include "encryptionalgorithm.h"

class TranspositionCipher : public EncryptionAlgorithm
{

public:
    explicit TranspositionCipher(QObject *parent = nullptr);
    TranspositionCipher(std::size_t offsetSize, QObject *parent = nullptr);
    virtual ~TranspositionCipher();

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    QString makeSymbolTransposition(const QString &text, std::size_t offset);

    std::size_t key_;
};

#endif // TRANSPOSITIONCIPHER_H
