#ifndef MAGICSQUARECIPHER_H
#define MAGICSQUARECIPHER_H

#include "encryptionalgorithm.h"

#include <vector>

typedef std::vector<std::vector<int>> Matrix;

class CIPHERSLIBRARY_EXPORT MagicSquareCipher : public EncryptionAlgorithm
{

public:
    explicit MagicSquareCipher(QObject *parent = nullptr);
    explicit MagicSquareCipher(const Matrix &magicSquare, QObject *parent = nullptr);
    ~MagicSquareCipher();

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;
    QString defaultKey() const override;
    bool setKey(const QString &key) override;

private:
    Matrix matrix_;
    std::size_t matrixSize_;
};

#endif // MAGICSQUARECIPHER_H
