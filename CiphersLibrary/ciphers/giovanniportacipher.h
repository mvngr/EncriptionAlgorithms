#ifndef GIOVANNIPORTACIPHER_H
#define GIOVANNIPORTACIPHER_H

#include "encryptionalgorithm.h"
#include "dictionaries/dictionary.h"

#include <memory>

class CIPHERSLIBRARY_EXPORT GiovanniPortaCipher : public EncryptionAlgorithm
{
public:
    explicit GiovanniPortaCipher(QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    QString wcharToNumberString(const QString &wcharString);
    QString numberStringToWchar(const QString &numberString);

    std::unique_ptr<Dictionary> dict_;
    std::vector<std::vector<QChar>> matrix_;
};

#endif // GIOVANNIPORTACIPHER_H
