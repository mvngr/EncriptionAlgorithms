#include "encryptionalgorithm.h"

EncryptionAlgorithm::EncryptionAlgorithm(QObject *parent) : QObject(parent)
{

}

EncryptionAlgorithm::~EncryptionAlgorithm()
{

}

QString EncryptionAlgorithm::errorString() const
{
    return error_;
}

bool EncryptionAlgorithm::hasError() const
{
    return !error_.isEmpty();
}
