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
    QString defaultKey() override;

private:
//    std::pair<QChar, QChar> cyrillicRange_= std::make_pair(L'а', L'Я');
//    std::pair<QChar, QChar> latinRange_ = std::make_pair(L'a', L'Z');

    std::size_t key_;
};

#endif // TRANSPOSITIONCIPHER_H
