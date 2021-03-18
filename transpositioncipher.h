#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include "encryptionalgorithm.h"

class TranspositionCipher : public EncryptionAlgorithm
{

public:
    explicit TranspositionCipher(QObject *parent = nullptr);

    virtual ~TranspositionCipher();

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

};

#endif // TRANSPOSITIONCIPHER_H
