#ifndef ENCRYPTIONALGORITHM_H
#define ENCRYPTIONALGORITHM_H

#include <QString>
#include <QObject>

class EncryptionAlgorithm
{
public:


    virtual ~EncryptionAlgorithm();
    virtual QString encrypt(const QString &textForEncrypt) = 0;
    virtual QString decrypt(const QString &encryptedText) = 0;
    virtual QString errorString() const;
    bool hasError() const;

protected:
    EncryptionAlgorithm();
    QString error_;
};

#endif // ENCRYPTIONALGORITHM_H
