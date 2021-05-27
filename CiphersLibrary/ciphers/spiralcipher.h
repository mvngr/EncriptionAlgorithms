#ifndef SPIRALCIPHER_H
#define SPIRALCIPHER_H

#include <memory>

#include "encryptionalgorithm.h"
#include "dictionaries/dictionary.h"

class CIPHERSLIBRARY_EXPORT SpiralCipher : public EncryptionAlgorithm
{
public:
    explicit SpiralCipher(QObject *parent = nullptr);

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    double pointToDist(double x, double y) const;
    double polarToDist(double phi) const;


    QString key_;
    std::unique_ptr<Dictionary> dict_ = nullptr;
    std::vector<std::vector<QChar>> matrix_;

    double distanceBetweenCoils_ = 1.0;
};

#endif // SPIRALCIPHER_H
