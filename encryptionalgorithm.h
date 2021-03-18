#ifndef ENCRYPTIONALGORITHM_H
#define ENCRYPTIONALGORITHM_H

#include <QString>
#include <QObject>

class EncryptionAlgorithm : public QObject
{
    Q_OBJECT
public:

    virtual ~EncryptionAlgorithm();
    Q_INVOKABLE virtual QString encrypt(const QString &textForEncrypt) = 0;
    Q_INVOKABLE virtual QString decrypt(const QString &encryptedText) = 0;
    Q_INVOKABLE virtual QString defaultKey() const = 0;
    Q_INVOKABLE virtual bool setKey(const QString &key) = 0;
    Q_INVOKABLE virtual QString errorString() const;
    Q_INVOKABLE bool hasError() const;

protected:
    explicit EncryptionAlgorithm(QObject *parent = nullptr);
    QString error_;
};

#endif // ENCRYPTIONALGORITHM_H
