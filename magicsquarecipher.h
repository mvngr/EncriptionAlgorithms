#ifndef MAGICSQUARECIPHER_H
#define MAGICSQUARECIPHER_H

#include "encryptionalgorithm.h"

#include <vector>

typedef std::vector<std::vector<int>> Matrix;

class MagicSquareCipher : public EncryptionAlgorithm
{

public:
    MagicSquareCipher(const Matrix &magicSquare);
    ~MagicSquareCipher();

    QString encrypt(const QString &textForEncrypt) override;
    QString decrypt(const QString &encryptedText) override;

private:
    Matrix matrix_;
    std::size_t matrixSize_;
};

#endif // MAGICSQUARECIPHER_H
