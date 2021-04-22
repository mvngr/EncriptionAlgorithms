#ifndef TRANSPOSITIONCIPHER_H
#define TRANSPOSITIONCIPHER_H

#include "encryptionalgorithm.h"

class CIPHERSLIBRARY_EXPORT TranspositionCipher : public EncryptionAlgorithm
{

public:
    explicit TranspositionCipher(QObject *parent = nullptr);
    explicit TranspositionCipher(std::size_t key, QObject *parent = nullptr);

    virtual ~TranspositionCipher();

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    std::size_t key_; //количество столбцов

};

#endif // TRANSPOSITIONCIPHER_H
